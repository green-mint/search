#include "../include/utils.h"
#include "../include/csv.h"
#include <fstream>
#include <string.h>

wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
stemming::english_stem<> stemmer;

void populateStopWords(const std::string &filename,
  std::unordered_map<std::string, char> &stopWords) {
  io::CSVReader<1> in(filename.c_str());
  in.read_header(io::ignore_extra_column, "words");

  string words;
  while (in.read_row(words)) {
    stopWords[words] = 'f';
  }
}

void populateMetadata(const string &filename, unordered_map<string, Article> &metadata) {
  io::CSVReader<4, io::trim_chars<' '>, io::double_quote_escape<',', '\"'> >in(filename.c_str());
  in.read_header(io::ignore_extra_column, "id", "title", "path_to_file", "updated_at");

  string id, title, path_to_file, updated_at;
  while (in.read_row(id, title, path_to_file, updated_at)) {
    toISODate(updated_at);
    Article article(id, title, path_to_file, date_from_iso_string(updated_at));
    metadata[id] = article;
  }
}

void toISODate(std::string &date) {
  std::stringstream ss;
  char *dateString = (char *) date.c_str();

  char *segment;
  size_t counter = 0;
  for (segment = strtok(dateString, "-T"); segment != NULL && counter < 3; segment = strtok(NULL, "-T")) {
    ss << string(segment);
    counter++;
  }
  date = ss.str();
}

void stemWord(const string &input, string &output) {
  wstring str = converter.from_bytes(input);
  stemmer(str);
  output = converter.to_bytes(str);
}

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, Article> &metadata) {
  size_t filesread = 0;
  for (auto it : metadata) {
    string fileId = it.first;
    Article &article = it.second;

    ifstream file(CLEANED_ARTICLES_DIR + article.path_to_file);
    string line;

    char *segment;
    string stemmedWord;
    string originalWord;
    size_t position = 0;
    while (getline(file, line)) {
      position = 0;
      for (segment = strtok((char *) line.c_str(), " "); segment != NULL; segment = strtok(NULL, " ")) {
        originalWord = string(segment);
        stemWord(originalWord, stemmedWord);
        invertedIndex.addWord(stemmedWord, fileId, position);
        ++position;
      }

      // cout << "Processed " << article.path_to_file << endl;
    }
    if (++filesread == 20) break;
  }
}

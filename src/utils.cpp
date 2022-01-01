#include "../include/utils.h"
#include "../include/csv.h"

using namespace std;

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
  // id
  // title
  // path_to_file
  // updated_at
  // another_title
  in.read_header(io::ignore_extra_column, "id", "title", "path_to_file", "updated_at");

  string id, title, path_to_file, updated_at;
  while (in.read_row(id, title, path_to_file, updated_at)) {
    Article article(id, title, path_to_file, date());
    metadata[id] = article;
  }
}

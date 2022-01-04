#include <csv.h>
#include <string.h>
#include <stringutils.h>
#include <trie.h>
#include <utils.h>

#include <fstream>

static wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
static stemming::english_stem<> stemmer;

void toISODate(std::string &date) {
  std::stringstream ss;
  char *dateString = (char *) date.c_str();

  char *segment;
  size_t counter = 0;
  for (segment = strtok(dateString, "-T"); segment != NULL && counter < 3;
    segment = strtok(NULL, "-T")) {
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


void loadLexicon(unordered_map<string, int> &lexicon) {
  const string filename = LEXICON_FILENAME;

  io::CSVReader<2> in(filename);
  in.read_header(io::ignore_extra_column, "word", "wordId");

  string word;
  uint32_t wordId;

  while (in.read_row(word, wordId)) {
    lexicon[word] = wordId;
  }
}

void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output) {
  stringstream ss(input);
  string item;
  while (getline(ss, item, delimiter)) {
    output.push_back(item);
  }
}

void populateTrie(Trie &trie, const unordered_map<string, Article> &metadata) {
  for (auto &article : metadata) {
    string title = article.second.title;
    string lowerSpaceRemovedTitle = lowerAndRemoveSpace(title);
    if (checkTitle(lowerSpaceRemovedTitle)) {
      // cout << title << endl;
      // cout << lowerSpaceRemovedTitle << endl;
      trie.insert(lowerSpaceRemovedTitle);
    }
  }

  cout << "Trie populated" << endl;
}

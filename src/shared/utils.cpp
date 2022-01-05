#include <csv.h>
#include <string.h>
#include <stringutils.h>
#include <trie.h>
#include <utils.h>
#include <fstream>
#include <indexing.h>

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


void loadLexicon(unordered_map<string, uint32_t> &lexiconMap) {
  const string filename = LEXICON_FILENAME;

  io::CSVReader<2> in(filename);
  in.read_header(io::ignore_extra_column, "word", "wordId");

  string word;
  uint32_t wordId;

  while (in.read_row(word, wordId)) {
    lexiconMap[word] = wordId;
  }
}

void populateTrie(Trie &trie, const unordered_map<uint32_t, ArticleMeta> &metadata) {
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


void getFileIdFromQuery(const string &query, DoublyLinkedList<uint32_t> &fileIds, DoublyLinkedList<string> &words, unordered_map<string, uint32_t> &lexiconMap) {
  DoublyLinkedList<string> queryWords;
  splitString(query, ' ', queryWords);

  DoublyLinkedList<string> stemmedQuery;
  for (auto head = queryWords.get_head(); head != nullptr; head = head->next) {
    string word = head->data;
    string stemmedWord;
    stemWord(word, stemmedWord);

    stemmedQuery.push_back(stemmedWord);
  }

  for (auto head = stemmedQuery.get_head(); head != nullptr; head = head->next) {
    if (lexiconMap[head->data]) {
      fileIds.push_back(lexiconMap[head->data]);
      words.push_back(head->data);
    }
  }

}

void loadMetadata(unordered_map<uint32_t, ArticleMeta> &metadata) {
  populateMetadata(METADATA_FILENAME, metadata);
}

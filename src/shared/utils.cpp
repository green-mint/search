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


void loadLexicon(HashMap<string, uint32_t> &lexiconMap) {
  const string filename = LEXICON_FILENAME;

  io::CSVReader<2> in(filename);
  in.read_header(io::ignore_extra_column, "word", "wordId");

  string word;
  uint32_t wordId;

  while (in.read_row(word, wordId)) {
    // lexiconMap[word] = wordId;
    lexiconMap.insert(word, wordId);
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


void getFileIdFromQuery(const string &query, DoublyLinkedList<uint32_t> &fileIds, DoublyLinkedList<string> &words, HashMap<string, uint32_t> &lexiconMap) {
  DoublyLinkedList<string> queryWords;
  splitString(query, ' ', queryWords);

  DoublyLinkedList<string> stemmedQuery;
  for (auto head = queryWords.get_head(); head != nullptr; head = head->next) {
    string word = head->data;
    string stemmedWord;
    stemWord(word, stemmedWord);

    stemmedQuery.push_back(toLower(stemmedWord));
  }

  for (auto head = stemmedQuery.get_head(); head != nullptr; head = head->next) {
    if (lexiconMap.find(head->data)) {
      fileIds.push_back(lexiconMap[head->data]);
      words.push_back(head->data);
    }
  }

}

void loadMetadata(HashMap<uint32_t, ArticleMeta> &metadata) {
  populateMetadata(METADATA_FILENAME, metadata);
}

bool compareTitleWithQuery(const string &articleTitle, DoublyLinkedList<string> words) {
  DoublyLinkedList<string> articleWords;
  splitString(articleTitle, ' ', articleWords);

  int counter = 0;
  for (auto head = words.get_head(); head != nullptr; head = head->next) {
    if (articleWords.find(head->data)) {
      counter++;
    }
  }

  return counter == words.size();
}


void fetchResults(DoublyLinkedList<string> &words, DoublyLinkedList<uint32_t> &wordFileIds, HashMap<uint32_t, ArticleMeta> &metadata) {
  DoublyLinkedList<Set<uint32_t> *> articlesContainer;
  Set<uint32_t> *resultSet = new Set<uint32_t>(SAMPLE_SIZE);


  string line;
  for (auto wordIdHead = wordFileIds.get_head(); wordIdHead != nullptr; wordIdHead = wordIdHead->next) {
    uint32_t wordId = wordIdHead->data;
    // cout << "WordId: " << wordId << endl;

    {
      Set<uint32_t> *articles = new Set<uint32_t>(SAMPLE_SIZE);
      size_t counter = 0;
      io::CSVReader<1, io::trim_chars<' '>, io::double_quote_escape<',', '\"'> > in(INVERTED_INDICES_DIR + to_string(wordId) + ".csv");

      in.read_header(io::ignore_extra_column, "fileId");
      while (in.read_row(line) && ++counter < SAMPLE_SIZE) {
        articles->insert(stoi(line));
      }

      articlesContainer.push_back(articles);
    }

  }

  for (auto articlesContainerHead = articlesContainer.get_head(); articlesContainerHead != nullptr; articlesContainerHead = articlesContainerHead->next) {
    Set<uint32_t> *articles = articlesContainerHead->data;
    size_t length = articles->length;
    Node<uint32_t, bool> **head = articles->getHead();

    for (size_t i = 0; i < length; i++) {
      uint32_t fileId = head[i]->key;
      ArticleMeta article = metadata[fileId];
      // cout << article.title << endl;
      // if (compareTitleWithQuery(article.title, words)) {
      //   resultSet->insert(fileId);
      // }
    }

  }

  Set<uint32_t> **arrToFree = new Set<uint32_t>*[words.size()];
  int counter = 0;

  Set<uint32_t> *s0, *s1;
  bool initiallyTwo = articlesContainer.size() >= 2;
  bool isFirst = true;
  s0 = articlesContainer.pop_front();
  while (isFirst && initiallyTwo && articlesContainer.size() > 0) {
    if (!isFirst)
      resultSet = new Set<uint32_t>(SAMPLE_SIZE);

    s1 = articlesContainer.pop_front();
    Set<uint32_t>::intersection(*s0, *s1, *resultSet);
    s0 = resultSet;
    arrToFree[counter++] = resultSet;

    isFirst = false;
  }

  if (isFirst && !initiallyTwo) {
    resultSet = s0;
  }

  cout << "Result set length: " << resultSet->length << endl;

  Node<uint32_t, bool> **resultSetHead = resultSet->getHead();
  for (size_t i = 0; i < resultSet->length; i++) {
    uint32_t fileId = resultSetHead[i]->key;
    ArticleMeta article = metadata[fileId];
    cout << article.title << endl;
  }

  for (int i = 0; i < counter; i++) {
    delete arrToFree[i];
  }
}

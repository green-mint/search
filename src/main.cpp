#include <iostream>
#include <unordered_map>
#include <hashmap.h>
#include <csv.h>
#include <trie.h>
#include <utils.h>
#include <invertedindex.h>
#include <indexing.h>
#include <linkedlist.h>

using namespace std;

int main() {
  cout << "Hashmap-uh!" << endl;

  cout << "Loading lexicon..." << endl;
  HashMap<string, uint32_t> lexiconMap(LEXICON_SIZE);
  loadLexicon(lexiconMap);

  cout << lexiconMap["short"] << endl;
  cout << lexiconMap["war"] << endl;
  cout << lexiconMap["descript"] << endl;

  // cout << "Loading metadata..." << endl;
  // unordered_map<uint32_t, ArticleMeta> metadata;
  // loadMetadata(metadata);

  // string userQuery;
  // userQuery.reserve(128);
  // cout << "Enter a query: ";
  // getline(cin, userQuery);

  // DoublyLinkedList<uint32_t> fileIds;
  // DoublyLinkedList<string> words;
  // getFileIdFromQuery(userQuery, fileIds, words, lexiconMap);

  // words.print();
  // fileIds.print();

  // // blue balls america mouth
  // // blue -> wordId
  // // balls -> wordId
  // // america -> wordId
  // // mouth -> wordId
  // cin.get();

  // for (auto head = fileIds.get_head(); head != nullptr; head = head->next) {
  //   string filename = INVERTED_INDICES_DIR + to_string(head->data) + ".csv";
  //   ifstream file(filename);

  //   cout << filename << endl << endl;
  //   string line;
  //   while (getline(file, line)) {
  //     cout << line << endl;

  //     //wordId, fileId, frequency, positions
  //     // 1, 1
  //     // 1, 100
  //     // 1, 134
  //     // 1, 113334
  //     // 1, 1212121

  //   }

  //   cin.get();
  //   cin.ignore();
  //   cout << "=============================================" << endl;
  // }
}

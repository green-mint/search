#include <iostream>
#include <unordered_map>
#include <csv.h>
#include <trie.h
#include <utils.h>
#include <invertedindex.h>
#include <indexing.h>
#include <linkedlist.h>

using namespace std;

int main() {
  cout << "Hashmap-uh!" << endl;

  cout << "Loading lexicon..." << endl;
  unordered_map<string, uint32_t> lexiconMap;
  loadLexicon(lexiconMap);

  string userQuery;
  userQuery.reserve(128);
  cout << "Enter a query: ";
  getline(cin, userQuery);

  DoublyLinkedList<uint32_t> fileIds;
  DoublyLinkedList<string> words;
  getFileIdFromQuery(userQuery, fileIds, words, lexiconMap);

  words.print();
  fileIds.print();

  for (auto head = fileIds.get_head(); head != nullptr; head = head->next) {
    string filename = INVERTED_INDICES_DIR + to_string(head->data) + ".csv";
    ifstream file(filename);

    cout << filename << endl << endl;
    string line;
    while (getline(file, line)) {
      cout << line << endl;
    }

    cin.get();
    cout << "=============================================" << endl;
  }
}

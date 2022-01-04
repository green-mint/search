#include <iostream>
#include <unordered_map>
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
  unordered_map<string, int> lexiconMap;
  loadLexicon(lexiconMap);

  string userQuery;
  userQuery.reserve(128);
  cout << "Enter a query: ";
  getline(cin, userQuery);


  DoublyLinkedList<string> queryWords;
  splitString(userQuery, ' ', queryWords);

  cout << "Stemming query..." << endl;
  DoublyLinkedList<string> stemmedQuery;
  for (auto head = queryWords.get_head(); head != nullptr; head = head->next) {
    string word = head->data;
    string stemmedWord;
    stemWord(word, stemmedWord);
    stemmedQuery.push_back(stemmedWord);
  }

  for (auto head = stemmedQuery.get_head(); head != nullptr; head = head->next) {
    if (lexiconMap[head->data])
      cout << head->data << " maps to " << lexiconMap[head->data] << endl;
  }

}

#include <iostream>

#include <hashmap.h>
#include <csv.h>
#include <trie.h>
#include <utils.h>
#include <invertedindex.h>
#include <indexing.h>
#include <linkedlist.h>

using namespace std;

int main()
{
  cout << "Hashmap-uh!" << endl;

  cout << "Loading lexicon..." << endl;
  HashMap<string, uint32_t> lexiconMap(LEXICON_SIZE);
  loadLexicon(lexiconMap);


  cout << "Loading metadata..." << endl;
  HashMap<uint32_t, ArticleMeta> metadata(METADATA_SIZE);
  loadMetadata(metadata);

  string userQuery;
  userQuery.reserve(128);
  cout << "Enter a query: ";
  getline(cin, userQuery);

  DoublyLinkedList<uint32_t> wordFileIds;
  DoublyLinkedList<string> words;
  // lexicon [word] -> wordId
  // short description => wordFileIds = {1, 2}
  getFileIdFromQuery(userQuery, wordFileIds, words, lexiconMap);

  fetchResults(words, wordFileIds, metadata);

  // string suggestionsFor;
  // Trie trie;
  // populateTrie(trie);
  
  // while(1){
  //   cout << "Suggestions for: ";
  //   getline(cin, suggestionsFor);
  //   trie.prefixSearch(trie.root, suggestionsFor);

  // }

  return 0;
}

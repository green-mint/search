#include <iostream>
#include <unordered_map>

#include "../include/csv.h"
#include "../include/trie.h"
#include "../include/utils.h"

using namespace std;

int main() {
  cout << "Hashmap-uh!" << endl;

  // Loading the stopwords
  unordered_map<string, char> stopWords;
  populateStopWords(STOPWORDS_FILENAME, stopWords);

  // Loading the metadata
  unordered_map<string, Article> metadata;
  populateMetadata(METADATA_FILENAME, metadata);

  InvertedIndex invertedIndex;
  populateInvertedIndex(invertedIndex, metadata);
  invertedIndex.print();

  return 0;
}

#include <iostream>
#include <unordered_map>

#include "../include/csv.h"
#include "../include/trie.h"
#include "../include/utils.h"

using namespace std;

#define STOPWORDS_FILENAME "../data/stopwords.csv"
#define METADATA_FILENAME "../data/metadata.csv"

int main() {
  cout << "Hashmap-uh!" << endl;

  // Loading the stopwords 
  unordered_map<string, char> stopWords;
  populateStopWords(STOPWORDS_FILENAME, stopWords);

  std::unordered_map<std::string, char> stopWords;
  if (stopWords["after"])
    cout << "Exists" << endl;
  else
    cout << "Doesn't exist";
  populateStopWords("data/stop_words.csv", stopWords);
  if (stopWords["after"])
    cout << "Exists";
  else
    cout << "Doesn't exist" << endl;


  // Loading the metadata 
  unordered_map<string, Article> metadata;
  populateMetadata(METADATA_FILENAME, metadata);

}

#include <iostream>
#include <unordered_map>
#include "../include/csv.h"
#include "../include/trie.h"
#include "../include/utils.h"


using namespace std;

int main() {
  cout << "Hashmap-uh!" << endl;
  io::CSVReader<3> in("data/sample.csv");
  in.read_header(io::ignore_extra_column, "name", "cms", "snake_level");
  std::string name;
  std::string cms;
  int snake_level;
  while (in.read_row(name, cms, snake_level)) {
    std::cout << name << " " << cms << " " << snake_level << std::endl;
  }

  std::unordered_map<std::string, char> stopWords;
  populateStopWords("data/stop_words.txt", stopWords);

  Trie trie;
  trie.insert("hello");
  trie.insert("world");
  trie.insert("hell");
  trie.insert("he");
  trie.insert("hel");

  cout << "Searched hello: " << trie.search("hello");
  trie.deleteWord("hello");
  cout << "Searched hello: " << trie.search("hello");

  cout << "Searched hell: " << trie.search("hell");
  cout << "Searched her: " << trie.search("her");

  return 0;
}

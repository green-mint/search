#include <csv.h>

#include <iostream>

#include "../include/trie.h"

using namespace std;
int main() {
    cout << "Hashmap-uh!" << endl;

    const unsigned int col_count = 3;
    const char *filename = "data/sample.csv";
    io::CSVReader<col_count> in(filename);

    in.read_header(io::ignore_extra_column, "name", "cms", "snake_level");
    std::string name;
    std::string cms;
    int snake_level;
    while (in.read_row(name, cms, snake_level)) {
        std::cout << name << " " << cms << " " << snake_level << std::endl;
    }

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

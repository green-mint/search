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
    if (stopWords["after"])
        cout << "Exists" << endl;
    else
        cout << "Doesn't exist";
    populateStopWords("data/stop_words.csv", stopWords);
    if (stopWords["after"])
        cout << "Exists";
    else
        cout << "Doesn't exist" << endl;

    return 0;
}

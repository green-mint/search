#include "../include/utils.h"

#include <unordered_map>

#include "../include/csv.h"
using namespace std;

void populateStopWords(const std::string &filename,
                       std::unordered_map<std::string, char> &stopWords) {
    io::CSVReader<1> in(filename.c_str());
    in.read_header(io::ignore_extra_column, "words");

    string words;
    while (in.read_row(words)) {
        stopWords[words] = 'f';
    }
}

#include "../include/utils.h"
#include "../include/csv.h"

void populateStopWords(const std::string &filename, std::unordered_map<std::string, char> &stopWords) {
  io::CSVReader<1> in(filename.c_str());


}

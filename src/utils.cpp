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

void populateMetadata(const string &filename, unordered_map<string, Article> &metadata) {
  io::CSVReader<5> in(filename.c_str());
  // id
  // title
  // path_to_file
  // updated_at
  // another_title
  string id, title, path_to_file, updated_at, another_title;
  in.read_header(io::ignore_extra_column, "id", "title", "path_to_file", "updated_at", "another_title");
  while (in.read_row(id, title, path_to_file, updated_at, another_title)) {
    Article article(id, title, path_to_file, date_from_iso_string(updated_at), another_title);
    metadata[id] = article;
  }
}

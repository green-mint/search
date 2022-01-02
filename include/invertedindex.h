#pragma once 

#include <iostream>
#include <list>
#include <unordered_map>
#include <utils.h>

using namespace std;

class InvertedIndex {
public:
  struct FilesMap;

  void addWord(const string &word, string &fileId, size_t position);
  FilesMap &searchWord(const string &word);
  void deleteWord(const string &word);
  void print();

public:
  struct FilesMap {
    struct WordDetail {
      size_t frequency = 0;
      list<size_t> positions;
    };
    // fileId, WordDetail
    unordered_map<string, WordDetail> files;
  };

private:
  // word, FilesMap
  unordered_map<string, FilesMap> index;
};

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, Article> &metadata);

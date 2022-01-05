#pragma once 

#include <iostream>
#include <list>
#include <unordered_map>
#include <utils.h>

using namespace std;

class InvertedIndex {
public:
  struct FilesMap;

  void addWord(const uint32_t wordId, uint32_t fileId, size_t position);
  FilesMap &searchWord(const uint32_t wordId);
  void deleteWord(const uint32_t wordId);
  void print();
  void writeToFile(const string &filename);

public:
  struct FilesMap {
    struct WordDetail {
      size_t frequency = 0;
      list<size_t> positions;
    };
    // fileId, WordDetail
    unordered_map<uint32_t, WordDetail> files;
  };

  // TODO: Move this down
  unordered_map<uint32_t, FilesMap> index;
private:
  // wordId, FilesMap
};

void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, uint32_t> &lexicon, unordered_map<uint32_t, ArticleMeta> &metadata);

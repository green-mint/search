#pragma once 

#include <list>
#include <iostream>
#include <codecvt>
#include <unordered_map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>
#include "olestem/stemming/english_stem.h"
#include "paths.h"

using namespace std;
using namespace boost::gregorian;
namespace fs = boost::filesystem;

struct Article {
  string id;
  string title;
  string path_to_file;
  date updated_at;

  Article() { }

  Article(string id, string title, string path_to_file, date updated_at) {
    this->id = id;
    this->title = title;
    this->path_to_file = path_to_file;
    this->updated_at = updated_at;
  };
};

class InvertedIndex {
public:
  struct WordMap {
    struct FileMap {
      size_t frequency = 0;
      list<size_t> positions;
    };
    // fileId, fileMap
    unordered_map<string, FileMap> files;
  };

  void addWord(const string &word, string &fileId, size_t position) {
    if (index.find(word) == index.end()) {
      // No such word in the index
      WordMap wordMap;
      index[word] = wordMap;
    }
    // Word exists in the index
    WordMap &wordMap = index[word];
    if (wordMap.files.find(fileId) == wordMap.files.end()) {
      // No such file in the word map
      WordMap::FileMap fileMap;
      fileMap.frequency = 1;
      wordMap.files[fileId] = fileMap;
    }
    else {
      // File exists in the word map
      WordMap::FileMap &fileMap = wordMap.files[fileId];
      fileMap.frequency++;
      fileMap.positions.push_back(position);
    }
  }

  WordMap &searchWord(const string &word) {
    return index[word];
  }

  void deleteWord(const string &word) {
    index.erase(word);
  }

  void print() {
    for (auto it = index.begin(); it != index.end(); ++it) {
      cout << it->first << ": ";
      for (auto it2 = it->second.files.begin(); it2 != it->second.files.end(); ++it2) {
        cout << it2->first << ": " << it2->second.frequency << " ";
      }
      cout << endl;
    }
  }

private:
  // word, WordMap
  unordered_map<string, WordMap> index;
};

void populateStopWords(const string &filename, unordered_map<string, char> &stopWords);
void populateMetadata(const string &filename, unordered_map<string, Article> &metadata);
void populateInvertedIndex(InvertedIndex &invertedIndex, unordered_map<string, Article> &metadata);

void toISODate(std::string &date);

void stemWord(const string &input, string &output);

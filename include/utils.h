#pragma once 

#include <iostream>
#include <codecvt>
#include <unordered_map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <olestem/stemming/english_stem.h>
#include <paths.h>
#include <linkedlist.h>
#include <trie.h>

using namespace std;
using namespace boost::gregorian;

// Article 
struct ArticleMeta {
  string id;
  string title;
  string filename;
  date updated_at;

  ArticleMeta() { }

  ArticleMeta(string id, string title, string filename, date updated_at) {
    this->id = id;
    this->title = title;
    this->filename = filename;
    this->updated_at = updated_at;
  };
};


/**
 *
 * wordId, fileId | ArticleId, frequency, postions[]
 * word -> fildId (1 - to - many)
 */

class Word {

private:
  uint32_t wordId;
  string word;
  // RANDBLACKTRee<Article> articles;

};

void toISODate(string &date);

void stemWord(const string &input, string &output);

void populateTrie(Trie &trie, const unordered_map<string, ArticleMeta> &metadata);

void loadLexicon(unordered_map<string, uint32_t> &lexiconMap);

void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output);

void loadMetadata(unordered_map<string, ArticleMeta> &metadata);

void getFileIdFromQuery(const string &query, DoublyLinkedList<uint32_t> &fileIds, DoublyLinkedList<string> &words, unordered_map<string, uint32_t> &lexiconMap);

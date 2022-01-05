#pragma once 

#include <iostream>
#include <codecvt>
#include <unordered_map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <olestem/stemming/english_stem.h>
#include <paths.h>
#include <linkedlist.h>
#include <hashmap.h>
#include <set.h>
#include <trie.h>

#define LEXICON_SIZE 1300000
#define METADATA_SIZE 22000

#define SAMPLE_SIZE 100

using namespace std;
using namespace boost::gregorian;

// Article 
struct ArticleMeta {
  uint32_t id;
  string title;
  string filename;
  date updated_at;

  ArticleMeta() { }

  ArticleMeta(uint32_t id, string title, string filename, date updated_at) {
    this->id = id;
    this->title = title;
    this->filename = filename;
    this->updated_at = updated_at;
  };
};

void toISODate(string &date);

void stemWord(const string &input, string &output);

void populateTrie(Trie &trie, const unordered_map<uint32_t, ArticleMeta> &metadata);

void loadLexicon(HashMap<string, uint32_t> &lexiconMap);

void loadMetadata(HashMap<uint32_t, ArticleMeta> &metadata);

void getFileIdFromQuery(const string &query, DoublyLinkedList<uint32_t> &fileIds, DoublyLinkedList<string> &words, HashMap<string, uint32_t> &lexiconMap);


void fetchResults(DoublyLinkedList<string> &words, DoublyLinkedList<uint32_t> &wordFileIds, HashMap<uint32_t, ArticleMeta> &metadata);

bool compareTitleWithQuery(const string &articleTitle, DoublyLinkedList<string> words, Set<string> *articleWordsSet, Set<string> *queryWordsSet, Set<string> *intersectionSet);

#pragma once 

#include <list>
#include <iostream>
#include <codecvt>
#include <unordered_map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <olestem/stemming/english_stem.h>
#include <paths.h>
#include <linkedlist.h>

using namespace std;
using namespace boost::gregorian;

struct Article {
  string id;
  string title;
  string filename;
  date updated_at;

  Article() { }

  Article(string id, string title, string filename, date updated_at) {
    this->id = id;
    this->title = title;
    this->filename = filename;
    this->updated_at = updated_at;
  };
};

void toISODate(string &date);

void stemWord(const string &input, string &output);

void loadLexicon(unordered_map<string, int> &lexicon);

void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output);


#pragma once 

#include <list>
#include <iostream>
#include <codecvt>
#include <unordered_map>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/filesystem.hpp>
#include <olestem/stemming/english_stem.h>
#include <paths.h>

using namespace std;
using namespace boost::gregorian;
namespace fs = boost::filesystem;

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


void populateStopWords(const string &filename, unordered_map<string, char> &stopWords);
void populateMetadata(const string &filename, unordered_map<string, Article> &metadata);

void toISODate(std::string &date);

void stemWord(const string &input, string &output);

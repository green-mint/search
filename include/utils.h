#pragma once 

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <unordered_map>

using namespace std;
using namespace boost::gregorian;

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

void populateStopWords(const string &filename, unordered_map<string, char> &stopWords);
void populateMetadata(const string &filename, unordered_map<string, Article> &metadata);

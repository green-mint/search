#pragma once 

#include <iostream>
#include <unordered_map>
#include <utils.h>

using namespace std;

void generateLexicon(const string &filename, unordered_map<string, uint32_t> &lexiconMap, unordered_map<string, char> &stopWords);

void populateStopWords(const string &filename, unordered_map<string, char> &stopWords);

void populateMetadata(const string &filename, unordered_map<string, ArticleMeta> &metadata);

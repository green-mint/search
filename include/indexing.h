#ifndef INDEXING_H
#define INDEXING_H
#include <iostream>
#include <unordered_map>
using namespace std;
void generateLexicon(const string &filename,
                     unordered_map<string, int> &lexiconMap,
                     unordered_map<string, char> &stopWords);
#endif
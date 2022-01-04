#pragma once 

#include <iostream>
#include <unordered_map>

using namespace std;
void generateLexicon(const string &filename, unordered_map<string, uint32_t> &lexiconMap, unordered_map<string, char> &stopWords);

#pragma once 

#include <iostream>

#include <utils.h>

using namespace std;

void generateLexicon(const string &filename, HashMap<string, uint32_t> &lexiconMap, HashMap<string, char> &stopWords);

void populateStopWords(const string &filename, HashMap<string, char> &stopWords);

#pragma once 

#include <iostream>
#include <unordered_map>

void populateStopWords(const std::string &filename, std::unordered_map<std::string, char> &stopWords);

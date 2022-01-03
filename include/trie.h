#ifndef TRIE_H
#define TRIE_H

#include <iostream>
using namespace std;

class TrieNode {
   public:
    bool isEndOfWord;
    TrieNode* children[26];
    ~TrieNode();

    TrieNode();
};

class Trie {
   public:
    TrieNode* root;
    Trie();
    ~Trie();

    void insert(string word);
    bool search(string word);
    bool deleteWord(string word);
    bool isLeafNode(TrieNode* node);
    void prefixSearchHelper(TrieNode* root, string prefix);
    void prefixSearch(TrieNode* root, string prefix);
};

#endif
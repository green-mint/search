#include <trie.h>
#include <iostream>
#include <string>
#include <utils.h>

using namespace std;

TrieNode::TrieNode() {
    isEndOfWord = false;
    for (size_t i = 0; i < 26; i++) {
        children[i] = NULL;
    }
}

TrieNode::~TrieNode() {
    for (size_t i = 0; i < 26; i++) {
        if (children[i] != NULL) {
            delete children[i];
        }
    }
}
Trie::Trie() { root = new TrieNode(); }

Trie::~Trie() { delete root; }

void Trie::insert(string word) {
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

bool Trie::search(string word) {
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            return false;
        }
        curr = curr->children[index];
    }
    return curr->isEndOfWord;
}

bool Trie::startsWith(string prefix) {
    // write this
    return prefix.size() != 0;
}

bool Trie::deleteWord(string word) {
    TrieNode *currNode = root;
    for (size_t i = 0; i < word.length(); i++) {
        int index = word[i] - 'a';
        if (currNode->children[index] != NULL) {
            currNode = currNode->children[index];
        }
        else {
            return false;
        }
    }

    currNode->isEndOfWord = false;
    return true;
}

#include <trie.h>
#include <utils.h>

#include <iostream>
#include <string>

using namespace std;

TrieNode::TrieNode()
{
    isEndOfWord = false;

    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        children[i] = NULL;
    }
}

TrieNode::~TrieNode()
{
    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        if (children[i] != NULL)
        {
            delete children[i];
        }
    }
}
Trie::Trie() { root = new TrieNode(); }

Trie::~Trie() { delete root; }

void Trie::insert(string word,int id)
{
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        int index = word[i] - ' ';
        if (curr->children[index] == NULL)
        {
            curr->children[index] = new TrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
    curr->id = id;
}

int Trie::search(string word)
{
    TrieNode *curr = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        int index = word[i] - ' ';
        if (curr->children[index] == NULL)
        {   

            return -1;
        }
        curr = curr->children[index];
    }
    if(curr->isEndOfWord)
    return curr->id;
    else 
    return -1;
}

bool Trie::deleteWord(string word)
{
    TrieNode *currNode = root;
    for (size_t i = 0; i < word.length(); i++)
    {
        int index = word[i] - ' ';
        if (currNode->children[index] != NULL)
        {
            currNode = currNode->children[index];
        }
        else
        {
            return false;
        }
    }

    currNode->isEndOfWord = false;
    return true;
}

bool Trie::isLeafNode(TrieNode *node)
{
    for (size_t i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        if (node->children[i] != NULL)
        {
            return false;
        }
    }
    return true;
}

void Trie::prefixSearchHelper(TrieNode *root, string prefix)
{
    if (root->isEndOfWord)
    {
        cout << prefix << endl;
    }

    if (isLeafNode(root))
        return;

    for (int i = 0; i < NUMBER_OF_ALPHABETS; i++)
    {
        if (root->children[i])
        {
            prefixSearchHelper(root->children[i], prefix + (char)(i + ' '));
        }
    }
}

void Trie::prefixSearch(TrieNode *root, const string prefix)
{
    {
        TrieNode *currentNode = root;

        for (u_int32_t i = 0; i < prefix.length(); i++)
        {
            int index = prefix[i] - ' ';

            if (!currentNode->children[index])
                return;

            currentNode = currentNode->children[index];
        }

        if (currentNode->isEndOfWord && isLeafNode(currentNode))
        {
            cout << prefix << endl;
            return;
        }
        else if (!isLeafNode(currentNode))
        {
            prefixSearchHelper(currentNode, prefix);
            return;
        }
    }
}
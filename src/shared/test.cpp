#include <test.h>
#include <trie.h>

#include <iostream>

void test_trie() {
       Trie t1;
    t1.insert("butterfly");
    t1.insert("butter");

    t1.insert("buttistan");
    t1.insert("butti");
    t1.insert("baskar");
    t1.insert("asf");

    t1.prefixSearch(t1.root, "as");
}
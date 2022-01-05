#pragma once

#include<iostream>
#include<linkedlist.h>

using namespace std;

string &toLower(string &text);

string &lowerAndRemoveSpace(string &text);

bool checkTitle(string title);

void splitString(const string &input, char delimiter, DoublyLinkedList<string> &output);

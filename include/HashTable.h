#pragma once 

#include <iostream>

#define HASH_TABLE_NULL 0x0

class HashTable {
  struct HashTableNode;
public:
  HashTable(size_t size);

  bool isEmpty();
  bool isFull();
  size_t getLength();

  bool insertItem(const std::string &value);
  bool deleteItem(const std::string &value);
  bool searchItem(const std::string &value);

  uint32_t hash(const char *value);
  void Print();

  ~HashTable();
private:

  struct HashTableNode {
    std::string value;
    HashTableNode *next;

    HashTableNode(const std::string &value = "", HashTableNode *next = nullptr)
      : value(value), next(next) {}
  };


  HashTableNode *table;
  size_t size;
  size_t length;
};

HashTable::HashTable(size_t size) : size(size) {
  table = new HashTableNode[size];
  length = 0;
}

HashTable::~HashTable() {
  delete[] table;
}

bool HashTable::isEmpty() {
  return length == 0;
}

bool HashTable::isFull() {
  return length == size;
}

size_t HashTable::getLength() {
  return length;
}



bool HashTable::insertItem(const std::string &value) {
  if (isFull()) {
    return false;
  }

  size_t index = hash(value.c_str());

  HashTableNode *curr = &table[index];
  while (curr->next != nullptr) {
    if (curr->value == value) {
      return false;
    }
    curr = curr->next;
  }

  if (curr->value == value) {
    return false;
  }

  curr->next = new HashTableNode(value);
  length++;
  return true;
}

bool HashTable::deleteItem(const std::string &value) {
  if (isEmpty()) {
    return false;
  }

  size_t index = hash(value.c_str());

  HashTableNode *curr = &table[index];
  while (curr != nullptr) {
    if (curr->value == value) {
      break;
    }
    curr = curr->next;
  }

  if (curr->next == nullptr) {
    return false;
  }

  HashTableNode *temp = curr->next;
  curr->next = temp->next;
  delete temp;
  length--;
  return true;
}

bool HashTable::searchItem(const std::string &value) {
  if (isEmpty()) {
    return false;
  }

  size_t index = hash(value.c_str());
  HashTableNode *curr = &table[index];
  while (curr->next != nullptr) {
    if (curr->value == value) {
      return true;
    }
    curr = curr->next;
  }

  return false;
}

uint32_t HashTable::hash(const char *str) {
  uint32_t hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash % size;
}

void HashTable::Print() {
  for (size_t i = 0; i < size; i++) {
    std::cout << i << ": ";
    HashTableNode *curr = &table[i];
    while (curr != nullptr) {
      std::cout << curr->value << " -> ";
      curr = curr->next;
    }
    std::cout << std::endl;
  }
}

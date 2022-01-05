#pragma once

#include <iostream>
#include <functional>

template <typename K, typename V>
class Node {
public:
  K key;
  V value;
  Node<K, V> *nextBucketNode;
  Node<K, V> *nextOverallNode;
  Node(K _key, V _value) {
    key = _key;
    value = _value;
    nextBucketNode = NULL;
    nextOverallNode = NULL;
  }
};

template <typename K, typename V>
class Bucket {
public:
  Node<K, V> *head;
  Node<K, V> *tail;

  Bucket() {
    head = NULL;
    tail = NULL;
  }

  ~Bucket() {
    Node<K, V> *curr = head;
    while (curr != NULL) {
      Node<K, V> *next = curr->nextBucketNode;
      delete curr;
      curr = next;
    }
  }
};


template <typename K, typename V>
class HashMap {
public:
  Bucket<K, V> *buckets;
  int numBuckets;
  Node<K, V> **nodes;
  int numNodes;
  std::hash<K> hashFunc;
  std::function<bool(Node<K, V>, Node<K, V>)> cmpFunc;

  HashMap(int _size) {
    buckets = new Bucket<K, V>[_size];
    numBuckets = _size;
    nodes = new Node<K, V>*[numBuckets];
    numNodes = 0;

    cmpFunc = [](Node<K, V> a, Node<K, V> b) {
      return a.key < b.key;
    };
  }

  HashMap(int _size, std::function<bool(Node<K, V>, Node<K, V>)> cmpFunc) {
    buckets = new Bucket<K, V>[_size];
    numBuckets = _size;
    nodes = new Node<K, V>*[numBuckets];
    numNodes = 0;

    this->cmpFunc = cmpFunc;
  }

  ~HashMap() {
    delete[] buckets;
    delete[] nodes;
  }

  // module of the bytes of the key
  int hash(K key) {
    return hashFunc(key) % numBuckets;
  }

  void remove(K key) {
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    Node<K, V> *prev = nullptr;

    while (curr != NULL) {
      if (curr->key == key) {
        if (prev != nullptr) {
          prev->nextBucketNode = curr->nextBucketNode;
        }
        delete curr;
        break;
      }
      prev = curr;
      curr = curr->nextBucketNode;
    }
  }

  void insert(K key, V value) {
    int bucketIndex = hash(key);

    Node<K, V> *newNode = new Node<K, V>(key, value);
    if (buckets[bucketIndex].head == NULL) {
      buckets[bucketIndex].head = newNode;
      buckets[bucketIndex].tail = newNode;
    }
    else {
      buckets[bucketIndex].tail->nextBucketNode = newNode;
      buckets[bucketIndex].tail = newNode;
    }

    nodes[numNodes] = newNode;
    numNodes++;
  }

  bool find(K key) {
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    while (curr != NULL) {
      if (curr->key == key) {
        return true;
      }
      curr = curr->nextBucketNode;
    }
    return false;
  }

  V &get(K key) {
    int bucketIndex = hash(key);
    Node<K, V> *curr = buckets[bucketIndex].head;
    while (curr != NULL) {
      if (curr->key == key) {
        return curr->value;
      }
      curr = curr->nextBucketNode;
    }
  }

  V &operator[](K key) {
    return get(key);
  }


  void sortNodes() {
    for (int i = 0; i < numNodes; i++) {
      for (int j = i + 1; j < numNodes; j++) {
        if (cmpFunc(nodes[i]->key, nodes[j]->key)) {
          Node<K, V> *temp = nodes[i];
          nodes[i] = nodes[j];
          nodes[j] = temp;
        }
      }
    }
  }

  void traverseKeyValuePairs() {
    for (int i = 0; i < numNodes; i++) {
      std::cout << nodes[i]->key << " " << nodes[i]->value << std::endl;
    }
  }

  Node<K, V> **getHead() {
    return nodes;
  }
};

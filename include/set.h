#pragma once 

#include <hashmap.h>
#include <linkedlist.h>


using namespace std;

template <typename T>
class Set {
public:
  int length = 0;
  int size = 0;

  HashMap<T, bool> *hashmap = nullptr;
  Set(int _size = 100) {
    hashmap = new HashMap<T, bool>(_size);
    size = 100;
    length = 0;
  }

  Set(const Set<T> &other) {
    hashmap = new HashMap<T, bool>(other.size);
    size = other.size;
    length = other.length;
    for (int i = 0; i < other.length; i++) {
      hashmap->insert(other.hashmap->get(i), true);
    }
  }

  Set(DoublyLinkedList<T> &list) {
    hashmap = new HashMap<T, bool>(list.size());
    size = list.size();
    length = size;
    for (auto head = list.get_head(); head != nullptr; head = head->next) {
      hashmap->insert(head->data, true);
    }
  }

  void clear() {
    delete hashmap;
    hashmap = new HashMap<T, bool>(size);
    length = 0;
  }

  void insert(const T &value) {
    if (hashmap->find(value))
      return;

    hashmap->insert(value, true);
    ++length;
  }

  bool find(const T &value) {
    return hashmap->find(value);
  }

  T &get(const T &value) {
    return hashmap->get(value);
  }

  void remove(const T &value) {
    hashmap->remove(value);
    length--;
  }

  Node<T, bool> **getHead() {
    return hashmap->getHead();
  }

  void print() {
    Node<T, bool> **head = hashmap->getHead();
    int count = hashmap->numNodes;

    for (int i = 0; i < count; ++i) {
      cout << head[i]->key << ",";
    }
    cout << endl;
  }

  bool operator==(const Set<T> &other) {
    if (length != other.length)
      return false;

    Node<T, bool> **head = hashmap->getHead();
    Node<T, bool> **otherHead = other.hashmap->getHead();
    int count = hashmap->numNodes;

    for (int i = 0; i < count; ++i) {
      if (head[i]->key != otherHead[i]->key)
        return false;
    }
    return true;
  }

  bool operator!=(const Set<T> &other) {
    return !(*this == other);
  }

  ~Set() {
    delete hashmap;
  }

  static void intersection(Set<T> &setA, Set<T> &setB, Set<T> &result) {

    Set<T> &primary = ((setA.length > setB.length) ? setA : setB);
    Set<T> &secondary = ((primary == setA) ? setB : setA);

    Node<T, bool> **nodes = primary.getHead();

    T key;
    for (int i = 0, len = primary.length; i < len; ++i) {
      if (nodes[i] != nullptr) {
        key = nodes[i]->key;
        if (secondary.find(key)) {
          result.insert(key);
        }
      }
    }
  }
};

// template <typename T>
// static Set<T> &Set<T>::intersection(Set<T> setA, set<T> setB) {
//   Node<T, bool> **nodes;
//   Set<T> result(std::max(setA.length, setB.length));

//   Set<T> &primary = setA.length > setB.length ? setA : setB;
//   Set<T> &secondary = primary == setA ? setB : setA;

//   for (int i = 0; i < primary.length; ++i) {
//     if (secondary.find(primary.get(i))) {
//       result.insert(primary.get(i));
//     }
//   }
// }


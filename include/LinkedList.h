#pragma once 

template <typename T>
class DoublyLinkedList {
public:
  struct Node;
  DoublyLinkedList();
  ~DoublyLinkedList();

  void push_front(const T &data);
  void push_back(const T &data);
  T pop_back();
  T pop_front();
  void print();
  size_t size();
  Node *get_head();
  bool find(const T &data);

  struct Node {
    T data;
    Node *next;
    Node *prev;
  };

private:
  Node *head;
  Node *pTail;
  Node *tail;
  size_t length;
};


template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
  head = nullptr;
  tail = nullptr;
  pTail = nullptr;
  length = 0;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr = curr->next;
    delete temp;
  }
}

template <typename T>
bool DoublyLinkedList<T>::find(const T &data) {
  Node *curr = head;
  while (curr != nullptr) {
    if (curr->data == data)
      return true;
    curr = curr->next;
  }
  return false;
}


template <typename T>
void DoublyLinkedList<T>::push_front(const T &data) {
  Node *newNode = new Node;
  newNode->data = data;
  newNode->next = head;
  newNode->prev = nullptr;
  if (head != nullptr) {
    head->prev = newNode;
  }
  head = newNode;
  if (pTail == nullptr) {
    pTail = newNode;
  }
  length++;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &data) {
  Node *newNode = new Node;
  newNode->data = data;
  newNode->next = nullptr;
  newNode->prev = pTail;
  if (pTail != nullptr) {
    pTail->next = newNode;
  }
  pTail = newNode;
  if (head == nullptr) {
    head = newNode;
  }
  length++;
}


template <typename T>
T DoublyLinkedList<T>::pop_back() {
  if (pTail == nullptr) {
    return T();
  }

  Node *temp = pTail;
  T temp2 = pTail->data;
  pTail = pTail->prev;
  if (pTail != nullptr) {
    pTail->next = nullptr;
  }

  length--;
  delete temp;
  return temp2;
}

template <typename T>
T DoublyLinkedList<T>::pop_front() {
  if (head == nullptr) {
    return T();
  }

  Node *temp = head;
  T temp2 = head->data;

  head = head->next;
  if (head != nullptr) {
    head->prev = nullptr;
  }
  // delete temp;
  length--;
  delete temp;
  return temp2;
}


template <typename T>
void DoublyLinkedList<T>::print() {
  Node *curr = head;
  while (curr != nullptr) {
    std::cout << curr->data << " -> ";
    curr = curr->next;
  }
  std::cout << std::endl;
}

template <typename T>
size_t DoublyLinkedList<T>::size() {
  return length;
}

template <typename T>
typename DoublyLinkedList<T>::Node *DoublyLinkedList<T>::get_head() {
  return head;
}

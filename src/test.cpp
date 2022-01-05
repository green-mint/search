#include <iostream>
#include <linkedlist.h>

using namespace std;

struct Article {
  string name;
};

int main() {
  DoublyLinkedList<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_back(5);
  list.push_back(6);
  list.print();

  list.pop_back();
  list.print();

  list.pop_front();
  list.pop_front();
  list.pop_front();
  list.pop_front();
  list.pop_front();
  list.pop_front();
  cout << "Szie" << list.size() << endl;
  list.print();
}

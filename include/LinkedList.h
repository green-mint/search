#pragma once 

#include <iostream>

class SinglyLinkedList
{
  class ListNode;

public:
  // Constructor, initializes all the values to 0/nullptr
  SinglyLinkedList()
    : m_head(nullptr), m_tail(nullptr), m_length(0), m_loc(nullptr), m_prevLoc(nullptr) {}

  // Searches the list for the value and if it finds it sets the m_loc = to the node and m_prevLoc = to the previous node
  void Search(int value)
  {
    // For the head node, m_loc = head, and m_prevLoc = nullptr
    m_loc = m_head;
    m_prevLoc = nullptr;

    // While the list doesn't end and the value contained in the node is less than the value since it's a sorted list
    while (m_loc != nullptr && m_loc->m_data < value)
    {
      m_prevLoc = m_loc;
      m_loc = m_loc->m_next;
    }

    // If the value is not found, set m_loc = nullptr
    if (m_loc != nullptr && m_loc->m_data > value)
    {
      m_loc = nullptr;
    }
  }

  // Returns whether the length of the list is 0 or not
  bool IsEmpty()
  {
    return m_length == 0;
  }

  // Inserts a the value at the logical position of the list
  void InsertSorted(int value)
  {
    // Searches the list for the value
    Search(value);

    // m_loc != nullptr, then the value is already in the list, therefore insetion can not be made
    if (m_loc != nullptr)
    {
      std::cout << "A node with value " << value << " already exists in the list." << std::endl;
      return;
    }

    // If the m_prevLoc == nullptr, then the insertion is at the head of the list
    if (m_prevLoc == nullptr)
    {
      m_loc = m_head;
    }

    // Inserts the value according to the prev, next and data provided
    Insert(value, m_prevLoc, m_loc);
  }

  // Inserts a node at the the front of the list
  void InsertAtFront(int value)
  {
    //Searches for a certain value in the list
    Search(value);

    // Value isn't present
    if (m_loc != nullptr)
    {
      std::cout << "A node with value " << value << " already exists in the list." << std::endl;
      return;
    }

    // As for head the m_prevLoc is nullptr and the next is always the current head of the list
    Insert(value, nullptr, m_head);
  }

  // Inserts a node at the end of the list
  void InsertAtEnd(int value)
  {
    // Searches for a particular value in the list
    Search(value);

    // Value isn't present
    if (m_loc != nullptr)
    {
      std::cout << "A node with value " << value << " already exists in the list." << std::endl;
      return;
    }

    // PrevLoc is always the tail of the list, and the next is always nullptr
    Insert(value, m_prevLoc, nullptr);
  }

  void Delete(int value)
  {
    // Searches for a particular value in the list
    Search(value);

    // Value not found
    if (m_loc == nullptr)
    {
      std::cout << "A node with value " << value << " not found in the list." << std::endl;
      return;
    }

    // If the node is the head, then the next node is the new head
    if (m_prevLoc == nullptr)
    {
      ListNode *next = m_loc->m_next;
      delete m_head;
      m_head = next;
    }
    // Else deletes in the middle
    else
    {
      m_prevLoc->m_next = m_loc->m_next;
      if (m_loc == m_tail)
      {
        m_tail = m_prevLoc;
      }
      delete m_loc;
    }

    // Decrementing the length
    m_length--;
  }

  // Prints the list
  void PrintList()
  {
    ListNode *curr = m_head;
    bool hasNext;

    for (;;)
    {
      hasNext = curr->m_next != nullptr;

      std::cout << curr->m_data << (hasNext ? " -> " : " ");
      curr = curr->m_next;

      if (!hasNext)
      {
        break;
      }
    }
    std::cout << std::endl;
    std::cout << "Length: " << m_length << std::endl;
  }

  // Destroys the list and frees all the memory
  void DestroyList()
  {
    ListNode *curr = m_head;
    ListNode *temp;

    while (curr != nullptr)
    {
      temp = curr->m_next;
      delete curr;

      curr = temp;
    }
  }

  // Reverses a linked List
  void Reverse()
  {
    ListNode *initialHead = m_head;
    ListNode *curr = m_head;
    ListNode *prev = nullptr;
    for (;;)
    {
      if (curr != nullptr)
      {
        ListNode *next = curr->m_next;
        curr->m_next = prev;

        prev = curr;
        curr = next;
      }
      else
      {
        break;
      }
    }
    m_head = prev;
    m_tail = initialHead;
  }

  // Destructor
  ~SinglyLinkedList()
  {
    // It just calls the DestroyList method
    DestroyList();
  }

private:
  // The ListNode class
  class ListNode
  {
  public:
    int m_data = 0;
    ListNode *m_next = nullptr;

    // Overloaded constructors
    ListNode() : m_data(0), m_next(nullptr) {}
    ListNode(int data) : m_data(data) {}
    ListNode(int data, ListNode *next) : m_data(data), m_next(next) {}
  };

  ListNode *m_head;
  ListNode *m_tail;
  uint32_t m_length;

  // Used by the Search method
  ListNode *m_loc;
  ListNode *m_prevLoc;

  // Private method used internally for inserting a node
  void Insert(int data, ListNode *prev, ListNode *next)
  {
    ListNode *newNode = new ListNode(data, next);

    // While inserting at the head
    if (prev == nullptr)
    {
      m_head = newNode;
    }
    else
      // Inserts in the middle
    {
      prev->m_next = newNode;
    }

    // If the next node is nullptr, then the new node is the tail
    if (next == nullptr || prev == m_tail)
    {
      m_tail = newNode;
    }

    // Increments the length
    m_length++;
  }
};

#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <stdlib.h>

#include <iostream>

template <typename T>
class List {
 private:
  struct Node {
    Node* next;
    Node* prev;
    T data;
    Node(const T& d = T{}, Node* p = nullptr, Node* n = nullptr)
        : data{d}, prev{p}, next{n} {}
  };

 public:
  List() : m_size{0}, head{nullptr}, tail{nullptr} {}

  ~List() { clear(); }

  size_t size() const { return m_size; }
  bool empty() const { return size() == 0; }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  void push_front(const T& item) {
    Node* newNode = new Node(item, nullptr, head);

    if (head != nullptr) {
      head->prev = newNode;
    } else {
      // If the list was empty, the new node is also the tail
      tail = newNode;
    }

    head = newNode;
    ++m_size;
  }

  void push_back(const T& item) {
    if (empty()) {
      push_front(item);
      return;
    }

    Node* newNode = new Node(item, tail, nullptr);
    tail->next = newNode;
    tail = newNode;
    ++m_size;
  }

  void pop_front() {
    if (empty()) return;

    Node* temp = head;
    head = head->next;

    if (head != nullptr) {
      head->prev = nullptr;
    } else {
      // If the list becomes empty, update tail as well
      tail = nullptr;
    }

    delete temp;
    --m_size;
  }

  void pop_back() {
    if (empty()) return;

    Node* temp = tail;

    // If only one element
    if (head == tail) {
      head = tail = nullptr;
    } else {
      tail = tail->prev;
      tail->next = nullptr;
    }

    delete temp;
    --m_size;
  }

  void insertAt(const T& item, size_t pos) {
    // Special case for inserting at the front
    if (pos == 0 || empty()) {
      push_front(item);
      return;
    }

    // If position is beyond the list size, insert at the end
    if (pos >= m_size) {
      push_back(item);
      return;
    }

    // Determine which end to start traversal from for more efficiency
    Node* current;
    if (pos <= m_size / 2) {
      // Start from head if position is in the first half
      current = head;
      for (size_t i = 0; i < pos - 1; ++i) {
        current = current->next;
      }
    } else {
      // Start from tail if position is in the second half
      current = tail;
      for (size_t i = m_size - 1; i > pos; --i) {
        current = current->prev;
      }
      current = current->prev;  // One more step back to get the node before our
                                // insertion point
    }

    // Insert the new node between current and current->next
    Node* newNode = new Node(item, current, current->next);
    current->next->prev = newNode;
    current->next = newNode;
    ++m_size;
  }

  friend std::ostream& operator<<(std::ostream& out, const List<T>& list) {
    typename List<T>::Node* current = list.head;
    while (current) {
      out << current->data;
      if (current->next) out << " -> ";
      current = current->next;
    }
    return out;
  }

  T& operator[](size_t index) {
    size_t i = 0;
    if (index >= size() || index < 0) {
      throw std::out_of_range("Out of bounds");
    }

    Node* temp = head;
    while (i < index) {
      temp = temp->next;
      ++i;
    }

    return temp->data;
  }

  T operator[](size_t index) const {
    size_t i = 0;
    if (index > size() || index < 0) {
      throw std::out_of_range("Out of bounds");
    }

    Node* temp = head;
    while (i < index) {
      temp = temp->next;
      ++i;
    }

    return temp->data;
  }

 private:
  size_t m_size;
  Node* head;
  Node* tail;
};

#endif
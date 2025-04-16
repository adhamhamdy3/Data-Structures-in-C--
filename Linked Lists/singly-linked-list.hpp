#ifndef SINGLY_LINKED_LIST
#define SINGLY_LINKED_LIST

#include <stdlib.h>

#include <iostream>

template <typename T>
class List {
 private:
  struct Node {
    Node* next;
    T data;
    Node(const T& d = T{}, Node* n = nullptr) : data{d}, next{n} {}
  };

 public:
  List() : m_size{0}, head{nullptr} {}

  ~List() { clear(); }

  size_t size() const { return m_size; }
  bool empty() const { return size() == 0; }

  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  void push_front(const T& item) {
    head = new Node(item, head);
    ++m_size;
  }

  void push_back(const T& item) {
    if (empty()) {
      push_front(item);
      return;
    }

    Node* temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = new Node(item);
    ++m_size;
  }

  void pop_front() {
    if (empty()) return;

    Node* temp = head;
    head = head->next;
    delete temp;
    --m_size;
  }

  void pop_back() {
    if (empty()) return;

    // If only one element
    if (head->next == nullptr) {
      delete head;
      head = nullptr;
      --m_size;
      return;
    }

    // Find the second-to-last node
    Node* temp = head;
    while (temp->next->next) {
      temp = temp->next;
    }

    // Delete the last node and update pointers
    delete temp->next;
    temp->next = nullptr;
    --m_size;
  }

  void remove(const T& item) {
    if (empty()) {
      return;
    }

    if (head->data == item) {
      pop_front();
      return;
    }

    Node* prev = head;
    Node* current = prev->next;

    while (current != nullptr && current->data != item) {
      prev = current;
      current = current->next;
    }

    if (current != nullptr) {
      prev->next = current->next;
      delete current;
      --m_size;
    }
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

    Node* current = head;
    size_t index = 0;

    while (current != nullptr && index < pos - 1) {
      current = current->next;
      ++index;
    }

    if (current != nullptr) {
      current->next = new Node(item, current->next);
      ++m_size;
    }
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
};

#endif
#ifndef LL_STACK_H
#define LL_STACK_H

#include <stdexcpt.h>

#include <utility>

template <typename T>
class LL_Stack {
 private:
  struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(T&& value) : data(std::move(value)), next(nullptr) {}
  };
  Node* top_node;
  size_t m_size;

 public:
  LL_Stack() : top_node{}, m_size{0} {}

  ~LL_Stack() { clear(); }

  // Copy Constructor
  LL_Stack(const LL_Stack& other) : top_node{nullptr}, m_size{0} {
    if (other.empty()) {
      return;
    }

    T* temp = new T[other.m_size];
    size_t count = 0;

    Node* current = other.top_node;

    while (current != nullptr) {
      temp[other.m_size - count - 1] = current->data;
      current = current->next;
      ++count;
    }

    for (size_t i = 0; i < other.m_size; i++) {
      push(temp[i]);
    }

    delete[] temp;
  }

  // Move constructor
  LL_Stack(LL_Stack&& other) : top_node(other.top_node), m_size(other.m_size) {
    other.top_node = nullptr;
    other.m_size = 0;
  }

  // Copy assignment operator
  LL_Stack& operator=(const LL_Stack& other) {
    if (this != &other) {
      LL_Stack temp(other);
      std::swap(top_node, temp.top_node);
      std::swap(m_size, temp.m_size);
    }
    return *this;
  }

  // Move assignment operator
  LL_Stack& operator=(LL_Stack&& other) {
    if (this != &other) {
      clear();
      top_node = other.top_node;
      m_size = other.m_size;
      other.top_node = nullptr;
      other.m_size = 0;
    }
    return *this;
  }

  void push(const T& item) {
    Node* newNode = new T(item);
    newNode->next = top_node;
    top_node = newNode;
    ++m_size;
  }

  // push with move semantics
  void push(T&& item) {
    Node* newNode = new Node(std::move(item));
    newNode->next = top_node;
    top_node = newNode;
    ++m_size;
  }

  void pop() {
    Node* temp = top_node;
    top_node = top_node->next;
    delete temp;
    m_size--;
  }

  T& top() {
    if (empty()) {
      throw std::out_of_range("can not access top of an empty stack");
    }
    return top_node->data;
  }

  const T& top() const {
    if (empty()) {
      throw std::out_of_range("Cannot access top of an empty stack");
    }
    return top_node->data;
  }

  bool empty() const { return top_node == nullptr; }

  size_t size() const { return m_size; }

  void clear() {
    while (!empty()) {
      pop();
    }
  }
};

#endif
#ifndef LL_QUEUE_H
#define LL_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class LL_Queue {
 private:
  struct Node {
    T data;
    Node* next;

    Node(const T& value) : data(value), next(nullptr) {}
    Node(T&& value) : data(std::move(value)), next(nullptr) {}
  };

 public:
  // Constructor
  LL_Queue() : front_node{nullptr}, rear_node{nullptr}, m_size{0} {}

  ~LL_Queue() { clear(); }

  LL_Queue(const LL_Queue& other)
      : front_node{nullptr}, rear_node{nullptr}, m_size{0} {
    if (other.empty()) {
      return;
    }

    Node* current = other.front_node;
    while (current) {
      enqueue(current->data);
      current = current->next;
    }
  }

  // Move Constructor
  LL_Queue(LL_Queue&& other)
      : front_node{other.front_node},
        rear_node{other.rear_node},
        m_size{other.m_size} {
    other.front_node = nullptr;
    other.rear_node = nullptr;
    other.m_size = 0;
  }

  // Copy assignment operator
  LL_Queue& operator=(const LL_Queue& other) {
    if (this != &other) {
      LL_Queue temp(other);
      std::swap(front_node, other.front_node);
      std::swap(rear_node, other.rear_node);
      std::swap(m_size, other.m_size);
    }

    return *this;
  }

  // Move assignment operator
  LL_Queue& operator=(LL_Queue&& other) {
    if (this != &other) {
      clear();
      front_node = other.front_node;
      rear_node = other.rear_node;
      m_size = other.m_size;

      other.front_node = nullptr;
      other.rear_node = nullptr;
      other.m_size = 0;
    }

    return *this;
  }

  // enqueue
  void enqueu(const T& item) {
    Node* new_node = new T(item);
    if (empty()) {
      front_node = rear_node = new_node;
    } else {
      rear_node->next = new_node;
      rear_node = new_node;
    }

    ++m_size;
  }

  // enqueue with move semantics
  void enqueu(T&& item) {
    Node* new_node = new Node(std::move(item));
    if (empty()) {
      front_node = rear_node = new_node;
    } else {
      rear_node->next = new_node;
      rear_node = new_node;
    }

    ++m_size;
  }

  // dequeue
  void dequeue() {
    if (empty()) {
      throw std::out_of_range("can not access front of empty queue");
    }

    Node* temp = front_node;
    front_node = front_node->next;

    // in case of queue has only one element
    if (front_node == nullptr) {
      rear_node = nullptr;
    }

    delete temp;
    --m_size;
  }

  T& front() {
    if (empty()) {
      throw std::out_of_range("can not access front of empty queue");
    }

    return front_node->data;
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("can not access front of empty queue");
    }

    return front_node->data;
  }

  bool empty() const { return front_node == nullptr; }

  size_t size() const { return m_size; }

  void clear() {
    while (!empty()) {
      dequeue();
    }
  }

 private:
  Node* front_node;
  Node* rear_node;
  size_t m_size;
};

#endif
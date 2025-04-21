#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H

#include <iostream>
#include <stdexcept>
#include <utility>

template <typename T>
class Queue {
 public:
  explicit Queue(size_t intial_capacity = 10)
      : front_index{0}, rear_index{0}, capacity{intial_capacity}, m_size{0} {
    array = new T[capacity];
  }

  ~Queue() { delete[] array; }

  // Copy Constructor
  Queue(const Queue& other)
      : front_index{other.front_index},
        rear_index{other.rear_index},
        capacity{other.capacity},
        m_size{other.m_size} {
    array = new T[capacity];

    for (size_t i = 0; i < m_size; i++) {
      array[i] = other.array[i];
    }
  }

  // Move Constructor
  Queue(Queue&& other)
      : front_index{other.front_index},
        rear_index{other.rear_index},
        capacity{other.capacity},
        m_size{other.m_size} {
    other.array = nullptr;
    other.front_index = 0;
    other.rear_index = 0;
    other.capacity = 0;
    other.m_size = 0;
  }

  // Copy assignment operator
  Queue& operator=(const Queue& other) {
    if (this != &other) {
      Queue temp(other);
      std::swap(array, temp.array);
      std::swap(front_index, temp.front_index);
      std::swap(rear_index, temp.rear_index);
      std::swap(capacity, temp.capacity);
      std::swap(m_size, temp.m_size);
    }
    return *this;
  }

  // Move assignment operator
  Queue& operator=(Queue&& other) {
    if (this != &other) {
      delete[] array;
      array = other.array;
      front_index = other.front_index;
      rear_index = other.rear_index;
      capacity = other.capacity;
      m_size = other.m_size;

      other.array = nullptr;
      other.front_index = 0;
      other.rear_index = 0;
      other.capacity = 0;
      other.m_size = 0;
    }
    return *this;
  }

  // enqueue
  void enqueue(const T& item) {
    if (full()) {
      resize(capacity * 2);
    }

    if (!empty()) {
      rear_index = (rear_index + 1) % capacity;
    }

    array[rear_index] = item;
    m_size++;
  }

  // enqueue with move semantics
  void enqueue(T&& item) {
    if (full()) {
      resize(capacity * 2);
    }

    if (!empty()) {
      rear_index = (rear_index + 1) % capacity;
    }

    array[rear_index] = std::move(item);
    m_size++;
  }

  // dequeue
  void dequeue() {
    if (empty()) {
      throw std::out_of_range("can not dequeue from empty queue");
    }
    if (!empty()) {
      front_index = (front_index + 1) % capacity;
    }

    // shrink the array if it's too large
    if (m_size > 0 && m_size < capacity / 4) {
      resize(capacity / 2);
    }

    m_size--;
  }

  T& front() {
    if (empty()) {
      throw std::out_of_range("can not dequeue from empty queue");
    }
    return array[front_index];
  }

  const T& front() const {
    if (empty()) {
      throw std::out_of_range("can not dequeue from empty queue");
    }
    return array[front_index];
  }

  size_t size() const { return m_size; }

  bool empty() const { return size() == 0; }

  void clear() {
    delete[] array;

    front_index = 0;
    rear_index = 0;
    capacity = 0;
    m_size = 0;
  }

 private:
  T* array;
  size_t front_index;
  size_t rear_index;
  size_t capacity;
  size_t m_size;

  void resize(size_t new_capacity) {
    T* new_array = new T[new_capacity];

    for (size_t i = 0; i < m_size; i++) {
      size_t index = (i + front_index) % capacity;
      new_array[i] = std::move(array[index]);
    }

    delete[] array;
    array = new_array;
    rear_index = m_size > 0 ? m_size - 1 : 0;
    capacity = new_capacity;
  }

  bool full() const { return m_size == capacity; }
};

#endif

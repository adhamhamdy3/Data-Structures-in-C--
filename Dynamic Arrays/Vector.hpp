#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

#include <algorithm>

template <typename T>
class Vector {
 public:
  explicit Vector(size_t initSize = 0)
      : m_size{initSize}, m_capacity{initSize + SPARE_CAPACITY} {
    data = new T[m_capacity];
  }

  Vector(const Vector& rhs)
      : m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, data{nullptr} {
    data = new T[m_capacity];
    for (size_t i = 0; i < m_size; i++) {
      data[i] = rhs.data[i];
    }
  }

  Vector& operator=(const Vector& rhs) {
    Vector copy = rhs;
    std::swap(*this, copy);
    return *this;
  }

  ~Vector() {
    delete[] data;
    data = nullptr;
  }

  // Move semantics (added for modern C++)
  Vector(Vector&& rhs)
      : m_size{rhs.m_size}, m_capacity{rhs.m_capacity}, data{rhs.data} {
    rhs.data = nullptr;
    rhs.m_size = 0;
    rhs.m_capacity = 0;
  }

  Vector& operator=(Vector&& rhs) {
    std::swap(m_size, rhs.m_size);
    std::swap(m_capacity, rhs.m_capacity);
    std::swap(data, rhs.data);
    return *this;
  }

  // Accessors
  bool empty() const { return size() == 0; }
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; }

  T& operator[](size_t index) const { return data[index]; }

  // Modifiers

  void reserve(int newCapacity) {
    if (newCapacity < m_size) return;

    T* newArray = new T[newCapacity];

    for (size_t i = 0; i < m_size; i++) {
      newArray[i] = std::move(data[i]);
    }

    m_capacity = newCapacity;
    std::swap(data, newArray);
    delete[] newArray;
  }

  void push_back(const T& newValue) {
    if (m_size == m_capacity) {
      reserve(2 * m_capacity + 1);
    }
    data[m_size++] = newValue;
  }

  void push_back(T&& newValue) {
    if (m_size == m_capacity) {
      reserve(2 * m_capacity + 1);
    }
    data[m_size++] = std::move(newValue);
  }

  void pop_back() { --m_size; }

  T& front() const { return data[0]; };
  T& back() const { return data[m_size - 1]; }

  void clear() { m_size = 0; }

  void insert(const T& value, size_t place) {
    

  }

  void remove() {}

  static const size_t SPARE_CAPACITY = 16;

 private:
  size_t m_size;
  size_t m_capacity;
  T* data;
};

#endif
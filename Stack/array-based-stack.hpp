#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdlib.h>

#include <stdexcept>
#include <utility>

template <typename T>
class ArrayStack {
 public:
  explicit ArrayStack(size_t initial_capacity = 10)
      : capacity(initial_capacity), top_index(0) {
    array = new T[capacity];
  }

  ~ArrayStack() { delete[] array; }

  // Copy constructor
  ArrayStack(const ArrayStack& other)
      : capacity(other.capacity), top_index(other.top_index) {
    array = new T[capacity];
    for (size_t i = 0; i < top_index; i++) {
      array[i] = other.array[i];
    }
  }

  // Move constructor
  ArrayStack(ArrayStack&& other) noexcept
      : array(other.array),
        capacity(other.capacity),
        top_index(other.top_index) {
    other.array = nullptr;
    other.capacity = 0;
    other.top_index = 0;
  }

  // Copy assignment operator
  ArrayStack& operator=(const ArrayStack& other) {
    if (this != &other) {
      ArrayStack temp(other);
      std::swap(array, temp.array);
      std::swap(capacity, temp.capacity);
      std::swap(top_index, temp.top_index);
    }
    return *this;
  }

  // Move assignment operator
  ArrayStack& operator=(ArrayStack&& other) noexcept {
    if (this != &other) {
      delete[] array;
      array = other.array;
      capacity = other.capacity;
      top_index = other.top_index;
      other.array = nullptr;
      other.capacity = 0;
      other.top_index = 0;
    }
    return *this;
  }

  void push(const T& value) {
    if (top_index >= capacity) {
      resize(capacity * 2);
    }

    array[top_index++] = value;
  }

  // Push with move semantics
  void push(T&& value) {
    if (top_index >= capacity) {
      resize(capacity * 2);
    }

    array[top_index++] = std::move(value);
  }

  void pop() {
    if (isEmpty()) {
      throw std::out_of_range("Cannot pop from an empty stack");
    }

    --top_index;

    // Shrink the array if it's too large
    if (top_index > 0 && top_index < capacity / 4) {
      resize(capacity / 2);
    }
  }

  T& top() {
    if (isEmpty()) {
      throw std::out_of_range("can not access top of an empty stack");
    }
    return array[top_index - 1];
  }

  const T& top() const {
    if (isEmpty()) {
      throw std::out_of_range("can not access top of an empty stack");
    }
    return array[top_index - 1];
  }

  bool isEmpty() const { return top_index == 0; }

  size_t size() const { return top_index; }

  void clear() { top_index = 0; }

 private:
  T* array;
  size_t capacity;
  size_t top_index;

  // Resize the array when it's full
  void resize(size_t new_capacity) {
    T* new_array = new T[new_capacity];

    // Copy elements to the new array
    for (size_t i = 0; i < top_index; i++) {
      new_array[i] = std::move(array[i]);
    }

    delete[] array;
    array = new_array;
    capacity = new_capacity;
  }
};

#endif
#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdlib.h>

template <typename T>
class BinarySearchTree {
 private:
  struct Node {
    T data;
    Node* left;
    Node* right;

    Node(const T& value) : data{value}, left{nullptr}, right{nullptr} {}
  };

  Node* root;

  // Helper Functions
  void destroyRecursive(Node* node);
  Node* insertRecursive(Node* node, const T& value);
  Node* findMinNode(Node* node) const;
  Node* removeRecursive(Node* node, const T& value);
  void inOrderTraversalRecursive(Node* node, void (*visit)(const T&)) const;
  Node* copyRecursive(const Node* node);
  bool containsRecursive(Node* node, const T& value) const;
  size_t sizeRecursive(Node* node) const;
  size_t heightRecursive(Node* node) const;

 public:
  // Constructor and destructor
  BinarySearchTree() : root(nullptr) {}

  // Copy constructor
  BinarySearchTree(const BinarySearchTree<T>& other);

  // Assignment operator
  BinarySearchTree<T>& operator=(const BinarySearchTree<T>& other);

  // Destructor
  ~BinarySearchTree();

  // Core BST operations
  void insert(const T& value);
  void remove(const T& value);
  bool contains(const T& value) const;

  // Additional operations
  bool isEmpty() const;
  size_t size() const;
  size_t height() const;
  T findMin() const;
  T findMax() const;
  void clear();

  // Traversal
  void inOrderTraversal(void (*visit)(const T&)) const;
};

// Copy constructor
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other)
    : root(nullptr) {
  root = copyRecursive(other.root);
}

// Copy helper
template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::copyRecursive(
    const Node* node) {
  if (node == nullptr) {
    return nullptr;
  }

  Node* newNode = new Node(node->data);
  newNode->left = copyRecursive(node->left);
  newNode->right = copyRecursive(node->right);

  return newNode;
}

// Assignment operator
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(
    const BinarySearchTree<T>& other) {
  if (this != &other) {
    // Clear existing tree
    clear();

    // Copy the other tree
    root = copyRecursive(other.root);
  }
  return *this;
}

// Destructor
template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  clear();
}

// Clear the tree
template <typename T>
void BinarySearchTree<T>::clear() {
  destroyRecursive(root);
  root = nullptr;
}

// Helper method to destroy the tree recursively
template <typename T>
void BinarySearchTree<T>::destroyRecursive(Node* node) {
  if (node != nullptr) {
    destroyRecursive(node->left);
    destroyRecursive(node->right);
    delete node;
  }
}

// Insert a value into the tree
template <typename T>
void BinarySearchTree<T>::insert(const T& value) {
  root = insertRecursive(root, value);
}

// Helper method to insert recursively
template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::insertRecursive(
    Node* node, const T& value) {
  if (node == nullptr) {
    return new Node(value);
  }

  if (value < node->data) {
    node->left = insertRecursive(node->left, value);
  } else if (value > node->data) {
    node->right = insertRecursive(node->right, value);
  }
  // If value is equal, we can either ignore or update
  // Here we choose to ignore duplicates

  return node;
}

// Check if the tree contains a value
template <typename T>
bool BinarySearchTree<T>::contains(const T& value) const {
  return containsRecursive(root, value);
}

// Helper method to check recursively
template <typename T>
bool BinarySearchTree<T>::containsRecursive(Node* node, const T& value) const {
  if (node == nullptr) {
    return false;
  }

  if (value == node->data) {
    return true;
  } else if (value < node->data) {
    return containsRecursive(node->left, value);
  } else {
    return containsRecursive(node->right, value);
  }
}

// Remove a value from the tree
template <typename T>
void BinarySearchTree<T>::remove(const T& value) {
  if (isEmpty()) {
    return;
  }

  if (!contains(value)) {
    return;
  }

  root = removeRecursive(root, value);
}

// Helper method to find the minimum node
template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::findMinNode(
    Node* node) const {
  if (node == nullptr) {
    return nullptr;
  }

  while (node->left != nullptr) {
    node = node->left;
  }

  return node;
}

// Helper method to remove recursively
template <typename T>
typename BinarySearchTree<T>::Node* BinarySearchTree<T>::removeRecursive(
    Node* node, const T& value) {
  if (node == nullptr) {
    return nullptr;
  }

  if (value < node->data) {
    node->left = removeRecursive(node->left, value);
  } else if (value > node->data) {
    node->right = removeRecursive(node->right, value);
  } else {
    // Node with the value found, handle 3 cases

    // Case 1: Node with no children (leaf)
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      return nullptr;
    }
    // Case 2: Node with one child
    else if (node->left == nullptr) {
      Node* temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      Node* temp = node->left;
      delete node;
      return temp;
    }
    // Case 3: Node with two children
    else {
      // Find the inorder successor (smallest node in right subtree)
      Node* successor = findMinNode(node->right);

      // Copy the successor's data to this node
      node->data = successor->data;

      // Delete the successor
      node->right = removeRecursive(node->right, successor->data);
    }
  }

  return node;
}

// Check if the tree is empty
template <typename T>
bool BinarySearchTree<T>::isEmpty() const {
  return root == nullptr;
}

// Get the size of the tree
template <typename T>
size_t BinarySearchTree<T>::size() const {
  return sizeRecursive(root);
}

// Helper method to calculate size recursively
template <typename T>
size_t BinarySearchTree<T>::sizeRecursive(Node* node) const {
  if (node == nullptr) {
    return 0;
  }

  return 1 + sizeRecursive(node->left) + sizeRecursive(node->right);
}

// Get the height of the tree
template <typename T>
size_t BinarySearchTree<T>::height() const {
  return heightRecursive(root);
}

// Helper method to calculate height recursively
template <typename T>
size_t BinarySearchTree<T>::heightRecursive(Node* node) const {
  if (node == nullptr) {
    return 0;
  }

  size_t leftHeight = heightRecursive(node->left);
  size_t rightHeight = heightRecursive(node->right);

  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Find the minimum value in the tree
template <typename T>
T BinarySearchTree<T>::findMin() const {
  if (isEmpty()) {
    throw std::runtime_error("Operation cannot be performed on empty tree");
  }

  Node* current = root;
  while (current->left != nullptr) {
    current = current->left;
  }

  return current->data;
}

// Find the maximum value in the tree
template <typename T>
T BinarySearchTree<T>::findMax() const {
  if (isEmpty()) {
    throw std::runtime_error("Operation cannot be performed on empty tree");
  }

  Node* current = root;
  while (current->right != nullptr) {
    current = current->right;
  }

  return current->data;
}

// Perform an in-order traversal of the tree
template <typename T>
void BinarySearchTree<T>::inOrderTraversal(void (*visit)(const T&)) const {
  inOrderTraversalRecursive(root, visit);
}

// Helper method for in-order traversal
template <typename T>
void BinarySearchTree<T>::inOrderTraversalRecursive(
    Node* node, void (*visit)(const T&)) const {
  if (node != nullptr) {
    inOrderTraversalRecursive(node->left, visit);
    visit(node->data);
    inOrderTraversalRecursive(node->right, visit);
  }
}

#endif
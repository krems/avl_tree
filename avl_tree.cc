#include <iostream>

#include <stdlib.h>
#include <vector>
#include <exception>
#include <stack>

using std::vector;
using std::stack;

template <typename T>
struct Node {
  Node<T>* left;
  Node<T>* right;
  size_t height;
  T key;

  Node(T key_) {
    left = 0;
    right = 0;
    height = 1;
    key = key_;
  }
  
  int balanceFactor() {
    if (right) {
      if (left) {
        return right->height - left->height;
      }
      return right->height;
    }
    if (left) {
      return -left->height;
    }
    return 0;
  }

  int compare(T rhs) {
    if (this->key < rhs) {
      return 1;
    }
    if (this->key == rhs) {
      return 0;
    }
    return -1;
  }
};

template <typename T>
class AVLTree {
  Node<T>* root;
 public:
  AVLTree(T key) {
    root = new Node<T>(key);
  }

  template <size_t N>
  AVLTree(T (&keys)[N]) { // : AVLTree(keys[0]) { c++0x didn't work here so
    root = new Node<T>(keys[0]);
    for (size_t i = 1; i < N; ++i) {
      this->add(keys[i]);
    }
  }

  AVLTree(const vector<T>& keys) { // : AVLTree(keys[0]) { see comment above
    root = new Node<T>(keys[0]);
    for (auto it = keys.cbegin() + 1; it != keys.cend(); ++it) {
      this->add(*it);
    }
  }
  
  Node<T>* add(T key) {
    return root = add(key, root);
  }
  
  Node<T>* remove(T key) {
    return root = remove(key, root);
  }

  Node<T>* find(T key) {
    return find(key, root);
  }
  
  ~AVLTree() {
    stack<Node<T>*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
      Node<T>* node = nodes.top();
      if (node->left) {
        nodes.push(node->left);
        continue;
      }
      if (node->right) {
        nodes.push(node->right);
        continue;
      }
      nodes.pop();
      delete node;
    }
  }
  
 private:
  Node<T>* add(T key, Node<T>* node) {
    if (!node) {
      std::cout << key << " " << std::endl;
      return new Node<T>(key);
    }
    switch(node->compare(key)) {
      case 0:
        std::cout << key << " 0 " << node->key << std::endl;
        return node;
      case -1:
        std::cout << key << " -1 " << node->key << std::endl;
        node->left = add(key, node->left);
        break;
      case 1:
        std::cout << key << " 1 " << node->key << std::endl;
        node->right = add(key, node->right);
    }
    return balance(node);
  }

  Node<T>* remove(T key, Node<T>* node) {
    if (!node) {
      throw std::exception();
    }
    switch(node->compare(key)) {
      case 1:
        node->right = remove(key, node->right);
        break;
      case -1:
        node->left = remove(key, node->left);
        break;
      case 0:
        Node<T>* lhs = node->left;
        Node<T>* rhs = node->right;
        delete node;
        if (!rhs) {
          return lhs;
        }
        if (!lhs) {
          return rhs;
        }
        Node<T>* replacing = getMin(rhs);
        replacing->left = lhs;
        replacing->right = removeMin(rhs);
        return balance(replacing);
    }
    std::cout << "bal " << node->key << std::endl;
    return balance(node);
  }

  Node<T>* find(T key, Node<T>* node) {
    if (!node) {
      std::cout << " NULL " << std::endl;
      return 0;
    }
    std::cout << node->key << " " << key << std::endl;
    switch(node->compare(key)) {
      case 0:
        std::cout << " match! " << std::endl;
        return node;
      case -1:
        std::cout << " -1 " << std::endl;
        return find(key, node->left);
      case 1:
        std::cout << " 1 " << std::endl;
        return find(key, node->right);
    }
  }
  
  Node<T>* getMin(Node<T>* node) {
    if (node->left) {
      return getMin(node->left);
    }
    return node;
  }

  Node<T>* removeMin(Node<T>* node) {
    if (!node->left) {
      return node->right;
    }
    node->left = removeMin(node->left);
    return balance(node);
  }
  
  Node<T>* rotateRight(Node<T>* parent) {
    Node<T>* up = parent->left;
    parent->left = up->right;
    up->right = parent;
    recalculateHeights(parent);
    recalculateHeights(up);
    return up;
  }
  
  Node<T>* rotateLeft(Node<T>* parent) {
    Node<T>* up = parent->right;
    parent->right = up->left;
    up->left = parent;
    recalculateHeights(parent);
    recalculateHeights(up);
    return up;
  }

  Node<T>* balance(Node<T>* node) {
    std::cout << "!" << node->key << std::endl;
    recalculateHeights(node);
    std::cout << "!!" << std::endl;
    switch(node->balanceFactor()) {
      case 2:
        if (node->right->balanceFactor() < 0) {
          std::cout << "2!!!" << std::endl;
          node->right = rotateRight(node->right);
        }
        std::cout << "2!!!!" << std::endl;
        return rotateLeft(node);
      case -2:
        if (node->left->balanceFactor() > 0) {
          std::cout << "-2!!!" << std::endl;
          node->left = rotateLeft(node->left);
        }
        std::cout << "-2!!!!" << std::endl;
        return rotateRight(node);
      default:
        std::cout << "!!!" << std::endl;
        return node;
    }
  }

  bool recalculateHeights(Node<T>* node) {
    size_t old_height = node->height;
    node->height = 1 + max(node->left, node->right);
    return !(old_height == node->height);
  }

  size_t max(Node<T>* lhs, Node<T>* rhs) {
    if (lhs != 0) {
      if (rhs != 0) {
        return lhs->height > rhs->height ? lhs->height : rhs->height;
      }
      return lhs->height;
    }
    if (rhs != 0) {
      return rhs->height;
    }
    return 0;
  }
};

int main() {
  int a[] = {0, 115, 243, 8, 98, 34, 71};
  AVLTree<int> tree(a[0]);
  for (size_t i = 1; i < 7; ++i) {
    std::cout << "a[" << i << "] = " << a[i] << std::endl;
    std::cout << "root: " << tree.add(a[i])->key << std::endl;;
  }
  tree.add(9);
  tree.find(9);
  tree.find(243);
  tree.remove(115);
  return 0;
}

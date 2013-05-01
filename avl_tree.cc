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
      return left->height;
    }
    return 0;
  }

  int compare(T rhs) {
    if (this->key < rhs) {
      return -1;
    }
    if (this->key == rhs) {
      return 0;
    }
    return 1;
  }
};

template <typename T>
class AVLTree {
  Node<T>* root;
 public:
  AVLTree(T key) {
    root = new Node<T>(key);
  }

  Node<T>* add(T key) {
    return add(key, root);
  }
  
  void remove(Node* node) {

  }
  
  ~AVLTree() {
    
  }
  
 private:
  Node<T>* add(T key, Node<T>* node) {
    if (!node) {
      return node = new Node<T>(key, node);
    }
    switch(node->compare(key)) {
      case 0:
        return node;
      case -1:
        node->right = add(key, node->left);
        break;
      default:
        node->right = add(key, node->right);
    }
    recalculateHeights(node);
    return balance(node);
  }
  
  Node<T>* rotateRight(Node<T>* parent) {
    Node<T>* up = parent->left;
    parent->left = up->right;
    up->right = parent;
    recalculateHeights(up->right);
    recalculateHeights(up);
    return up;
  }
  
  Node<T>* rotateLeft(Node<T>* parent) {
    Node<T>* up = parent->right;
    parent->right = up->left;
    up->left = parent;
    recalculateHeights(up->left);
    recalculateHeights(up);
    return up;
  }

  Node<T>* balance(Node<T>* node) {
    siwtch(node->balanceFactor()) {
      case 2:
        if ((node->right)->left->height > (node->right)->right->height) {
          node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
      case -2:
        if ((node->right)->left->height < (node->right)->right->height) {
          node->right = rotateLeft(node->right);
        }
        return rotateRight(node);
      default:
        return node;
    }
  }

  bool recalculateHeights(Node<T>* node) {
    size_t old_geight = node->height;
    node->height = 1 + max(node->left, node->right);
    return !(old_geight == node->height);
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
  return 0;
}

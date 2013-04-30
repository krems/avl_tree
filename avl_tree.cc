template <typename T>
struct Node {
  Node(T data_, Node* parent_) {
    parent = parent_;
    left = 0;
    right = 0;
    height = 1;
    data = data_;
  }
  Node(T data_): Node(data_, 0) {}
  Node* parent;
  Node* left;
  Node* right;
  size_t height;
  T data;
  int balanceFactor() {
    return right->height - left->height;
  }
  int compare(T rhs) {
    if (this->data < rhs) {
      return -1;
    }
    if (this->data == rhs) {
      return 0;
    }
    return 1;
  }
};

template <typename T>
class AVLTree {
  Node<T>* root;
 public:
  AVLTree(T data) {
    root = new Node<T>(data, 0);
  }

  Node* add(T data) {
    Node* node = root;
    while (true) {
      switch(node->compare(data)) {
        case 0:
          return node;
        case -1:
          if (node->left == 0) {
            node->left = new Node<T>(data, node);
            recalculateHeightsAndBalance(node);
            return node->left;
          } else {
            node = node->left;
          }
          break;
        default:
          if (node->right == 0) {
            node->right = new Node<T>(data, node);
            recalculateHeightsAndBalance(node);
            return node->right;
          } else {
            node = node->right;
          }
      }
    }
  }

  void remove(Node* node) {

  }
  
  ~AVLTree() {
    delete root;
  }
  
 private: // todo: recalculate heights
  Node* rotateRight(Node* parent) {
    Node* up = parent->left;
    parent->left = up->right;
    up->right = parent;
    up->parent = parent->parent;
    parent->parent = up;
    recalculateHeights(up->right);
    recalculateHeights(up);
    return up;
  }
  
  Node* rotateLeft(Node* parent) {
    Node* up = parent->right;
    parent->right = up->left;
    up->left = parent;
    up->parent = parent->parent;
    parent->parent = up;
    recalculateHeights(up->left);
    recalculateHeights(up);
    return up;
  }

  Node* balance(Node* parent) {
    siwtch(parent->balanceFactor()) {
      case 2:
        if ((parent->right)->left->height > (parent->right)->right->height) {
          parent->right = rotateRight(parent->right);
        }
        return rotateLeft(parent);
      case -2:
        if ((parent->right)->left->height < (parent->right)->right->height) {
          parent->right = rotateLeft(parent->right);
        }
        return rotateRight(parent);
      default:
        return parent;
    }
  }

  bool recalculateHeights(Node* node) {
    size_t old_geight = node->height;
    node->height = 1 + max(node->left, node->right);
    return !(old_geight == node->height);
  }

  void recalculateHeightsAndBalance(Node* node) {
    while(node) {
      if (recalculateHeights(node)) {
        return recalculateHeightsAndBalance(balance(node));
      }
    }
  }
  
  size_t max(Node* lhs, Node* rhs) {
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

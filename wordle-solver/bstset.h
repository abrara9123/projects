#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

using namespace std;

template <typename T>
class BSTSet {
 private:
  struct BSTNode {
    // These two members should never change after initialization!
    const T value;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;

    // This is fancy constructor syntax
    // Don't worry too much about it -- it's just necesssary for the const
    // member.
    BSTNode(T value, BSTNode* parent)
        : value(value), parent(parent), left(nullptr), right(nullptr) {
    }
  };

  BSTNode* root;
  size_t sz;

  // Utility pointer for begin and next.
  BSTNode* curr;

  // TODO_STUDENT: add private helper function definitions here

 public:
  void clearHelper(BSTNode*& curr) {
    if (curr == nullptr) {
      return;
    }
    // clearHelper(curr);
    clearHelper(curr->left);
    clearHelper(curr->right);
    delete curr;
    sz--;
    curr = nullptr;
  }
  // use Inorder Traversal and learn this when u have the time
  void to_string_helper(BSTNode* curr, ostream& ss) const {
    if (curr == nullptr) {
      return;
    }

    if (curr->left != nullptr) {
      to_string_helper(curr->left, ss);
      ss << ", ";
    }

    ss << curr->value;

    if (curr->right != nullptr) {
      ss << ", ";
      to_string_helper(curr->right, ss);
    }
  }

  bool containsRecursive(BSTNode* node, T target) const {
    if (node == nullptr) {
      return false;
    }
    if (target == node->value) {
      return true;
    } else if (target < node->value) {
      return containsRecursive(node->left, target);
    } else {
      return containsRecursive(node->right, target);
    }
  }

  BSTNode* CopyConstrucHelper(BSTNode* other, BSTNode* curr) {
    if (other == nullptr) {
      return nullptr;
    }
    BSTNode* newroot = new BSTNode(other->value, curr);
    // curr->value = other->value;

    newroot->left = CopyConstrucHelper(other->left, newroot);
    newroot->right = CopyConstrucHelper(other->right, newroot);

    sz++;

    return newroot;
  }

  BSTNode* CopyAssignHelper(BSTNode* other, BSTNode* curr) {
    if (other == nullptr) {
      return nullptr;
    }
    clear();
    BSTNode* newroot = new BSTNode(other->value, curr);
    // curr->value = other->value;

    newroot->left = CopyAssignHelper(other->left, newroot);
    newroot->right = CopyAssignHelper(other->right, newroot);

    sz++;

    return newroot;
  }
  /**
   *
   * Creates an empty `BSTSet`. Runs in O(1).
   */
  BSTSet() : root(nullptr), sz(0), curr(nullptr) {
    // TODO_STUDENT
  }

  /**
   * Checks if the `BSTSet` is empty. Runs in O(1).
   */
  bool empty() const {
    // TODO_STUDENT
    if (sz == 0) {
      return true;
    }
    return false;
  }

  /**
   * Returns the number of elements in the `BSTSet`. Runs in O(1).
   */
  size_t size() const {
    // TODO_STUDENT
    return sz;
  }

  /**
   * Adds the `value` to the `BSTSet`. If the value already
   * exists in the set, does not do anything.
   *
   * Uses the `value` to determine the location in the underlying BST.
   * Creates exactly one new node.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  void insert(T value) {
    // TODO_STUDENT

    BSTNode* current;
    // Check if it is nullptr and then return the with the parent node
    if (root == nullptr) {
      auto b1 = new BSTNode(value, nullptr);
      root = b1;
      sz++;
      return;
    }
    current = root;
    // Use a while loop to go through each iteration and to only stop at the end
    // fot he right and left node
    while (current != nullptr) {
      // If the value is a duplicate then we want to return and not add or do
      // anything
      if (value == current->value) {
        return;

      }
      // If the value is less than our current value then we will try to
      // iterrate until we reach the last value then add the node to it
      else if (value < current->value) {
        if (current->left == nullptr) {
          auto node1 = new BSTNode(value, current);
          sz++;
          // This is how we link the node
          current->left = node1;
          return;
        } else {
          // used for iterationg the nodes
          current = current->left;
        }

      }
      // If the value is greather than our current value then we will try to
      // iterrate until we reach the last value then add the node to it
      else if (value > current->value) {
        if (current->right == nullptr) {
          auto node1 = new BSTNode(value, current);
          sz++;
          // This is for linking the right with the new node or we lose the
          // values
          current->right = node1;
          return;
        } else {
          // This is the iteration of the nodes
          current = current->right;
        }
      }
    }
  }

  /**
   * Returns `true` if the `value` is present in the set,
   * and `false` otherwise.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  bool contains(const T& value) const {
    return containsRecursive(root, value);
  }

  /**
   * Empties the `BSTSet`, freeing all memory it controls.
   *
   * Runs in O(N), where N is the number of elements in the set.
   */
  void clear() {
    clearHelper(root);
    // BSTNode* rtemp = root->right;
    // BSTNode* ltemp = root->left;
    // if (rtemp == nullptr && ltemp == nullptr) {
    //   return;
    // }
    // while (rtemp == nullptr && ltemp == nullptr) {
    //   delete rtemp;
    //   delete ltemp;
    //   rtemp = rtemp->right;
    //   ltemp = ltemp->left;
    //   sz--;
    // }
    // TODO_STUDENT
  }

  /**
   * Destructor, cleans up the `BSTSet`.
   *
   * Runs in O(N), where N is the number of elements in the set.
   */
  ~BSTSet() {
    // TODO_STUDENT
    clear();
  }

  /**
   * Converts the `BSTSet` to a string representation, with the values
   * in-order by value.
   *
   * Example:
   *
   * c++
   * BSTSet<string> names;
   * names.insert("Gwen");
   * names.insert("Jen");
   * names.insert("Ben");
   * names.insert("Sven");
   *
   * Calling `names.to_string()` would return the following
   * string: `{Ben, Gwen, Jen, Sven}`
   *
   * Runs in O(N), where N is the number of elements.
   */
  string to_string() const {
    // TODO_STUDENT
    ostringstream ss;
    ss << "{";
    to_string_helper(root, ss);
    ss << "}";
    return ss.str();
  }

  /**
   * Copy constructor.
   *
   * Copies the elements from the provided `BSTSet`.
   * The internal tree structure must be copied exactly.
   *
   *
   * Runs in O(N), where N is the number of elements in `other`.
   */
  BSTSet(const BSTSet& other) {
    // TODO_STUDENT
    // clear();
    root = CopyConstrucHelper(other.root, nullptr);
    sz = other.size();
  }

  /**
   * Assignment operator; `operator=`.
   *
   * Clears this tree, and copies the elements from the provided `BSTSet`.
   * The internal tree structure must be copied exactly.
   *
   * Runs in O(N + O), where N is the number of elements in `this`, and O is
   * the number of elements in `other`.
   */
  BSTSet& operator=(const BSTSet& other) {
    // TODO_STUDENT
    if (this == &other) {
      return *this;
    }
    clear();
    root = CopyAssignHelper(other.root, nullptr);
    sz = other.size();
    return *this;
  }

  BSTNode* findMin(BSTNode* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
    // if (node->left == nullptr) {
    //   return node;
    // }
    // return findMin(node->left);
  }
  BSTNode* findParent(BSTNode* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    BSTNode* temp = nullptr;
    while (node->left != nullptr) {
      temp = node;
      node = node->left;
    }
    return temp;
    // if (node->left == nullptr) {
    //   return node;
    // }
    // return findMin(node->left);
  }
  // =========================================================================

  /**
   * Locates the smallest element in the BSTSet, and removes it
   * from the `BSTSet`. If the `BSTSet` is empty, throws a
   * `runtime_error`
   *
   * Creates no new nodes, and does not update any
   * existing nodes.
   *
   * Runs in O(H), where H is the height of the tree.
   */
  T remove_min() {
    if (root == nullptr) {
      throw std::runtime_error("Error");
    }

    BSTNode* parent;
    parent = findParent(root);
    BSTNode* temp = findMin(root);

    if (parent == nullptr) {
      // If the parent is the minumun, then we wnat to make the root point to
      // thr righht so we dont acess the ist
      root = temp->right;
      if (root != nullptr) {
        root->parent = nullptr;
      }
    } else {
      // This is to make the parent point to the right of the lowest value we
      // found, and we do this so we dont acess to the rest of list, make sure
      // to study this more and review this inperson
      parent->left = temp->right;
      if (temp->right != nullptr) {
        temp->right->parent = parent;
      }
    }
    T val = temp->value;
    delete temp;
    sz--;
    return val;
  }

  /**
   * Resets internal state for an iterative inorder traversal.
   *
   * See `next` for usage details. Modifies nothing except for `curr`.
   *
   * O(H), where H is the maximum height of the tree.
   */
  void begin() {
    // TODO_STUDENT
    curr = findMin(root);
  }

  /**
   * Uses the internal state to return the next in-order element
   * by reference, and advances the internal state. Returns `true`
   * if the reference was set, and `false` otherwise.
   *
   * Example usage:
   *
   * c++
   * BSTSet<string> bst;
   * bst.begin();
   * string value;
   * while (bst.next(val)) {
   *   cout << val << endl;
   * }
   * ```
   *
   * Modifies nothing except for `curr`.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */

  BSTNode* nextHelper() {
    if (curr == nullptr) {
      return nullptr;
    }
    // The right child case
    if (curr->right != nullptr) {
      BSTNode* temp = findMin(curr->right);
      // go left till you cant go left anymore adn we can alos use the min
      // ufnction from before
      //  while (temp->left != nullptr) {
      //    temp = temp->left;
      //  }
      return temp;
    } else {
      // If there is no right child
      BSTNode* succ = nullptr;
      BSTNode* ances = root;
      // Keep going until we find the curr
      while (ances != curr) {
        // if curr is in the left subtree, then we want to
        // if the the curr is less than the ancesotr
        if (curr->value < ances->value) {
          // if it i then set the succest to equal the ances
          succ = ances;
          // keep going left until the condiotn fails
          ances = ances->left;
        } else {
          // if the lest doenst equal the curr , then we want to go right
          ances = ances->right;
        }
      }
      // reutrn the succ of the value we are looking for
      return succ;
    }
  }
  bool next(T& value) {
    // TODO_STUDENT
    if (curr == nullptr) {
      return false;
    }

    value = curr->value;
    curr = nextHelper();
    return true;
  }

  // =========================================================================
  // GO over this with Ta and then tell them to explain it to me in more detial
  BSTNode* getSuccessor(BSTNode* curr) {
    curr = curr->right;
    while (curr != nullptr && curr->left != nullptr) curr = curr->left;
    return curr;
  }

  BSTNode* eraseHelper(BSTNode* node, T value) {
    if (node == nullptr) {
      throw std::out_of_range("Error");
      return nullptr;
    }
    if (value < node->value) {
      node->left = eraseHelper(node->left, value);
    } else if (value > node->value) {
      node->right = eraseHelper(node->right, value);
    } else {
      // Node with No Child if the node has one child case will be handles by
      // this
      if (node->left == nullptr) {
        // Ask professor or TA about this and diagram it if you have the time to
        // do so
        BSTNode* temp = node->right;
        delete node;
        sz--;
        return temp;
      }
      if (node->right == nullptr) {
        BSTNode* temp = node->left;
        delete node;
        sz--;
        return temp;
      }
      // With 2 Children and the Successor involved
      BSTNode* succesror = getSuccessor(node);
      // create a new node with successor's value
      BSTNode* newNode = new BSTNode(succesror->value, nullptr);

      // hook up children properly
      newNode->left = node->left;
      newNode->right = eraseHelper(node->right, succesror->value);

      delete node;
      return newNode;
    }

    return node;
  }
  /**
   * Removes the given element from the `BSTSet`, and returns the
   * value.
   *
   * Throws `out_of_range` if the value is not present in the set.
   * Creates no new nodes, and does not update the value of any
   * existing nodes.
   *
   * Runs in worst-case O(H) where H is the height of the tree.
   */
  T erase(const T& value) {
    root = eraseHelper(root, value);
    
    return value;
  }

  // =========================================================================

  /**
   * Returns a pointer to the root node of the `BSTSet`. For autograder testing
   * purposes only.
   */
  void* getRoot() const {
    return this->root;
  }
};

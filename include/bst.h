// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (value < node->value) {
            insert(node->left, value);
        } else if (value > node->value) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    int search(Node* node, const T& value) const {
        if (node == nullptr) return 0;
        if (value == node->value) return node->count;
        if (value < node->value) return search(node->left, value);
        return search(node->right, value);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void collect(Node* node, Node** arr, int& idx) const {
        if (node == nullptr) return;
        collect(node->left, arr, idx);
        arr[idx++] = node;
        collect(node->right, arr, idx);
    }

    int size(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + size(node->left) + size(node->right);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int search(const T& value) const {
        return search(root, value);
    }

    int size() const {
        return size(root);
    }

    void collectNodes(Node** arr, int& idx) const {
        collect(root, arr, idx);
    }

    using NodeType = Node;
};

#endif  // INCLUDE_BST_H_

// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T data;
        int freq;
        Node* left;
        Node* right;
        explicit Node(const T& val) : data(val), freq(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void push(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
        } else if (value < node->data) {
            push(node->left, value);
        } else if (value > node->data) {
            push(node->right, value);
        } else {
            node->freq++;
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    int search(Node* node, const T& value) const {
        if (node == nullptr) return 0;
        if (value == node->data) return node->freq;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void fetch(Node* node, Node** arr, int& idx) const {
        if (node == nullptr) return;
        fetch(node->left, arr, idx);
        arr[idx++] = node;
        fetch(node->right, arr, idx);
    }

    int getSize(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + getSize(node->left) + getSize(node->right);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void push(const T& value) {
        push(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int search(const T& value) const {
        return search(root, value);
    }

    int getSize() const {
        return getSize(root);
    }

    void fetchNodes(Node** arr, int& idx) const {
        fetch(root, arr, idx);
    }

    using NodeType = Node;
};

#endif  // INCLUDE_BST_H_

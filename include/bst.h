// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>

template<typename ValType>
class BST {
 private:
    struct Item {
        ValType data;
        int freq;
        Item* leftLink;
        Item* rightLink;
        
        explicit Item(const ValType& val) 
            : data(val), freq(1), leftLink(nullptr), rightLink(nullptr) {}
    };

    Item* top;

    void addItem(Item*& node, const ValType& val) {
        if (node == nullptr) {
            node = new Item(val);
        } else if (val < node->data) {
            addItem(node->leftLink, val);
        } else if (val > node->data) {
            addItem(node->rightLink, val);
        } else {
            node->freq++;
        }
    }

    int calcDepth(Item* node) const {
        if (node == nullptr) return 0;
        int leftDepth = calcDepth(node->leftLink);
        int rightDepth = calcDepth(node->rightLink);
        return 1 + std::max(leftDepth, rightDepth);
    }

    int findValue(Item* node, const ValType& val) const {
        if (node == nullptr) return 0;
        if (val == node->data) return node->freq;
        if (val < node->data) return findValue(node->leftLink, val);
        return findValue(node->rightLink, val);
    }

    void eraseAll(Item* node) {
        if (node == nullptr) return;
        eraseAll(node->leftLink);
        eraseAll(node->rightLink);
        delete node;
    }

    void traverse(Item* node, Item** buffer, int& idx) const {
        if (node == nullptr) return;
        traverse(node->leftLink, buffer, idx);
        buffer[idx++] = node;
        traverse(node->rightLink, buffer, idx);
    }

    int countItems(Item* node) const {
        if (node == nullptr) return 0;
        return 1 + countItems(node->leftLink) + countItems(node->rightLink);
    }

 public:
    BST() : top(nullptr) {}

    ~BST() {
        eraseAll(top);
    }

    void push(const ValType& val) {
        addItem(top, val);
    }

    int height() const {
        return calcDepth(top);
    }

    int count(const ValType& val) const {
        return findValue(top, val);
    }

    int getSize() const {
        return countItems(top);
    }

    void fetchNodes(Item** arr, int& start) const {
        traverse(top, arr, start);
    }

    using NodeType = Item;
};

#endif  // INCLUDE_BST_H_

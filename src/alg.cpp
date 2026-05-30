// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    while (!file.eof()) {
        int ch = file.get();
        if (file.eof()) break;
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch - 'A' + 'a';
            }
            word += static_cast<char>(ch);
        } else {
            if (word.size() > 0) {
                tree.insert(word);
            }
            word.clear();
        }
    }
    if (word.size() > 0) {
        tree.insert(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    int total = tree.size();
    if (total == 0) return;
    
    using NodePtr = BST<std::string>::NodeType*;
    std::vector<NodePtr> nodes(total);
    int idx = 0;
    tree.collectNodes(nodes.data(), idx);
    
    std::sort(nodes.begin(), nodes.begin() + idx,
        [](const NodePtr& a, const NodePtr& b) {
            if (a->count != b->count)
                return a->count > b->count;
            return a->value < b->value;
        });
    
    for (int i = 0; i < idx; i++) {
        std::cout << nodes[i]->value << " " << nodes[i]->count << "\n";
    }
    
    std::ofstream out("result/freq.txt");
    if (out) {
        for (int i = 0; i < idx; i++) {
            out << nodes[i]->value << " " << nodes[i]->count << "\n";
        }
        out.close();
    }
}

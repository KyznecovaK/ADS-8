// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& bstObj, const char* filePath) {
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string tempWord;
    while (!inputFile.eof()) {
        int symbol = inputFile.get();
        if (inputFile.eof()) break;
        if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z')) {
            if (symbol >= 'A' && symbol <= 'Z') {
                symbol = symbol - 'A' + 'a';
            }
            tempWord += static_cast<char>(symbol);
        } else {
            if (tempWord.size() > 1) {
                bstObj.push(tempWord);
            }
            tempWord.clear();
        }
    }
    if (tempWord.size() > 1) {
        bstObj.push(tempWord);
    }
    inputFile.close();
}

void printFreq(BST<std::string>& bstObj) {
    int totalElems = bstObj.getSize();
    if (totalElems == 0) return;
    using NodePtr = BST<std::string>::NodeType*;
    std::vector<NodePtr> storage(totalElems);
    int position = 0;
    bstObj.fetchNodes(storage.data(), position);
    std::sort(storage.begin(), storage.begin() + position,
        [](const NodePtr& first, const NodePtr& second) {
            if (first->freq != second->freq)
                return first->freq > second->freq;
            return first->data < second->data;
        });
    for (int i = 0; i < position; i++) {
        std::cout << storage[i]->data << " " << storage[i]->freq << "\n";
    }
    std::ofstream outFile("result/freq.txt");
    if (outFile) {
        for (int i = 0; i < position; i++) {
            outFile << storage[i]->data << " " << storage[i]->freq << "\n";
        }
        outFile.close();
    }
}

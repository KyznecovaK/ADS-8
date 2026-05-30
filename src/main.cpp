// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void printFreq(BST<std::string>& bstTree);
void makeTree(BST<std::string>& bstTree, const char* inputFile);

int main() {
    const char* inputFile = "src/war_peace.txt";

    BST<std::string> bstTree;
    makeTree(bstTree, inputFile);

    std::cout << "Tree depth: " << bstTree.depth() << std::endl;
    std::cout << "Unique words: " << bstTree.size() << std::endl;
    std::cout << "'the' count: " << bstTree.search("the") << std::endl;
    std::cout << "'pierre' count: " << bstTree.search("pierre") << std::endl;

    printFreq(bstTree);

    return 0;
}

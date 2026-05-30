// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    const char* filename = "src/war_peace.txt";

    BST<std::string> tree;
    makeTree(tree, filename);

    std::cout << "Tree height: " << tree.depth() << std::endl;
    std::cout << "Unique words: " << tree.size() << std::endl;
    std::cout << "'the' count: " << tree.search("the") << std::endl;
    std::cout << "'pierre' count: " << tree.search("pierre") << std::endl;

    printFreq(tree);

    return 0;
}

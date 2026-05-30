// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void printFreq(BST<std::string>& bstTree) {
  int totalElements = bstTree.size();
  if (totalElements == 0) return;
  
  using NodePointer = BST<std::string>::NodeType*;
  std::vector<NodePointer> collectedNodes(totalElements);
  int currentIndex = 0;
  bstTree.collectNodes(collectedNodes.data(), currentIndex);
  
  std::sort(collectedNodes.begin(), collectedNodes.begin() + currentIndex,
    [](const NodePointer& firstNode, const NodePointer& secondNode) {
      if (firstNode->count != secondNode->count)
        return firstNode->count > secondNode->count;
      return firstNode->value < secondNode->value;
    });
  
  for (int i = 0; i < currentIndex; i++) {
    std::cout << collectedNodes[i]->value << " " << collectedNodes[i]->count << "\n";
  }
  
  std::ofstream outputFile("result/freq.txt");
  if (outputFile) {
    for (int i = 0; i < currentIndex; i++) {
      outputFile << collectedNodes[i]->value << " " << collectedNodes[i]->count << "\n";
    }
    outputFile.close();
  }
}

void makeTree(BST<std::string>& bstTree, const char* inputFile) {
  std::ifstream fileStream(inputFile);
  if (!fileStream) {
    std::cout << "File error!" << std::endl;
    return;
  }
  
  std::string currentWord;
  while (!fileStream.eof()) {
    int character = fileStream.get();
    if (fileStream.eof()) break;
    
    if ((character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z')) {
      if (character >= 'A' && character <= 'Z') {
        character = character - 'A' + 'a';
      }
      currentWord += static_cast<char>(character);
    } else {
      if (currentWord.size() > 1) {
        bstTree.insert(currentWord);
      }
      currentWord.clear();
    }
  }
  
  if (currentWord.size() > 1) {
    bstTree.insert(currentWord);
  }
  fileStream.close();
}

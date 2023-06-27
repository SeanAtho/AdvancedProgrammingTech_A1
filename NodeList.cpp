#include "NodeList.h"
#include <iostream>

NodeList::NodeList(){
    length = 0;
}

NodeList::~NodeList(){
    // Delete all the nodes in the list
    for (int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

NodeList::NodeList(NodeList& other){
   // Perform a deep copy of the other NodeList
    length = other.length;
    for (int i = 0; i < length; i++) {
        nodes[i] = new Node(*(other.nodes[i]));
    }
}

int NodeList::getLength(){
    return length;
}

void NodeList::addElement(Node* newNode) {
    // Check if the NodeList is already full
    if (length >= NODE_LIST_ARRAY_MAX_SIZE) {
        std::cout << "Cannot add element. NodeList is full." << std::endl;
        return;
    }

    // Make a copy of the newNode and add it to the list
    Node* copyNode = new Node(*newNode);
    nodes[length] = copyNode;
    length++;
}

void NodeList::removeElement(Node* node) {
    // Find the node in the list
    for (int i = 0; i < length; i++) {
        if (nodes[i] == node) {
            // Shift the elements after the found node to the left
            for (int j = i; j < length - 1; j++) {
                nodes[j] = nodes[j + 1];
            }
            length--;
            return;
        }
    }
}



Node* NodeList::getNode(int i){
    // Check if the index is within the valid range
    if (i >= 0 && i < length) {
        return nodes[i];
    }

    std::cout << "Invalid index. Returning nullptr." << std::endl;
    return nullptr;
}

bool NodeList::containsNode(Node* node) {
    // Iterate over the nodes in the list
    for (int i = 0; i < length; i++) {
        // Check if the current node matches the given node
        if (nodes[i]->getRow() == node->getRow() && nodes[i]->getCol() == node->getCol()) {
            return true;  // Node found in the list
        }
    }
    return false;  // Node not found in the list
}

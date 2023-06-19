#include "NodeList.h"
#include <iostream>

// Constructor: Initialize NodeList with zero nodes.
NodeList::NodeList(){
    length = 0;
}

// Destructor: Delete all nodes in the NodeList.
NodeList::~NodeList(){
    for (int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

// Copy Constructor: Deep copy other NodeList.
NodeList::NodeList(NodeList& other){
    length = other.length;
    for (int i = 0; i < length; i++) {
        nodes[i] = new Node(*other.nodes[i]);
    }
}

// Return the number of elements in the NodeList.
int NodeList::getLength(){
    return length;
}

// Add a copy of the node element to the back of the NodeList.
void NodeList::addElement(Node* newPos){
if (length < NODE_LIST_ARRAY_MAX_SIZE) {
        nodes[length] = new Node(*newPos);
        length++;
    } else {
        std::cerr << "NodeList is full. Can't add more nodes." << std::endl;
    }
}

// Get a pointer to the ith node in the node list.
Node* NodeList::getNode(int i){
    if (i >= 0 && i < length) {
        return nodes[i];
    } else {
        std::cerr << "Invalid index." << std::endl;
        return nullptr;
    }
}
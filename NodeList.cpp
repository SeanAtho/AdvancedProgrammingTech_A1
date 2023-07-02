#include "NodeList.h"
#include <iostream>

/*
 * NodeList constructor
 * Initializes the length to 0
 */
NodeList::NodeList(){
    length = 0;
}

/*
 * NodeList destructor
 * Deletes all the nodes in the list
 */
NodeList::~NodeList(){
    for (int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

/*
 * Copy constructor for NodeList
 * Performs a deep copy of the other NodeList
 */
NodeList::NodeList(NodeList& other){
    length = other.length;
    for (int i = 0; i < length; i++) {
        nodes[i] = new Node(*(other.nodes[i]));
    }
}

/*
 * Method to get the length of NodeList
 */
int NodeList::getLength(){
    return length;
}

/*
 * Method to add a new element to NodeList
 * Checks if the NodeList is already full before adding
 * Makes a copy of the newNode and adds it to the list
 */
void NodeList::addElement(Node* newNode) {
    if (length >= NODE_LIST_ARRAY_MAX_SIZE) {
        std::cout << "Cannot add element. NodeList is full." << std::endl;
        return;
    }

    Node* copyNode = new Node(*newNode);
    nodes[length] = copyNode;
    length++;
}

/*
 * Method to remove an element from NodeList
 * Finds the node in the list and shifts the elements after the found node to the left
 */
void NodeList::removeElement(Node* node) {
    for (int i = 0; i < length; i++) {
        if (nodes[i] == node) {
            for (int j = i; j < length - 1; j++) {
                nodes[j] = nodes[j + 1];
            }
            length--;
            return;
        }
    }
}

/*
 * Method to get the node at a particular index
 * Checks if the index is within the valid range
 */
Node* NodeList::getNode(int i){
    Node* result = nullptr;
    if (i >= 0 && i < length) {
        result = nodes[i];
    } else {
        std::cout << "Invalid index." << std::endl;
    }
    return result;
}

/*
 * Method to check if NodeList contains a particular node
 * Iterates over the nodes in the list and checks if the current node matches the given node
 */
bool NodeList::containsNode(Node* node) {
    bool foundNode = false;
    int i = 0;
    while(i < length && !foundNode) {
        if (nodes[i]->getRow() == node->getRow() && nodes[i]->getCol() == node->getCol()) {
            foundNode = true;  
        }
        i++;
    }
    return foundNode;
}

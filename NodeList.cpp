#include "NodeList.h"
#include <iostream>

// Constructor: Initialize NodeList with zero nodes.
NodeList::NodeList() 
    : length(0) {
}

// Destructor: Delete all nodes in the NodeList.
NodeList::~NodeList() {
    for (int i = 0; i < length; i++) {
        delete nodes[i];
    }
}

// Copy Constructor: Deep copy other NodeList.
NodeList::NodeList(NodeList& other) 
    : length(other.length) {

    for (int i = 0; i < length; i++) {
        nodes[i] = new Node(*other.nodes[i]);
    }
}


// Return the number of elements in the NodeList.
int NodeList::getLength() {
    return length;
}

// Add a copy of the node element to the back of the NodeList.
void NodeList::addElement(Node* newNode) {
    if (length < NODE_LIST_ARRAY_MAX_SIZE) {
        nodes[length] = new Node(*newNode);
        length++;
    } else {
        throw std::length_error("NodeList is full. Can't add more nodes.");
    }
}


// Get a pointer to the ith node in the node list.
Node* NodeList::getNode(int i) {
    if (i >= 0 && i < length) {
        return nodes[i];
    } else {
        throw std::out_of_range("Invalid index provided to getNode.");
    }
}



/*
 * Function: isNodeInList
 * --------------------------
 * Check whether a given node is already in the list
 *
 * node: Reference to the Node object that needs to be checked.
 *
 * Returns: true if the node exists in the list, false otherwise.
 */
bool NodeList::isNodeInList(Node& node) const {
    // Loop through all nodes in the list
    for (int i = 0; i < length; ++i) {
        // If a node in the list has the same row and column as the given node
        if (nodes[i]->getRow() == node.getRow() &&
            nodes[i]->getCol() == node.getCol()) {
            return true; // Node is in the list
        }
    }
    return false; // Node is not in the list
}


/*
 * Function: removeNodeByIndex
 * -----------------------------
 * Remove a node from the list based on its index.
 *
 * index: The index of the node to be removed.
 *
 * Returns: void.
 */
void NodeList::removeNodeByIndex(int index) {
    // Check if index is within the valid range
    if (index >= 0 && index < length) {
        // Delete the node at the given index
        delete nodes[index];
        // Shift all nodes after the deleted one to fill the gap
        for (int i = index; i < length - 1; ++i) {
            nodes[i] = nodes[i + 1];
        }
        // Decrease the length of the list as one node is removed
        --length;
    } else {
        // Throw exception if index is invalid
        throw std::out_of_range("Invalid index provided to removeNodeByIndex.");
    }
}

Node* NodeList::getNodeWithMinDist(Node* goal, const NodeList& closedList) {
    if (length == 0) {
        throw std::runtime_error("The list is empty.");
    }

    Node* minDistNode = nullptr;
    int minDist = std::numeric_limits<int>::max();  // initialize with maximum possible int value

    for (int i = 0; i < length; i++) {
        if (!closedList.isNodeInList(*nodes[i])) {  // check if the node is not in the closed list
            int estimate = nodes[i]->getDistanceTraveled() +
                           std::abs(nodes[i]->getCol() - goal->getCol()) +
                           std::abs(nodes[i]->getRow() - goal->getRow());  // calculate the estimated distance to the goal
            if (estimate < minDist) {
                minDist = estimate;
                minDistNode = nodes[i];
            }
        }
    }

    if (!minDistNode) {
        throw std::runtime_error("No node found which is not in the closed list.");
    }

    return minDistNode;
}

int NodeList::getNodeIndex(Node* node) {
    for (int i = 0; i < length; ++i) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1; // if the node is not found in the NodeList
}

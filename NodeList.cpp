#include "NodeList.h"
#include <iostream>
#include <limits>

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

// This function returns a pointer to the node in the NodeList with the minimum 
// estimated distance to the goal node that is not in the closed list.
// If the NodeList is empty, or all the nodes in the NodeList are in the closed list, 
// this function throws a runtime_error exception.
Node* NodeList::getNodeWithMinDist(Node* goal, const NodeList& closedList) {
    // Throw an error if the NodeList is empty.
    if (length == 0) {
        throw std::runtime_error("The list is empty.");
    }

    // Initialize the minimum distance with the maximum possible int value
    // and minDistNode with nullptr.
    Node* minDistNode = nullptr;
    int minDist = std::numeric_limits<int>::max();

    // Iterate over the NodeList to find the node with minimum estimated distance.
    for (int i = 0; i < length; i++) {
        // Only consider the node if it is not in the closed list.
        if (!closedList.isNodeInList(*nodes[i])) {
            // Estimate the distance to the goal using Manhattan distance.
            int estimate = nodes[i]->getDistanceTraveled() +
                           std::abs(nodes[i]->getCol() - goal->getCol()) +
                           std::abs(nodes[i]->getRow() - goal->getRow());

            // If this node's estimated distance is less than the current minimum,
            // update the minimum and set minDistNode to this node.
            if (estimate < minDist) {
                minDist = estimate;
                minDistNode = nodes[i];
            }
        }
    }

    // If all nodes are in the closed list, throw an error.
    if (!minDistNode) {
        throw std::runtime_error("No node found which is not in the closed list.");
    }

    // Return the node with the minimum estimated distance.
    return minDistNode;
}

// This function returns the index of the provided node in the NodeList.
// If the node is not found in the NodeList, it returns -1.
int NodeList::getNodeIndex(Node* node) {
    // Iterate over the NodeList to find the node.
    for (int i = 0; i < length; ++i) {
        // If the node at the ith index in the NodeList is the given node,
        // return the index.
        if (nodes[i] == node) {
            return i;
        }
    }

    // If the node is not found in the NodeList, return -1.
    return -1;
}


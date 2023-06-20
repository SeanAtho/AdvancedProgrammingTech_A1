#include "PathSolver.h"
#include <iostream>

// Constructor: Initialize PathSolver with zero nodes.
PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

// Destructor: Delete all nodes in the PathSolver.
PathSolver::~PathSolver(){
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env){
    // Initialize start and end Nodes with null
    Node* startNode = nullptr;
    Node* endNode = nullptr;

    // Iterate over the environment to find the start and end points
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            // Check if the current point is the start point
            if (env[i][j] == SYMBOL_START) {
                startNode = new Node(j, i, 0); // Distance traveled by start node is 0
            } 
            // Check if the current point is the end point
            else if (env[i][j] == SYMBOL_GOAL) {
                endNode = new Node(j, i, 0); // Distance traveled is not relevant for end node
            }
        }
    }

    // Throw an error if no start or end point is found
    if (!startNode || !endNode) {
        throw std::runtime_error("No start or end point in the environment.");
    }

    // Create an open list (to visit) and a closed list (already visited)
    NodeList openList;
    NodeList closedList;

    // Start the search from the starting node
    openList.addElement(startNode);

    // Keep searching as long as there are nodes to visit
    while (openList.getLength() > 0) {
        // Pick the node with the shortest distance to the end node
        Node* currentNode = openList.getNodeWithMinDist(endNode, closedList);

        // If the current node is the goal node, finish the search
        if (*currentNode == *endNode) {
            nodesExplored = new NodeList(closedList);
            break;
        }

        // Remove the current node from the open list and add it to the closed list
        int currentNodeIndex = openList.getNodeIndex(currentNode);
        openList.removeNodeByIndex(currentNodeIndex);
        closedList.addElement(currentNode);

        // Examine all the neighboring nodes of the current node
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                // Skip the current node itself
                if (dx == 0 && dy == 0) continue;

                // Calculate the coordinates of the neighbor
                int nx = currentNode->getCol() + dx;
                int ny = currentNode->getRow() + dy;

                // Skip if the neighbor is out of bounds or is a wall
                if (nx < 0 || nx >= ENV_DIM || ny < 0 || ny >= ENV_DIM) continue;
                if (env[ny][nx] == SYMBOL_WALL) continue;

                // Create a temporary neighbor node
                Node tempNeighbor(nx, ny, currentNode->getDistanceTraveled() + 1);

                // If the neighbor node is not in open or closed list, add it to the open list
                if (!openList.isNodeInList(tempNeighbor) && !closedList.isNodeInList(tempNeighbor)) {
                    Node* neighbor = new Node(nx, ny, currentNode->getDistanceTraveled() + 1);
                    openList.addElement(neighbor);
                }
            }
        }
    }

    // Delete the end node as it is no longer needed
    delete endNode;
}

// Method for getting a deep copy of the explored NodeList in forward search
NodeList* PathSolver::getNodesExplored(){
    // Deep copy
    NodeList* nodesExploredCopy = new NodeList(*nodesExplored);
    return nodesExploredCopy;
}

// Method for getting the path the robot should travel
NodeList* PathSolver::getPath(Env env){
    // TODO: To be implemented in milestone 3
    return nullptr;
}


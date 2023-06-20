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
    // Create start and end Nodes
    Node* startNode = nullptr;
    Node* endNode = nullptr;
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            if (env[i][j] == SYMBOL_START) {
                startNode = new Node(j, i, 0); // distance traveled by start node is 0
            } else if (env[i][j] == SYMBOL_GOAL) {
                endNode = new Node(j, i, 0); // distance traveled is not relevant for end node
            }
        }
    }

    if (!startNode || !endNode) {
        throw std::runtime_error("No start or end point in the environment.");
    }

    // P - open list
    NodeList openList;
    // C - closed list
    NodeList closedList;

    openList.addElement(startNode);

    while (openList.getLength() > 0) {
        Node* currentNode = openList.getNodeWithMinDist(endNode, closedList); // use the function to find the node with minimum distance

        // Check if current node is the goal
        if (*currentNode == *endNode) {
            nodesExplored = new NodeList(closedList);
            break;
        }

        // Find index of current node in the open list
        int currentNodeIndex = openList.getNodeIndex(currentNode);
        // Remove current node from open list
        openList.removeNodeByIndex(currentNodeIndex);
        // Add current node to closed list
        closedList.addElement(currentNode);

        // Iterate over the neighbors
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue;

                int nx = currentNode->getCol() + dx;
                int ny = currentNode->getRow() + dy;

                if (nx < 0 || nx >= ENV_DIM || ny < 0 || ny >= ENV_DIM) continue;
                if (env[ny][nx] == SYMBOL_WALL) continue;

                Node* neighbor = new Node(nx, ny, currentNode->getDistanceTraveled() + 1);

                if (!openList.isNodeInList(*neighbor) && !closedList.isNodeInList(*neighbor)) {
                    openList.addElement(neighbor);
                } else {
                    delete neighbor;
                }
            }
        }
    }

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


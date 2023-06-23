#include "PathSolver.h"
#include <iostream>

int manhattanDist(std::pair<int, int> p1, std::pair<int, int> p2) {
    return std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second);
}


// Constructor: Initialize PathSolver with zero nodes.
PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

// Destructor: Delete all nodes in the PathSolver.
PathSolver::~PathSolver(){
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
    Node* startNode = nullptr;
    Node* endNode = nullptr;

    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            if (env[i][j] == SYMBOL_START) {
                startNode = new Node(j, i, 0);
            } 
            else if (env[i][j] == SYMBOL_GOAL) {
                endNode = new Node(j, i, 0);
            }
        }
    }

    if (!startNode || !endNode) {
        throw std::runtime_error("No start or end point in the environment.");
    }

    NodeList openList;
    NodeList closedList;

    openList.addElement(startNode);

    while (openList.getLength() > 0) {
        Node* currentNode = openList.getNodeWithMinDist(endNode, closedList);

        // You need to get the index of the currentNode in the openList before removing it
        int currentNodeIndex = openList.getNodeIndex(currentNode);

        // Now you can remove the node
        Node* removedNode = openList.removeNodeByIndex(currentNodeIndex);
        // There's no need to delete the removedNode. It's the same as currentNode which will be used later.

        closedList.addElement(currentNode);

        if (*currentNode == *endNode) {
            delete nodesExplored;
            nodesExplored = new NodeList(closedList);
            break;
        }

        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; ++i) {
            int nx = currentNode->getCol() + dx[i];
            int ny = currentNode->getRow() + dy[i];

            if (nx < 0 || nx >= ENV_DIM || ny < 0 || ny >= ENV_DIM) continue;
            if (env[ny][nx] == SYMBOL_WALL) continue;

            Node tempNeighbor(nx, ny, currentNode->getDistanceTraveled() + 1);

            if (!openList.isNodeInList(tempNeighbor) && !closedList.isNodeInList(tempNeighbor)) {
                Node* neighbor = new Node(nx, ny, currentNode->getDistanceTraveled() + 1);
                neighbor->setParent(currentNode);
                openList.addElement(neighbor);
            }
        }
    }
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


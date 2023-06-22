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

    // Add the start node to the open list
    openList.addElement(startNode);

    // Keep searching as long as there are nodes to visit
    while (openList.getLength() > 0) {
        // Pick the node with the shortest estimated distance to the end node that's not in closed list
        Node* currentNode = openList.getNodeWithMinDist(endNode, closedList);

        // Remove the current node from the open list
        int currentNodeIndex = openList.getNodeIndex(currentNode);
        openList.removeNodeByIndex(currentNodeIndex);

        // Add current node to closed list
        closedList.addElement(currentNode);

        // If the current node is the goal node, finish the search
        if (*currentNode == *endNode) {
            nodesExplored = new NodeList(closedList);
            break;
        }

        // Examine all the neighboring nodes of the current node
        for (int i = 0; i < 4; ++i) {
            // Define the four possible movements (up, down, left, right)
            int dx[4] = {0, 0, -1, 1};
            int dy[4] = {-1, 1, 0, 0};

            // Calculate the coordinates of the neighbor
            int nx = currentNode->getCol() + dx[i];
            int ny = currentNode->getRow() + dy[i];

            // Skip if the neighbor is out of bounds or is a wall
            if (nx < 0 || nx >= ENV_DIM || ny < 0 || ny >= ENV_DIM) continue;
            if (env[ny][nx] == SYMBOL_WALL) continue;

            // Create a temporary neighbor node
            Node tempNeighbor(nx, ny, currentNode->getDistanceTraveled() + 1);

            // If the neighbor node is not in open or closed list, add it to the open list
            if (!openList.isNodeInList(tempNeighbor) && !closedList.isNodeInList(tempNeighbor)) {
                Node* neighbor = new Node(nx, ny, currentNode->getDistanceTraveled() + 1);
                neighbor->setParent(currentNode); // Set the parent node
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


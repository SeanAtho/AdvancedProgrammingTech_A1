#include "PathSolver.h"
#include <iostream>
#include <climits>


PathSolver::PathSolver(){
    // Constructor implementation
    nodesExplored = new NodeList();
}

PathSolver::~PathSolver(){
    // Destructor implementation
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env) {
    // Get the start and goal positions from the environment
    Node* start = nullptr;
    Node* goal = nullptr;

    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            if (env[i][j] == SYMBOL_START) {
                start = new Node(i, j, 0);
            } else if (env[i][j] == SYMBOL_GOAL) {
                goal = new Node(i, j, 0);
            }
        }
    }

    // Create the open list and closed list
    NodeList openList;
    NodeList closedList;

    // Add the start position to the open list
    openList.addElement(start);

    bool goalReached = false;

    while (openList.getLength() > 0 && !goalReached) {
        // Select the node with the smallest estimated distance from the open list
        Node* current = nullptr;
        int smallestDistance = INT_MAX;

        // Iterate over the nodes in the open list and find the node with the smallest estimated distance
        for (int i = 0; i < openList.getLength(); i++) {
            Node* node = openList.getNode(i);
            if (node != nullptr) {
                int estimatedDistance = node->getEstimatedDist2Goal(goal);

                if (estimatedDistance < smallestDistance) {
                    smallestDistance = estimatedDistance;
                    current = node;
                }
            } else {
                std::cout << "Invalid node at index: " << i << std::endl;
            }
        }

        // Remove the current node from the open list
        openList.removeElement(current);

        // Add the current node to the closed list
        closedList.addElement(current);

        // Check if the current node is the goal
        bool isGoal = current->isGoal(goal);
        goalReached = isGoal;

        // Explore neighboring positions
        int row = current->getRow();
        int col = current->getCol();

        // Check neighboring positions: up, down, left, right
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; i++) {
            int newRow = row + dy[i];
            int newCol = col + dx[i];

            // Check if the new position is valid and not a wall
            bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM &&
                                 env[newRow][newCol] != SYMBOL_WALL;

            if (validPosition) {
                // Create a new node for the neighboring position
                Node* neighbor = new Node(newRow, newCol, current->getDistanceTraveled() + 1);

                // Check if the neighbor is already in the closed list
                bool inClosedList = closedList.containsNode(neighbor);

                if (!inClosedList) {
                    // Check if the neighbor is already in the open list
                    bool inOpenList = openList.containsNode(neighbor);

                    if (!inOpenList) {
                        // Add the neighbor to the open list
                        openList.addElement(neighbor);
                    } else {
                        delete neighbor;
                    }
                } else {
                    delete neighbor;
                }
            }
        }
    }

    // Store the explored positions in nodesExplored
    delete nodesExplored;
    nodesExplored = new NodeList(closedList);

    // Clean up
    delete start;
    delete goal;
}




NodeList* PathSolver::getNodesExplored() {
    // Create a deep copy of the nodesExplored list
    NodeList* copyList = new NodeList(*nodesExplored);
    return copyList;
}

NodeList* PathSolver::getPath(Env env) {
    NodeList* path = new NodeList();
    Node* goalNode = nullptr;

    // Find the goal node in the explored nodes
    for(int i = 0; i < nodesExplored->getLength(); i++) {
        Node* node = nodesExplored->getNode(i);
        if(env[node->getRow()][node->getCol()] == SYMBOL_GOAL) {
            goalNode = node;
        }
    }

    if(goalNode != nullptr) {
        Node* currentNode = goalNode;
        NodeList* tempPath = new NodeList();

        // Add goal node to tempPath
        tempPath->addElement(currentNode);

        while(currentNode->getDistanceTraveled() > 0) { // until we reach the start node
            // Check neighboring positions: up, right, down, left
            int dx[4] = {0, 1, 0, -1};
            int dy[4] = {-1, 0, 1, 0};
            
            bool foundValidNeighbor = false;

            for (int i = 0; i < 4 && !foundValidNeighbor; i++) {
                int newRow = currentNode->getRow() + dy[i];
                int newCol = currentNode->getCol() + dx[i];

                // Check if the new position is valid
                bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM;

                if (validPosition) {
                    for(int j = 0; j < nodesExplored->getLength() && !foundValidNeighbor; j++) {
                        Node* node = nodesExplored->getNode(j);

                        // If this node is a neighbor of the current node and its distance traveled is one less than the current node's
                        if(node->getRow() == newRow && node->getCol() == newCol && node->getDistanceTraveled() == currentNode->getDistanceTraveled() - 1) {
                            currentNode = node;
                            foundValidNeighbor = true;
                        }
                    }
                }
            }
            if (foundValidNeighbor) {
                // Only add the node to the path if a valid neighbor was found
                tempPath->addElement(currentNode);
            }
        }

        // Reorder tempPath from start to finish and assign it to path
        for(int i = tempPath->getLength() - 1; i >= 0; i--) {
            path->addElement(tempPath->getNode(i));
        }
        delete tempPath;
    }

    return path;
}


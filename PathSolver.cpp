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
            int estimatedDistance = node->getEstimatedDist2Goal(goal);

            if (estimatedDistance < smallestDistance) {
                smallestDistance = estimatedDistance;
                current = node;
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


NodeList* PathSolver::getPath(Env env){
    // TODO: Implement the logic to find the path
    // ...

    NodeList* path = nullptr; // Placeholder, replace with actual path

    return path; // Return the path or nullptr
}

//-----------------------------


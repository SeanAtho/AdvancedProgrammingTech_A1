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

// Method: forwardSearch
// This method performs the pathfinding search on the environment using the A* algorithm.
void PathSolver::forwardSearch(Env env) {
    // Define Node pointers for start and goal nodes.
    Node* start = nullptr;
    Node* goal = nullptr;

    // Iterate over the environment grid to find the start and goal positions.
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            // Create a new start node if the current position is the start symbol.
            if (env[i][j] == SYMBOL_START) {
                start = new Node(i, j, 0);
            } 
            // Create a new goal node if the current position is the goal symbol.
            else if (env[i][j] == SYMBOL_GOAL) {
                goal = new Node(i, j, 0);
            }
        }
    }

    // Initialize the open and closed lists for the A* algorithm.
    NodeList openList;
    NodeList closedList;

    // Add the start node to the open list to begin the algorithm.
    openList.addElement(start);

    // Initialize a boolean to track if the goal has been reached.
    bool goalReached = false;

    // Execute the main loop of the A* algorithm until the open list is empty or the goal is reached.
    while (openList.getLength() > 0 && !goalReached) {
        // The current node is the node from the open list with the smallest estimated distance to the goal.
        Node* current = nullptr;
        int smallestDistance = INT_MAX;

        // Find the node with the smallest estimated distance in the open list.
        for (int i = 0; i < openList.getLength(); i++) {
            Node* node = openList.getNode(i);
            if (node != nullptr) {
                int estimatedDistance = node->getEstimatedDist2Goal(goal);

                // Update the current node if the estimated distance is smaller.
                if (estimatedDistance < smallestDistance) {
                    smallestDistance = estimatedDistance;
                    current = node;
                }
            } else {
                std::cout << "Invalid node at index: " << i << std::endl;
            }
        }

        // Move the current node from the open list to the closed list.
        openList.removeElement(current);
        closedList.addElement(current);

        // Check if the current node is the goal, and update the boolean accordingly.
        bool isGoal = current->isGoal(goal);
        goalReached = isGoal;

        // If the current node is not the goal, explore its neighbors.
        int row = current->getRow();
        int col = current->getCol();

        // The direction vectors represent up, down, left, right.
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};

        // Explore each neighboring position.
        for (int i = 0; i < 4; i++) {
            int newRow = row + dy[i];
            int newCol = col + dx[i];

            // Verify that the new position is within the environment and not a wall.
            bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM &&
                                 env[newRow][newCol] != SYMBOL_WALL;

            if (validPosition) {
                // Create a new neighbor node.
                Node* neighbor = new Node(newRow, newCol, current->getDistanceTraveled() + 1);

                // If the neighbor node is not in the closed list, consider it for the open list.
                bool inClosedList = closedList.containsNode(neighbor);

                if (!inClosedList) {
                    bool inOpenList = openList.containsNode(neighbor);

                    // Add the neighbor node to the open list if it's not already there.
                    if (!inOpenList) {
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

    // Save the nodes that have been explored (those in the closed list).
    delete nodesExplored;
    nodesExplored = new NodeList(closedList);

    // Clean up the dynamically allocated memory.
    delete start;
    delete goal;
}



// Method: getNodesExplored
// This method returns a deep copy of the nodesExplored list.
NodeList* PathSolver::getNodesExplored() {
    // Create a new NodeList instance as a copy of the nodesExplored.
    NodeList* copyList = new NodeList(*nodesExplored);
    
    // Return the copy of nodesExplored.
    return copyList;
}

// Function: getPath
// This function finds the shortest path from start to goal using the explored nodes from forwardSearch function.
NodeList* PathSolver::getPath(Env env) {
    // Initialize a new NodeList object to store the path.
    NodeList* path = new NodeList();
    
    // Initialize a Node pointer to store the goal node.
    Node* goalNode = nullptr;

    // Iterate over the explored nodes to find the goal node.
    for(int i = 0; i < nodesExplored->getLength(); i++) {
        Node* node = nodesExplored->getNode(i);
        if(env[node->getRow()][node->getCol()] == SYMBOL_GOAL) {
            // Set goalNode to the current node if it is the goal node.
            goalNode = node;
        }
    }

    // If a goal node was found
    if(goalNode != nullptr) {
        // Start with the goal node and work backwards to find the path.
        Node* currentNode = goalNode;
        
        // Initialize a temporary NodeList object to store the path in reverse.
        NodeList* tempPath = new NodeList();

        // Add the goal node to tempPath.
        tempPath->addElement(currentNode);

        // Continue until the start node (whose distance traveled is 0) is reached.
        while(currentNode->getDistanceTraveled() > 0) {
            // Define the direction vectors for the neighboring positions (up, right, down, left).
            int dx[4] = {0, 1, 0, -1};
            int dy[4] = {-1, 0, 1, 0};
            
            bool foundValidNeighbor = false;

            // Iterate over the neighboring positions.
            for (int i = 0; i < 4 && !foundValidNeighbor; i++) {
                int newRow = currentNode->getRow() + dy[i];
                int newCol = currentNode->getCol() + dx[i];

                // Check if the new position is within the bounds of the environment.
                bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM;

                if (validPosition) {
                    // Iterate over the explored nodes to find a valid neighbor.
                    for(int j = 0; j < nodesExplored->getLength() && !foundValidNeighbor; j++) {
                        Node* node = nodesExplored->getNode(j);

                        // Check if this node is a neighbor of the current node and its distance traveled is one less than the current node's.
                        if(node->getRow() == newRow && node->getCol() == newCol && node->getDistanceTraveled() == currentNode->getDistanceTraveled() - 1) {
                            currentNode = node;
                            foundValidNeighbor = true;
                        }
                    }
                }
            }
            if (foundValidNeighbor) {
                // Only add the node to the path if a valid neighbor was found.
                tempPath->addElement(currentNode);
            }
        }

        // Reorder tempPath from start to finish and assign it to path.
        for(int i = tempPath->getLength() - 1; i >= 0; i--) {
            path->addElement(tempPath->getNode(i));
        }
        
        // Delete tempPath as it is no longer needed.
        delete tempPath;
    }

    // Return the path.
    return path;
}


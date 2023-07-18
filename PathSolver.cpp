#include "PathSolver.h"
#include <iostream>
#include <climits>

/*
 * Constructor implementation for PathSolver
 */
PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

/*
 * Destructor implementation for PathSolver
 */
PathSolver::~PathSolver(){
    delete nodesExplored;
}

/*
 * Method: forwardSearch
 * Performs the pathfinding search on the environment using the algorithm
 */
void PathSolver::forwardSearch(Env env) {
    /*
     * Define Node pointers for start and goal nodes
     * Iterate over the environment grid to find the start and goal positions
     */
    Node* start = nullptr;
    Node* goal = nullptr;
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            if (env[i][j] == SYMBOL_START) {
                start = new Node(i, j, 0);
            } 
            else if (env[i][j] == SYMBOL_GOAL) {
                goal = new Node(i, j, 0);
            }
        }
    }

    /*
     * Initialize the open and closed lists for the algorithm
     * Add the start node to the open list to begin the algorithm
     */
    NodeList openList;
    NodeList closedList;
    openList.addElement(start);
    bool goalReached = false;

    /*
     * Main loop of the algorithm
     * Continues until the open list is empty or the goal is reached
     */
    while (openList.getLength() > 0 && !goalReached) {
        /*
         * The current node is the node from the open list with the smallest estimated distance to the goal
         * Find this node in the open list
         */
        Node* current = nullptr;
        int smallestDistance = INT_MAX;
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

        /*
         * Move the current node from the open list to the closed list
         * Check if the current node is the goal, and update the boolean accordingly
         * If the current node is not the goal, explore its neighbors
         */
        openList.removeElement(current);
        closedList.addElement(current);
        bool isGoal = current->isGoal(goal);
        goalReached = isGoal;
        int row = current->getRow();
        int col = current->getCol();
        int dx[4] = {0, 0, -1, 1};
        int dy[4] = {-1, 1, 0, 0};
        for (int i = 0; i < 4; i++) {
            int newRow = row + dy[i];
            int newCol = col + dx[i];
            bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM &&
                                 env[newRow][newCol] != SYMBOL_WALL;
            if (validPosition) {
                Node* neighbor = new Node(newRow, newCol, current->getDistanceTraveled() + 1);
                bool inClosedList = closedList.containsNode(neighbor);
                if (!inClosedList) {
                    bool inOpenList = openList.containsNode(neighbor);
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

    /*
     * Save the nodes that have been explored (those in the closed list)
     * Clean up the dynamically allocated memory
     */
    delete nodesExplored;
    nodesExplored = new NodeList(closedList);
    delete start;
    delete goal;
}


/*
 * Method: getNodesExplored
 * Returns a deep copy of the nodesExplored list
 */
NodeList* PathSolver::getNodesExplored() {
    NodeList* copyList = new NodeList(*nodesExplored);
    return copyList;
}

/*
 * Method: getPath
 * Finds the shortest path from start to goal using the explored nodes from forwardSearch function
 */
NodeList* PathSolver::getPath(Env env) {
    /*
     * Initialize a NodeList to store the path and a Node pointer for the goal node
     * Find the goal node in the list of nodes explored
     */
    NodeList* path = new NodeList();
    Node* goalNode = nullptr;
    for(int i = 0; i < nodesExplored->getLength(); i++) {
        Node* node = nodesExplored->getNode(i);
        if(env[node->getRow()][node->getCol()] == SYMBOL_GOAL) {
            goalNode = node;
        }
    }

    /*
     * If the goal node was found in the list of explored nodes, 
     * trace the path back from the goal node to the start node by examining the distance traveled by each node
     * Add each node to the path as it is identified
     */
    if(goalNode != nullptr) {
        Node* currentNode = goalNode;
        NodeList* tempPath = new NodeList();
        tempPath->addElement(currentNode);
        while(currentNode->getDistanceTraveled() > 0) {
            int dx[4] = {0, 1, 0, -1};
            int dy[4] = {-1, 0, 1, 0};
            bool foundValidNeighbor = false;
            for (int i = 0; i < 4 && !foundValidNeighbor; i++) {
                int newRow = currentNode->getRow() + dy[i];
                int newCol = currentNode->getCol() + dx[i];
                bool validPosition = newRow >= 0 && newRow < ENV_DIM && newCol >= 0 && newCol < ENV_DIM;
                if (validPosition) {
                    for(int j = 0; j < nodesExplored->getLength() && !foundValidNeighbor; j++) {
                        Node* node = nodesExplored->getNode(j);
                        if(node->getRow() == newRow && node->getCol() == newCol && node->getDistanceTraveled() == currentNode->getDistanceTraveled() - 1) {
                            currentNode = node;
                            foundValidNeighbor = true;
                        }
                    }
                }
            }
            if (foundValidNeighbor) {
                tempPath->addElement(currentNode);
            }
        }
        /*
         * Once the entire path has been identified,
         * add the nodes from the temporary path to the final path in reverse order
         */
        for(int i = tempPath->getLength() - 1; i >= 0; i--) {
            path->addElement(tempPath->getNode(i));
        }
        delete tempPath;
    }
    return path;
}


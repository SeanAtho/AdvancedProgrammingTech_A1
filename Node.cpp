#include "Node.h"
#include <iostream>

/*
 * Constructor for the Node class. Initializes the node with row, column and distance traveled.
 * All initialization is done in the member initializer list.
 */
Node::Node(int row, int col, int dist_traveled) 
: row(row), col(col), dist_traveled(dist_traveled)
{
}


/*
 * Destructor for the Node class. 
 * No dynamically allocated resources are present, so no cleanup is required.
 */
Node::~Node(){
}

/*
 * Getter for the 'row' field of the node.
 */
int Node::getRow(){
    return row;
}

/*
 * Getter for the 'col' field of the node.
 */
int Node::getCol(){
    return col;
}

/*
 * Getter for the 'dist_traveled' field of the node.
 */
int Node::getDistanceTraveled(){
    return dist_traveled;
}

/*
 * Setter for the 'dist_traveled' field of the node.
 */
void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

/*
 * Computes and returns the estimated distance from the current node to the goal node.
 */
int Node::getEstimatedDist2Goal(Node* goal){
    /*
     * If the goal node is null, throw an exception.
     */
    if (goal == nullptr) {
        throw std::invalid_argument("Goal node is a null pointer.");
    }
    /*
     * Calculate the Manhattan distance between this node and the goal node.
     * Return the estimated distance by adding the current distance traveled to the Manhattan distance.
     */
    int manhattanDistance = abs(row - goal->getRow()) + abs(col - goal->getCol());
    return dist_traveled + manhattanDistance;
}
    
//--------------------------------                             


/*
 * Checks if the current node is the goal node.
 * Returns true if the row and column of the current node match the row and column of the goal node.
 */
bool Node::isGoal(Node* goal) {
    return (row == goal->getRow()) && (col == goal->getCol());
}

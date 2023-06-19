#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <cassert>


/*
 * Constructs a new Node object with specified row, col, and distance traveled
 */
Node::Node(int row, int col, int dist_traveled)
    : row(row), col(col), dist_traveled(dist_traveled)
{
    // Ensure all parameters are initialized
    assert(row >= 0);
    assert(col >= 0);
    assert(dist_traveled >= 0);
}


/*
 * Node destructor
 */
Node::~Node(){
    // Since Node doesn't have dynamic allocated member, nothing to do here.
}

/*
 * Returns the row of the node.
 */
int Node::getRow()
{
    return this->row;
}


/*
 * Returns the column of the node.
 */
int Node::getCol()
{
    return this->col;
}


/*
 * Returns the distance traveled to reach this node.
 */
int Node::getDistanceTraveled()
{
    return this->dist_traveled;
}


/*
 * Sets the distance traveled to reach this node.
 * @param dist_traveled: The distance that has been traveled.
 */
void Node::setDistanceTraveled(int dist_traveled)
{
    // Ensure that dist_traveled is initialized at the point of declaration
    assert(dist_traveled >= 0);

    // Set the member variable with the input parameter
    this->dist_traveled = dist_traveled;
}


// Calculate the estimated distance to goal.
// It sums the distance traveled and the Manhattan distance from this node to the goal.
int Node::getEstimatedDist2Goal(Node* goal) {
    // Ensure that goal is not a null pointer
    assert(goal != nullptr);
    
    // Calculate Manhattan distance
    int manhattanDistance = std::abs(this->getRow() - goal->getRow()) + std::abs(this->getCol() - goal->getCol());
    
    // Return the sum of distance traveled and Manhattan distance
    return this->getDistanceTraveled() + manhattanDistance;
}


//--------------------------------                             
#include "Node.h"
#include <iostream>


Node::Node(int row, int col, int dist_traveled) 
: row(row), col(col), dist_traveled(dist_traveled)
{
    // Constructor implementation
}

Node::~Node(){
    // Destructor implementation
}

int Node::getRow(){
    return row;
}

int Node::getCol(){
    return col;
}

int Node::getDistanceTraveled(){
    return dist_traveled;
}

void Node::setDistanceTraveled(int dist_traveled)
{
    this->dist_traveled = dist_traveled;
}

int Node::getEstimatedDist2Goal(Node* goal){
    // Calculate the Manhattan distance between this node and the goal node
    int manhattanDistance = abs(row - goal->getRow()) + abs(col - goal->getCol());

    // Return the estimated distance by adding the current distance traveled to the Manhattan distance
    return dist_traveled + manhattanDistance;
}
    
//--------------------------------                             

bool Node::isGoal(Node* goal) {
    return (row == goal->getRow()) && (col == goal->getCol());
}

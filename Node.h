#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"


/*
 * Class Node
 * This class represents a node in a graph. Each node has row and column coordinates,
 * as well as the distance it has traveled from the start node.
 */
class Node{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    /*
     * Node constructor
     * Initializes a new node with the specified row and column coordinates and distance traveled.
     * @param int row: The row-coordinate of the node.
     * @param int col: The column-coordinate of the node.
     * @param int dist_traveled: The distance that has been traveled from the start node.
     */
    Node(int row, int col, int dist_traveled);

    /*
     * Node destructor
     */
    ~Node();

    /*
     * Function getRow
     * Returns the row-coordinate of the node.
     */
    int getRow();

    /*
     * Function getCol
     * Returns the column-coordinate of the node.
     */
    int getCol();

    /*
     * Function getDistanceTraveled
     * Returns the distance traveled from the start node.
     */
    int getDistanceTraveled();

    /*
     * Function setDistanceTraveled
     * Sets the distance traveled from the start node.
     * @param int dist_traveled: The new distance to be set.
     */
    void setDistanceTraveled(int dist_traveled);

    /*
     * Function getEstimatedDist2Goal
     * Returns the estimated distance to the goal node.
     * This is calculated as the sum of the Manhattan distance to the goal and the distance traveled.
     * @param Node* goal: The goal node.
     */
    int getEstimatedDist2Goal(Node* goal);

    /*
     * Function isGoal
     * Checks if the current node is the goal node.
     * @param Node* goal: The goal node.
     */
    bool isGoal(Node *goal);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    int row;            // The row-coordinate of the node
    int col;            // The column-coordinate of the node
    int dist_traveled;  // The distance from the start node

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */

};

#endif //COSC_ASSIGN_ONE_NODE
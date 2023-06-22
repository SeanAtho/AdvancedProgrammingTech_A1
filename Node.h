#ifndef COSC_ASSIGN_ONE_NODE
#define COSC_ASSIGN_ONE_NODE

#include "Types.h"

class Node{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    Node(int row, int col, int dist_traveled);
    ~Node();

    // get row-coodinate of the node
    int getRow();

    // get column-coodinate of the node
    int getCol();

    //getter and setter for distance traveled
    int getDistanceTraveled();
    void setDistanceTraveled(int dist_traveled);

    //getter for estimated dist to goal - need to return -> Manhatten distance + distance traveled
    int getEstimatedDist2Goal(Node* goal);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */ 

    // Overloads the equality operator to compare two Node objects. 
    // Returns true if the Node objects have the same row and column coordinates, 
    // false otherwise.
    bool operator==(const Node& other) const;


    // Set the parent of the node
    void setParent(Node* parent);

    // Get the parent of the node
    Node* getParent();

    
private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    int row;
    int col;
    int dist_traveled;  // distance from start node

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */


    // Add a parent node pointer
    Node* parent;
};

#endif //COSC_ASSIGN_ONE_NODE
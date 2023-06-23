#ifndef COSC_ASSIGN_ONE_NODELIST
#define COSC_ASSIGN_ONE_NODELIST

#include "Types.h"
#include "Node.h"

// NodeList class encapsulates a list of nodes and provides 
// functionalities such as adding a node to the list, retrieving a node
// by its index, and checking if a particular node is in the list.
class NodeList{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    // Constructor/Desctructor
    NodeList();
    ~NodeList();

    // Copy Constructor
    // Produces a DEEP COPY of the NodeList
    NodeList(NodeList& other);

    // Number of elements in the NodeList
    int getLength();

    // Add a COPY node element to the BACK of the nodelist.
    void addElement(Node* newNode);

    // Get a pointer to the ith node in the node list
    Node* getNode(int i);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    
    // Checks if the provided node is in the NodeList.
    // Returns true if found, false otherwise.
    bool isNodeInList(Node& node) const;

    // Removes the node at the given index from the NodeList.
    Node* removeNodeByIndex(int index);

    // Returns the node in NodeList with the minimum estimated 
    // distance to the provided goal node, excluding nodes in the closed list.
    Node* getNodeWithMinDist(Node* goal, const NodeList& closedList);

    // Returns the index of the provided node in the NodeList.
    int getNodeIndex(Node* node);
    
private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    // NodeList: list of node objects
    // You may assume a fixed size for M1, M2, M3
    Node* nodes[NODE_LIST_ARRAY_MAX_SIZE];

    // Number of nodes currently in the NodeList
    int length;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
};




#endif //COSC_ASSIGN_ONE_NODELIST
#ifndef COSC_ASSIGN_ONE_NODELIST
#define COSC_ASSIGN_ONE_NODELIST

#include "Types.h"
#include "Node.h"

class NodeList{
public:
    /*                                           */
    /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
    /*                                           */

    /*
     * Constructor to initialize a NodeList object
     */
    NodeList();

    /*
     * Destructor to delete a NodeList object
     */
    ~NodeList();

    /*
     * Copy Constructor to create a DEEP COPY of a NodeList object
     */
    NodeList(NodeList& other);

    /*
     * Function to get the number of elements in the NodeList
     */
    int getLength();

    /*
     * Function to add a COPY node element to the BACK of the NodeList
     */
    void addElement(Node* newNode);

    /*
     * Function to remove a specific element from the NodeList
     */
    void removeElement(Node *node);

    /*
     * Function to get a pointer to the ith node in the NodeList
     */
    Node* getNode(int i);


    /*
     * Function to check if a specific node is contained in the NodeList
     */
    bool containsNode(Node *node);

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
    


private:
    /*                                           */
    /* DO NOT MOFIFY THESE VARIABLES             */
    /*                                           */

    /*
     * NodeList: list of node objects.
     * Assuming a fixed size for M1, M2, M3.
     */
    Node* nodes[NODE_LIST_ARRAY_MAX_SIZE];

    /*
     * Variable to hold the number of nodes currently in the NodeList
     */
    int length;

    /*                                           */
    /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
    /*                                           */
};




#endif //COSC_ASSIGN_ONE_NODELIST
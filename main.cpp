#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <set>
#include <utility>
#include <vector>


#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);
    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathSolver* pathSolver = nullptr;
    pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = nullptr;
    solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    delete pathSolver;
    delete exploredPositions;
    delete solution;

}

/*
 * Function: readEnvStdin
 * ----------------------
 * Reads the environment from standard input.
 * Input is read into the provided 2D array 'env'.
 */
void readEnvStdin(Env env) {
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            std::cin >> env[i][j];
        }
    }
}


/*
 * Function: printEnvStdout
 * ------------------------
 * Prints the environment to standard output.
 * The environment is read from the provided 2D array 'env'
 * and printed to the console.
 * The 'solution' parameter is currently unused.
 */
void printEnvStdout(Env env, NodeList* solution) {
    //TODO
    for (int i = 0; i < ENV_DIM; ++i) {
        for (int j = 0; j < ENV_DIM; ++j) {
            std::cout << env[i][j];
        }
        std::cout << "\n";
    }
}

// Function to test Node class
void testNode() {
    // Start of Node test
    std::cout << "TESTING Node" << std::endl;

    // Create a Node instance with (row, col, distanceTraveled) = (1, 1, 2)
    Node* node = nullptr;
    node = new Node(1, 1, 2);
    // Print the values of the Node
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    // Clean up the Node instance
    delete node;

    // Create another Node instance with different values
    node = new Node(4, 2, 3);
    // Print the values of the new Node
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    // Clean up the Node instance
    delete node;
}


// Function to test NodeList class
void testNodeList() {
    // Start of NodeList test
    std::cout << "TESTING NodeList" << std::endl;

    // Create a NodeList instance
    NodeList* nodeList = nullptr;
    nodeList = new NodeList();
    // Print the initial size of NodeList
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Create a Node and add it to NodeList
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    // Print the size of NodeList after adding a node
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Create another Node and add it to NodeList
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    // Print the size of NodeList after adding another node
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Get the second Node from NodeList and print its values
    try {
        Node* getB = nodeList->getNode(1);
        std::cout << getB->getRow() << ",";
        std::cout << getB->getCol() << ",";
        std::cout << getB->getDistanceTraveled() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Create more Nodes and add them to NodeList
    Node* b3 = new Node(3, 4, 2);
    nodeList->addElement(b3);
    Node* b4 = new Node(2, 2, 3);
    nodeList->addElement(b4);
    // Print the size of NodeList after adding more nodes
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl; // should be 4

    // Test the function that checks if a specific Node is in the NodeList
    Node testNode(1, 1, 1);
    if (nodeList->isNodeInList(testNode)) {
        std::cout << "Node is in the list" << std::endl;
    } else {
        std::cout << "Node is not in the list" << std::endl;
    }

    // Test the function that removes a Node from NodeList by its index
    try {
        nodeList->removeNodeByIndex(1);
        // Print the size of NodeList after removing a node
        std::cout << "NodeList size after removal: " << nodeList->getLength() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Test getNode function with an out-of-bound index
    try {
        nodeList->getNode(10); // Assuming the NodeList size is less than 10
    } catch (std::out_of_range& e) {
        // Print the caught exception
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Test adding a node to a full NodeList
    NodeList* fullList = nullptr;
    fullList = new NodeList();
    for (int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; ++i) {
        Node* node = new Node(i, i, i);
        fullList->addElement(node);
    }
    try {
        std::cout << "Attempting to add a node to a full NodeList..." << std::endl;
        Node* extraNode = new Node(NODE_LIST_ARRAY_MAX_SIZE, NODE_LIST_ARRAY_MAX_SIZE, NODE_LIST_ARRAY_MAX_SIZE);
        fullList->addElement(extraNode);
    } catch (std::length_error& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Clean up: delete NodeList and Node instances
    delete nodeList;
}


void testPathSolver() {
    std::cout << "TESTING PathSolver" << std::endl;

    // Create a more complex environment
    Env env = {
        {'=', '=', '=', '=', 'S', '=', '=', '=', '='},
        {'=', '.', '.', '.', '.', '.', '.', 'G', '='},
        {'=', '.', '=', '=', '=', '=', '.', '=', '='},
        {'=', '.', '=', '=', '=', '=', '.', '=', '='},
        {'=', '=', '=', '=', '=', '=', '=', '=', '='}
    };

    // Create a PathSolver instance
    PathSolver pathSolver;

    // Execute forward search
    pathSolver.forwardSearch(env);

    // Get the explored nodes
    NodeList* exploredNodes = pathSolver.getNodesExplored();

    // Set of expected nodes
    std::set<std::pair<int, int>> expectedNodes = {
        {1, 4}, {1, 5}, {1, 6}, {2, 1}, {2, 6}, {3, 1}, {3, 6}
        // Add all the expected node positions in the form {row, col}
    };

    // Compare the explored nodes with expected nodes
    for (int i = 0; i < exploredNodes->getLength(); ++i) {
        Node* node = exploredNodes->getNode(i);
        if (expectedNodes.find({node->getRow(), node->getCol()}) == expectedNodes.end()) {
            std::cout << "Unexpected node explored: (" << node->getRow() << ", " << node->getCol() << ")\n";
        } else {
            std::cout << "Node explored as expected: (" << node->getRow() << ", " << node->getCol() << ")\n";
        }
    }

    // Don't forget to free the memory
    delete exploredNodes;
}
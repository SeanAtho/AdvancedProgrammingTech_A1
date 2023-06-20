#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

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
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

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
    Node* node = new Node(1, 1, 2);
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
    NodeList* nodeList = new NodeList();
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
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

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
    nodeList->removeNodeByIndex(1);
    // Print the size of NodeList after removing a node
    std::cout << "NodeList size after removal: " << nodeList->getLength() << std::endl;

    // Test getNode function with an out-of-bound index
    try {
        nodeList->getNode(10); // Assuming the NodeList size is less than 10
    } catch (std::out_of_range& e) {
        // Print the caught exception
        std::cout << "Caught exception: " << e.what() << std::endl;
    }

    // Clean up: delete NodeList and Node instances
    delete nodeList;
    delete b1;
    delete b2;
    delete b3;
    delete b4;
}

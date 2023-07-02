#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

/*
 * These are some helper test functions for the code.
 * They are not part of the main code and will be commented out before submission.
 */
void testNode();
void testNodeList();

/*
 * This function reads the environment layout from standard input.
 */
void readEnvStdin(Env env);

/*
 * This function prints the environment layout to standard output,
 * marking the solution path if it exists.
 * It will be implemented for Milestone 3.
 */
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

    /*
     * Load Environment.
     */
    Env env;
    readEnvStdin(env);
    
    /*
     * Attempt to solve using forwardSearch.
     * Note: This will only work if Milestone 2 has been completed.
     */
    PathSolver* pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);

    NodeList* exploredPositions = nullptr;
    exploredPositions = pathSolver->getNodesExplored();

    /*
     * Print the explored positions.
     */
    std::cout << "Explored Positions: " << std::endl;
    for (int i = 0; i < exploredPositions->getLength(); i++) {
        Node* node = exploredPositions->getNode(i);
        std::cout << "Row: " << node->getRow() << ", Col: " << node->getCol() << std::endl;
    }


    /*
     * Attempt to retrieve the path.
     * Note: This will only work if Milestone 3 has been completed.
     */
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    /*
     * Print the environment and the solution.
     */
    NodeList* copiedList = new NodeList(*exploredPositions);
    std::cout << "Copied List Size: " << copiedList->getLength() << std::endl;


    /*
     * Cleanup
     */
    delete pathSolver;
    delete exploredPositions;
    delete solution;
    delete copiedList;
}

/*
 * Function readEnvStdin
 * Reads a given environment from standard input and stores it in the provided 2D array.
 * Also prints out the dimensions of the environment for debugging purposes.
 */
void readEnvStdin(Env env) {
    // Loop through each cell of the environment
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            // Read a character from the standard input and store it in the environment
            char c;
            std::cin >> c;
            env[i][j] = c;
        }
    }

    // For debugging purposes, print out the dimensions of the environment
    std::cout << "Dimensions of environment: " << ENV_DIM << "x" << ENV_DIM << std::endl;
}



/*
 * Function printEnvStdout
 * Prints a given environment to the standard output.
 * If a solution exists and is not empty, it updates the environment to mark the path before printing.
 */
void printEnvStdout(Env env, NodeList* solution) {
    // If the solution exists and is not empty, update the environment to mark the path
    if (solution != nullptr && solution->getLength() > 0) {
        // Loop through the solution list (excluding the last node)
        for (int i = 0; i < solution->getLength() - 1; i++) {
            // Get the current node and the next node in the solution list
            Node* current = solution->getNode(i);
            Node* next = solution->getNode(i + 1);

            // Initialize the direction character to space (' ')
            char direction = ' ';
            // Determine the direction from the current node to the next node and set the direction character
            if (next->getCol() > current->getCol()) {
                direction = '>';  // right
            } else if (next->getCol() < current->getCol()) {
                direction = '<';  // left
            } else if (next->getRow() < current->getRow()) {
                direction = '^';  // up
            } else if (next->getRow() > current->getRow()) {
                direction = 'v';  // down
            }

            // If the current cell is not the start or the goal, mark the path by setting the cell to the direction character
            if (env[current->getRow()][current->getCol()] != SYMBOL_START && 
                env[current->getRow()][current->getCol()] != SYMBOL_GOAL) {
                env[current->getRow()][current->getCol()] = direction;
            }
        }
    }

    // Print the environment to standard output
    // Iterate over the environment's rows
    for (int i = 0; i < ENV_DIM; i++) {
        // Iterate over the environment's columns
        for (int j = 0; j < ENV_DIM; j++) {
            // Print the character in the current cell
            std::cout << env[i][j];
        }
        // Print a newline character at the end of each row
        std::cout << std::endl;
    }
}



/*
 * Function testNode
 * Test the Node class by creating some instances, modifying them, and printing their contents.
 */
void testNode() {
    // Print the message to indicate the beginning of Node class testing
    std::cout << "TESTING Node" << std::endl;

    // Create a new Node object with given row, column, and distance traveled
    Node* node = new Node(1, 1, 2);
    // Print out the row, column, and distance traveled of the node
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    // Clean up the node after usage
    delete node;

    // Create another Node object with different parameters and print out its details
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    // Clean up the node after usage
    delete node;
}

/*
 * Function testNodeList
 * Test the NodeList class by creating an instance, modifying it, and printing its contents.
 */
void testNodeList() {
    // Print the message to indicate the beginning of NodeList class testing
    std::cout << "TESTING NodeList" << std::endl;

    // Create a new NodeList object
    NodeList nodeList;
    // Print the size of the NodeList
    std::cout << "NodeList size: " << nodeList.getLength() << std::endl;

    // Create a Node object and add it to the NodeList, then print the NodeList size
    Node node1(1, 1, 2);
    nodeList.addElement(&node1);
    std::cout << "NodeList size: " << nodeList.getLength() << std::endl;

    // Create another Node object, add it to the NodeList, and print the NodeList size
    Node node2(4, 2, 3);
    nodeList.addElement(&node2);
    std::cout << "NodeList size: " << nodeList.getLength() << std::endl;

    // Iterate through the NodeList and print out the row, column, and distance traveled for each node
    for (int i = 0; i < nodeList.getLength(); i++) {
        Node* node = nodeList.getNode(i);
        if (node != nullptr) {
            std::cout << node->getRow() << "," << node->getCol() << "," << node->getDistanceTraveled() << std::endl;
        } else {
            // Print error message if the node is invalid
            std::cout << "Invalid node." << std::endl;
        }
    }

    // Prompt for the exercise of printing out a NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
    // Print the message to indicate the end of testing
    std::cout << "DONE TESTING" << std::endl;
}


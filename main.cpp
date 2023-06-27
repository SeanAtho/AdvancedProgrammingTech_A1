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

    // Print the explored positions
    std::cout << "Explored Positions: " << std::endl;
    for (int i = 0; i < exploredPositions->getLength(); i++) {
        Node* node = exploredPositions->getNode(i);
        std::cout << "Row: " << node->getRow() << ", Col: " << node->getCol() << std::endl;
    }


    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathSolver->getPath(env);

    printEnvStdout(env, solution);

    // Test the copy constructor of NodeList
    NodeList* copiedList = new NodeList(*exploredPositions);
    std::cout << "Copied List Size: " << copiedList->getLength() << std::endl;

    delete pathSolver;
    delete exploredPositions;
    delete solution;
    delete copiedList;
}

void readEnvStdin(Env env) {
    // Read the environment from standard input (cin)
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            char c;
            std::cin >> c;
            env[i][j] = c;
        }
    }

    // Debug: Print the dimensions of the environment
    std::cout << "Dimensions of environment: " << ENV_DIM << "x" << ENV_DIM << std::endl;
}



void printEnvStdout(Env env, NodeList* solution) {
    // If solution exists, update the environment with the path
    if (solution != nullptr && solution->getLength() > 0) {
        for (int i = 0; i < solution->getLength() - 1; i++) {
            Node* current = solution->getNode(i);
            Node* next = solution->getNode(i + 1);

            char direction = ' ';
            if (next->getCol() > current->getCol()) {
                direction = '>';
            } else if (next->getCol() < current->getCol()) {
                direction = '<';
            } else if (next->getRow() < current->getRow()) {
                direction = '^';
            } else if (next->getRow() > current->getRow()) {
                direction = 'v';
            }

            // If not start or goal, set the cell to the direction
            if (env[current->getRow()][current->getCol()] != SYMBOL_START && 
                env[current->getRow()][current->getCol()] != SYMBOL_GOAL) {
                env[current->getRow()][current->getCol()] = direction;
            }
        }
    }

    // Print the environment to standard output
    for (int i = 0; i < ENV_DIM; i++) {
        for (int j = 0; j < ENV_DIM; j++) {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }
}




void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Node
    Node* b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
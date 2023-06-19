#include "PathSolver.h"
#include <iostream>

// Constructor: Initialize PathSolver with zero nodes.
PathSolver::PathSolver(){
    nodesExplored = new NodeList();
}

// Destructor: Delete all nodes in the PathSolver.
PathSolver::~PathSolver(){
    delete nodesExplored;
}

void PathSolver::forwardSearch(Env env){
    // TODO 
}

// Method for getting a deep copy of the explored NodeList in forward search
NodeList* PathSolver::getNodesExplored(){
    // Deep copy
    NodeList* nodesExploredCopy = new NodeList(*nodesExplored);
    return nodesExploredCopy;
}

// Method for getting the path the robot should travel
NodeList* PathSolver::getPath(Env env){
    // TODO: To be implemented in milestone 3
    return nullptr;
}

//-----------------------------
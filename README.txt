In developing this pathfinding program, my strategy/development proccess entailed tackling the problem
incrementally, breaking it down into manageable tasks addressed one at a time. The process started with 
implementing features in the main file to read in an environment from standard input and print it out 
unmodified.

After confirming that I could correctly read and display the environment, I implemented the Node class.
This was a vital step as the Node class serves as the core building block for the pathfinding algorithm. 
It was essential to ensure that each node could hold and manage its properties effectively, as these 
properties would be crucial in determining the path through the environment.

Next, I took on the challenge of implementing the NodeList class. This task was more complex, as the NodeList 
class had to manage multiple nodes and facilitate operations on them. Ensuring it was well structured and 
functional was crucial to the program's operation.

The implementation of the PathSolver class followed. This step was the most demanding, as it involved the 
actual computation of the path using the provided Psuedocode (A* algorithm). This also involved ensuring 
various edge cases and that the algorithm could handle different environments, including those with 
intricate and complex paths.

After successfully implementing the PathSolver class, I updated the main file to integrate the PathSolver and
have it control the pathfinding process.

Throughout this development process, I encountered several challenges. Memory management emerged as a particular
concern due to Node objects' dynamic allocation and deletion. I also faced difficulties maintaining the 
20x20 grid size constraints when creating intricate test mazes and ensuring comments adhered to a specific 
style guide. However, the most challenging aspect was translating the pseudocode into a working program. 
The development process was a continuous learning and problem-solving journey, bringing together various 
components to build a comprehensive pathfinding solution.

---------------------------------------------------------------------------------------------------------------------

Milestone 3 Tasks and Challenges

Having successfully implemented Milestones 1 and 2, which involved developing the Node class, NodeList class, 
and laying the foundation of the PathSolver class, I embarked on Milestone 3. This milestone was a significant 
leap from the previous ones as it involved the execution of a backtracking algorithm and creating a deep 
copy of the path the robot should travel.

After the forward search algorithm from Milestone 2 had identified all potential paths, I had to develop a way 
to trace back from the goal node to the start node to identify the optimal path. This involved creating a 
mechanism within the PathSolver class to compare each node's heuristic and keep track of the predecessor node, 
enabling the algorithm to navigate back to the source.

The next challenge was creating a deep copy of the optimal path. It was crucial to ensure this was indeed a 
deep copy, meaning changes to the original NodeList wouldn't affect the copied version. This functionality 
allowed the program to maintain a clean and independent record of the optimal path, which could be returned 
and utilized without disrupting the original data.

Milestone 3 brought its share of challenges, however, through iterative testing and debugging, I was able to 
create a robust and efficient backtracking algorithm. This allowed the robot to accurately navigate through 
a variety of complex environments, marking the successful completion of Milestone 3.

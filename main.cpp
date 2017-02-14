#include <iostream>
#include <queue>
#include <utility>
#include "node.h"

using namespace std;

bool checkRepeated(vector<Node>& exploredSet, priority_queue<Node, vector<Node>>& frontier,
		   Node& expandNode) {
  // Check if expanded node is in the explored set
  for (int i = 0; i < exploredSet.size(); ++i) {
    if (expandNode == exploredSet.at(i)) {
      return false;
    }
  }
  // Check if expanded node is in the frontier
  // TODO
  return true;
}

bool run(Node& goalNode, Node& root) {
  
  // Initalize the frontier using the inital state of the problem
  priority_queue<Node, vector<Node>> frontier;
  frontier.push(root);
  // Initalize the explored set to be empty
  vector<Node> exploredSet;
  
  while (1) {
    // If frontier is empty then return failure
    if (frontier.empty()) return false;
    // Choose a leaf node and remove it from the frontier
    Node selectedNode = frontier.top();
    // If node contains a goal state then return the corresponding solution
    if (selectedNode == goalNode) return true;
    // Add the node to the explored set
    exploredSet.push_back(selectedNode);
    // Expand the chosen node and add the resulting node to the frontier
    // Only if they are not already in the frontier or the explored set
    Node expandNode;
    if (selectedNode.move_blank_up(expandNode)) {
      if (!checkRepeated(exploredSet, frontier, expandNode)) {
	// Add the expanded node to the frontier
	frontier.push(expandNode);
      }
    }

    if (selectedNode.move_blank_right(expandNode)) {
      if (!checkRepeated(exploredSet, frontier, expandNode)) {
	// Add the expanded node to the frontier
	frontier.push(expandNode);
      }
    }

    if (selectedNode.move_blank_down(expandNode)) {
      if (!checkRepeated(exploredSet, frontier, expandNode)) {
	// Add the expanded node to the frontier
	frontier.push(expandNode);
      }
    }
     
    if (selectedNode.move_blank_left(expandNode)) {
      if (!checkRepeated(exploredSet, frontier, expandNode)) {
	// Add the expanded node to the frontier
	frontier.push(expandNode);
      }
    }
  }
}

int main() {
  short initialState[9] = {1, 2, 3, 4, 5, 6, 7, 0, 8};
  short goalState[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  

  Node root;
  Node goalNode;
  root.set_state(initialState);
  goalNode.set_state(goalState);

 
  
  return 0;
}

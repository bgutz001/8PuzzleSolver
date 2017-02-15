#include <iostream>
#include <queue>
#include <utility>
#include <cmath>
#include <unordered_map>
#include "node.h"

using namespace std;

void print_trace(Node* n) {
  n->print();
  if (n->get_parent() == 0) {
    n->print();
    return;
  }
  print_trace(n->get_parent());
}

int uniformCost(Node& goalNode, Node& currentNode) {
  return 0;
}

int misplaceTileH(Node& goalNode, Node& currentNode) {
  short* goalState = goalNode.get_state();
  short* currentState = currentNode.get_state();
  short misplacedTiles = 0;

  for (short i = 0; i < 9; ++i) {
    if (goalState[i] != currentState[i]) {
      ++misplacedTiles;
    }
  }

  return misplacedTiles;
}

int manhattanDistanceH(Node& goalNode, Node& currentNode) {
  short* goalState = goalNode.get_state();
  short* currentState = currentNode.get_state();
  int distance = 0;

  for (short i = 0; i < 9; ++i) {
    for (short j = 0; j < 9; ++j) {
      if (goalState[i] == currentState[j]) {
	int temp = abs(i - j);
	distance += (temp/3) + (temp%3);
	//	cout << "i: " << i << " j: " << j << " abs: " << temp << " dist: " << distance << endl;

	break;
      }
    }
  }

  return distance;
}



bool checkRepeated(unordered_map<unsigned long, bool>& expandedSet,
		   Node& expandNode) {
  try {
    if (expandedSet.at(expandNode.get_key()) == true) {
      return false;
    }
  }
  catch (const out_of_range& e) {};
  return true;
}

bool run(Node& goalNode, Node& root, int (*heuristic)(Node&, Node&)) {
  bool solved = false;
  Node selectedNode;
  Node expandNode;

  // Initalize the frontier using the inital state of the problem
  priority_queue<Node, vector<Node>, greater<Node>> frontier;
  frontier.push(root);
  // Initalize the expanded set
  unordered_map<unsigned long, bool> expandedSet;
  cout << "key: " <<  root.get_key() << endl;
  expandedSet.insert(make_pair<unsigned long, bool>(root.get_key(), true));
  
  while (!solved) {
    // If frontier is empty then return failure
    if (frontier.empty()) return false;
    // Choose a leaf node and remove it from the frontier
    selectedNode = frontier.top();
    frontier.pop();
    selectedNode.print();
    // If node contains a goal state then return the corresponding solution
    if (selectedNode == goalNode) {
      solved = true;
    }
    // Expand the chosen node and add the resulting node to the frontier
    // Only if they are not already in the frontier or the explored set
    if (selectedNode.move_blank_up(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Add to the cost based on the heuristic
	expandNode.set_cost(expandNode.get_cost() + heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
      }
    }

    if (selectedNode.move_blank_right(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Add to the cost based on the heuristic
	expandNode.set_cost(expandNode.get_cost() + heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
      }
    }

    if (selectedNode.move_blank_down(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Add to the cost based on the heuristic
	expandNode.set_cost(expandNode.get_cost() + heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
      }
    }
     
    if (selectedNode.move_blank_left(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Add to the cost based on the heuristic
	expandNode.set_cost(expandNode.get_cost() + heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
      }
    }
  }

  cout << "Number of nodes explored: " << expandedSet.size() << endl;
  return true;
}



int main() {
  short initialState[9] = {8, 7, 6, 5, 4, 3, 2, 1, 0};
  short goalState[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  

  Node root;
  Node goalNode;
  root.set_state(initialState);
  goalNode.set_state(goalState);

  if (!run(goalNode, root, &uniformCost)) {
    cout << "Failed to find a solution!" << endl;
  }
 
  
  return 0;
}

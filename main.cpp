#include <iostream>
#include <queue>
#include <utility>
#include <cmath>
#include <unordered_map>
#include "node.h"

using namespace std;

const short INITIAL_STATE[9] = {8, 6, 7, 2, 5, 4, 3, 0, 1};
const short GOAL_STATE[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};


typedef int (*heuristic)(Node&, Node&);

void print_trace(Node* n) {
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

  for (short i = 0; i < 8; ++i) {
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

  // Variables used to hold metadata
  unsigned long numExplored = 0;
  unsigned long numCreated = 0;
  unsigned long maxQueueSize = 0;

  // Initalize the frontier using the inital state of the problem
  priority_queue<Node, vector<Node>, greater<Node>> frontier;
  frontier.push(root);
  // Initalize the expanded set
  unordered_map<unsigned long, bool> expandedSet;
  expandedSet.insert(make_pair<unsigned long, bool>(root.get_key(), true));
  
  while (!solved) {
    // If frontier is empty then return failure
    if (frontier.empty()) return false;
    // Meta Data
    ++numExplored;
    maxQueueSize = max(frontier.size(), maxQueueSize);
    
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
	// Calculate the potential of a node using a heuristic
	expandNode.set_distanceToGoal(heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));

	++numCreated;
      }
    }

    if (selectedNode.move_blank_right(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Calculate the potential of a node using a heuristic
	expandNode.set_distanceToGoal(heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
	
	++numCreated;
      }
    }

    if (selectedNode.move_blank_down(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Calculate the potential of a node using a heuristic
	expandNode.set_distanceToGoal(heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
	
	++numCreated;
      }
    }
     
    if (selectedNode.move_blank_left(expandNode)) {
      if (checkRepeated(expandedSet, expandNode)) {
	// Calculate the potential of a node using a heuristic
	expandNode.set_distanceToGoal(heuristic(goalNode, expandNode));
	// Add the expanded node to the frontier
	frontier.push(expandNode);
	// Add the expanded node to the expanded set
	expandedSet.insert(make_pair<unsigned long, bool>(expandNode.get_key(), true));
	
	++numCreated;
      }
    }
  }
  cout << "solution trace" << endl;
  cout << "Number of nodes explored: " << numExplored << endl;
  cout << "Number of nodes created: " << numCreated << endl;
  cout << "Maximum number of nodes in the queue at any given time: " << maxQueueSize << endl;
  cout << "Depth of the solution was: " << selectedNode.get_cost() << endl;
  
  return true;
}

void get_input(Node& root, heuristic& h) {
  short state[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
  short temp;
  cout << "Type \"1\" to use a default puzzle, or \"2\" to enter your own puzzle." << endl;
  cin >> temp;
  cout << temp << endl;

  while (temp != 1 && temp != 2) {
    cout << "Please type \"1\" or \"2\"" << endl;
    cin >> temp;
  }

  if (temp == 1) {
    root.set_state(INITIAL_STATE);
  }
  else {
    cout << "Enter your puzzle, use a zero to represent the blank" << endl;
    cout << "Enter the first row, use space or tabs between numbers \t\t";
    cin >> state[0] >> state[1] >> state[2];
    cout << "Enter the second row, use space or tabs between numbers \t";
    cin >> state[3] >> state[4] >> state[5];
    cout << "Enter the third row, use space or tabs between numbers \t\t";
    cin >> state[6] >> state[7] >> state[8];

    //tODO
    // Check if entered state is valid
    
    root.set_state(state);
  }

  cout << "Enter your choice of algorithm" << endl;
  cout << "1. Uniform Cost Search" << endl;
  cout << "2. A* with the Misplaced Tile heuristic" << endl;
  cout << "3. A* with the Manhattan Distance heuristic" << endl;
  cin >> temp;

  while (temp != 1 && temp != 2 && temp != 3) {
    cout << "Please type \"1\", \"2\" or \"3\"" << endl;
    cin >> temp;
  }

  if (temp == 1) {
    h = &uniformCost;
  }
  else if (temp == 2) {
    h = &misplaceTileH;
  }
  else {
    h = &manhattanDistanceH;
  }
  
  
}

int main() {
  heuristic h;
  Node root;
  Node goalNode;
  
  goalNode.set_state(GOAL_STATE);
  get_input(root, h);

  if (!run(goalNode, root, h)) {
    cout << "Failed to find a solution!" << endl;
  }
 
  
  return 0;
}

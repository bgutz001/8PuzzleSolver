#include <assert.h>
#include <utility>
#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  cost = 0;
  distanceToGoal = 0;
  key = 0;
}

Node::Node(const Node& n) {
  cost = n.cost;
  for (short i = 0; i < 9; ++i) {
    state[i] = n.state[i];
  }
  key = n.key;
  distanceToGoal = n.distanceToGoal;

}

Node::~Node() {
}

void Node::set_cost(int c) {
  cost = c;
}

int Node::get_cost() {
  return cost;
}

void Node::set_distanceToGoal(int d) {
  distanceToGoal = d;
}

int Node::get_distanceToGoal() {
  return distanceToGoal;
}

void Node::set_state(const short* s) {
  assert(s);
  for (short i = 0; i < 9; ++i) {
    state[i] = s[i];
  }
  updateKey();
}

short* Node::get_state() {
  return state;
}

void Node::set_parent(Node* p) {
  parent = p;
}

Node* Node::get_parent() {
  return parent;
}

unsigned long Node::get_key() {
  return key;
}

bool Node::operator<(const Node& rhs) const {
  if (this->cost + this->distanceToGoal < rhs.cost + rhs.distanceToGoal) {
    return true;
  }
  return false;
}

bool Node::operator>(const Node& rhs) const {
  if (this->cost + this->distanceToGoal > rhs.cost + rhs.distanceToGoal) {
    return true;
  }
  return false;
}


bool Node::operator==(const Node& rhs) const {
  assert(this->state);
  assert(rhs.state);
  for (short i = 0; i < 9; ++i) {
    if (this->state[i] != rhs.state[i])
      return false;
  }
  return true;
}

void Node::updateKey() {
  key = 0;
  for (short i = 0; i < 9; ++i) {
    key = key * 10 + state[i];
  }
}

bool Node::move_blank_up(Node& n) {
  // Find where the blank tile is
  short pos;
  for (short i = 0; i < 9; ++i) {
    if (this->state[i] == 0) {
      pos = i;
    }
  }
  // Check if the blank tile can be moved up
  if (pos < 3)
    return false;

  n = *this;
  swap(n.state[pos], n.state[pos-3]);
  ++n.cost;
  n.updateKey();
  
  return true;
}
  
bool Node::move_blank_right(Node& n) {
  // Find where the blank tile is
  short pos;
  for (short i = 0; i < 9; ++i) {
    if (this->state[i] == 0) {
      pos = i;
    }
  }
  // check if the blank tile can be moved right
  if (pos % 3 == 2)
    return false;

  n = *this;
  swap(n.state[pos], n.state[pos+1]);
  ++n.cost;
  n.updateKey();
  
  return true;
}

bool Node::move_blank_down(Node& n) {
  // Find where the blank tile is
  short pos;
  for (short i = 0; i < 9; ++i) {
    if (this->state[i] == 0) {
      pos = i;
    }
  }
  // check if the blank tile can be moved down
  if (pos > 5)
    return false;

  n = *this;
  swap(n.state[pos], n.state[pos+3]);
  ++n.cost;
  n.updateKey();

  return true;
}

bool Node::move_blank_left(Node& n) {
  // Find where the blank tile is
  short pos;
  for (short i = 0; i < 9; ++i) {
    if (this->state[i] == 0) {
      pos = i;
    }
  }
  // check if the blank tile can be moved left
  if (pos % 3 == 0)
    return false;

  n = *this;
  swap(n.state[pos], n.state[pos-1]);
  ++n.cost;
  n.updateKey();
  
  return true;
}

void Node::print() {
  cout << "Node g(n): " << this->cost << " Node h(n): " << this->distanceToGoal << "\n";
  cout << "Node State:\n";
  for (short i = 0; i < 9; ++i) {
    cout << this->state[i] << ' ';
    if (i % 3 == 2) {
      cout << '\n';
    }
  }
  cout << flush;
}

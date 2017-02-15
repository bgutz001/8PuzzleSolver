#include <assert.h>
#include <utility>
#include <iostream>
#include "node.h"

using namespace std;

Node::Node() {
  parent = 0;
  cost = 0;
  key = 0;
}

Node::Node(const Node& n) {
  cost = n.cost;
  for (short i = 0; i < 9; ++i) {
    state[i] = n.state[i];
  }
  parent = n.parent;
  key = n.key;
}

Node::~Node() {

}

void Node::set_cost(int c) {
  cost = c;
}

int Node::get_cost() {
  return cost;
}

void Node::set_state(short* s) {
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
  if (this->cost < rhs.cost) {
    return true;
  }
  return false;
}

bool Node::operator>(const Node& rhs) const {
  if (this->cost > rhs.cost) {
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

  n.set_state(this->state);
  swap(n.state[pos], n.state[pos-3]);
  n.cost = this->cost + 1;
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

  n.set_state(this->state);
  swap(n.state[pos], n.state[pos+1]);
  n.cost = this->cost + 1;
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

  n.set_state(this->state);
  swap(n.state[pos], n.state[pos+3]);
  n.cost = this->cost + 1;
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

  n.set_state(this->state);
  swap(n.state[pos], n.state[pos-1]);
  n.cost = this->cost + 1;
  n.updateKey();

  return true;
}

void Node::print() {
  cout << "Node cost: " << this->cost << "\n";
  cout << "Node State:\n";
  for (short i = 0; i < 9; ++i) {
    cout << this->state[i] << ' ';
    if (i % 3 == 2) {
      cout << '\n';
    }
  }
  cout << flush;
}

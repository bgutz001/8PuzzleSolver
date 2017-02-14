#include <assert.h>
#include <utility>
#include "node.h"

using namespace std;

Node::Node() {
  parent = 0;
  cost = 0;
};

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
}

short* Node::get_state() {
  return state;
}

bool Node::operator<(const Node& rhs) const {
  if (this->cost <= rhs.cost) {
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

  swap(this->state[pos], this->state[pos-3]);
  n.cost = this->cost + 1;
  n.parent = this;
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

  swap(this->state[pos], this->state[pos+1]);
  n.cost = this->cost + 1;
  n.parent = this;
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

  swap(this->state[pos], this->state[pos+3]);
  n.cost = this->cost + 1;
  n.parent = this;
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

  swap(this->state[pos], this->state[pos-1]);
  n.cost = this->cost + 1;
  n.parent = this;
  return true;
}

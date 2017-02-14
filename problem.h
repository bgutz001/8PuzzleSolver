#include "node.h"
#include <queue>

class Problem {
 private:
  short initalState[9];
  short goalState[9];
 public:
  Problem();
  int solve(); // returns 1 on success; 0 on failure
  void move_up();
  void move_right();
  void move_down();
  void move_left();
}


class Node {
 private:
  Node* parent;
  Node* child[4];
  int cost;
  short state[9];

 public:
  Node();
  void set_cost(int c);
  int get_cost();
  void set_state(short* s);
  short* get_state();
  bool operator<(const Node& rhs) const;
  bool operator==(const Node& rhs) const;

  bool move_blank_up(Node& n);
  bool move_blank_right(Node& n);
  bool move_blank_down(Node& n);
  bool move_blank_left(Node& n);
  
};

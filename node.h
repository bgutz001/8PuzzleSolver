class Node {
 private:
  int cost; // This is g(n). in this case it is also the depth
  int distanceToGoal; // This is h(n). an estimation of how good the current state is
  short state[9];
  unsigned long key;
  Node* parent;
  
  void updateKey();

 public:
  Node();
  Node(const Node& n);
  ~Node();
  void set_cost(int c);
  int get_cost();
  void set_distanceToGoal(int d);
  int get_distanceToGoal();
  void set_state(const short* s);
  short* get_state();
  void set_parent(Node* p);
  Node* get_parent();
  unsigned long get_key();
  bool operator<(const Node& rhs) const;
  bool operator>(const Node& rhs) const;
  bool operator==(const Node& rhs) const;

  bool move_blank_up(Node& n);
  bool move_blank_right(Node& n);
  bool move_blank_down(Node& n);
  bool move_blank_left(Node& n);

  void print();
  
};

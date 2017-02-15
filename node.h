
class Node {
 private:
  Node* parent;
  int cost;
  short state[9];
  unsigned long key;

  void updateKey();

 public:
  Node();
  Node(const Node& n);
  ~Node();
  void set_cost(int c);
  int get_cost();
  void set_state(short* s);
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

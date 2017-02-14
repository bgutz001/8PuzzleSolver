
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
  
};

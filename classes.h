enum lines { NOLINE, SINGLELINE, DOUBLELINE };
enum modes { NOMODE, INT_FLOAT, INT_INT_INT };
enum parameters {
  ELEMENT_LENGTH,
  PI,
  KAPPA,
  LAMBDA,
  IPSILON,
  PSI,
  ALPHA,
  DELTA,
  ETA
};
enum sizes { NODES, ELEMENTS, DIRICHLET };

class item {
 protected:
  int id;
  float x;
  int node1, node2;
  float value;

 public:
  void setId(int identifier) { id = identifier; }

  void setX(float x_coord) { x = x_coord; }

  void setNode1(int node_1) { node1 = node_1; }

  void setNode2(int node_2) { node2 = node_2; }

  void setValue(float value_to_assign) { value = value_to_assign; }

  int getId() const { return id; }

  float getX() const { return x; }

  int getNode1() const { return node1; }

  int getNode2() const { return node2; }

  float getValue() const { return value; }

  // abstract methods
  virtual void setIntFloat(int n, float r) = 0;

  virtual void setIntIntInt(int n1, int n2, int n3) = 0;
};

class node : public item {
 public:
  void setIntFloat(int identifier, float x_coordinate) {
    id = identifier;
    x = x_coordinate;
  }

  void setIntIntInt(int n1, int n2, int n3) {}
};

class element : public item {
 public:
  void setIntFloat(int identifier, float x_coordinate) {}

  void setIntIntInt(int identifier, int n1, int n2) {
    id = identifier;
    node1 = n1;
    node2 = n2;
  }
};

class condition : public item {
 public:
  void setIntFloat(int node_to_apply, float prescribed_value) {
    node1 = node_to_apply;
    value = prescribed_value;
  }

  void setIntIntInt(int n1, int n2, int n3) {}
};

class mesh {
  float parameterss[9];
  int sizes[3];
  node *node_list;
  element *element_list;
  condition *dirichlet_list;

 public:
  void setParameters(float l, float pi, float kappa, float lambda,
                     float ipsilon, float psi, float alpha, float delta,
                     float eta) {
    parameterss[ELEMENT_LENGTH] = l;
    parameterss[PI] = pi;
    parameterss[KAPPA] = kappa;
    parameterss[LAMBDA] = lambda;
    parameterss[IPSILON] = ipsilon;
    parameterss[PSI] = psi;
    parameterss[ALPHA] = alpha;
    parameterss[DELTA] = delta;
    parameterss[ETA] = eta;
  }

  void setSizes(int nnodes, int nelm, int ndirch) {
    sizes[NODES] = nnodes;
    sizes[ELEMENTS] = nelm;
    sizes[DIRICHLET] = ndirch;
  }

  int getSize(int s) { return sizes[s]; }

  float getParameter(int p) { return parameterss[p]; }

  void createData() {
    node_list = new node[sizes[NODES]];
    element_list = new element[sizes[ELEMENTS]];
    dirichlet_list = new condition[sizes[DIRICHLET]];
  }

  node *getNodes() { return node_list; }

  element *getElements() { return element_list; }

  condition *getDirichlet() { return dirichlet_list; }

  node getNode(int i) { return node_list[i]; }

  element getElement(int i) { return element_list[i]; }

  condition getCondition(int i) { return dirichlet_list[i]; }
};
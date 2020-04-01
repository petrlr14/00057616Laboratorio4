#include <iostream>
#include <fstream>
#include "math_tools.h"
#include "display_tools.h"
#include "classes.h"

using namespace std;

void readCoordinates(ifstream& file, int n, item* item_list) {
  int e;
  float r;
  for (int i = 0; i < n; i++) {
    file >> e >> r;
    item_list[i].setIntFloat(e, r);
  }
}

int main() {
  char filename[10];
  string line;
  mesh m;
  ifstream file;
  float k, Q;
  int nnodes, neltos, ndirich, nneu;

  do {
    cout << "Ingrese el noombre del archivo: ";
    cin >> filename;
    file.open(filename);
  } while (!file);

  file >> k >> Q;
  file >> nnodes >> neltos >> ndirich >> nneu;
  file >> line;
  file >> line;
  m.setParameters(k, Q);
  m.setSizes(nnodes, neltos, ndirich, nneu);
  m.createData();
  readCoordinates(file, nnodes, m.getNodes());
  file.close();
  for (int i = 0; i < nnodes; i++) {
    cout << m.getNode(i).getX() << "\n";
  }
  return 0;
}
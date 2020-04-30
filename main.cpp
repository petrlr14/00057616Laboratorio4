#include <iostream>
#include "math_tools.h"
#include "classes.h"
#include "display_tools.h"
#include "tools.h"
#include "sel.h"

void about();

using namespace std;

int main() {
  about();
  mesh mesh;
  Matrix K;
  Vector b;
  Vector T;
  vector<Matrix> localKs;
  vector<Vector> localBs;

  readMeshAndConditions(mesh);

  createLocalSystem(mesh, localKs, localBs);
  cout << "Se creo el sistema local" << endl;
  zeroes(K, mesh.getSize(NODES) * 2);
  zeroes(b, mesh.getSize(NODES) * 2);
  assembly(mesh, localKs, localBs, K, b);
  applyDirichlet(mesh, K, b);

  showMatrix(K);

  /* zeroes(T, b.size());
  calculate(K, b, T);

  cout << "La respuesta es:" << endl;
  showVector(T); */

  return 0;
}

void about() {
  cout << "Implementacion de los metodos finitos" << endl;
  cout << "\t-Ecuaciones de Navier-Stokes." << endl;
  cout << "\t-1 dimension." << endl;
  cout << "\t-Funciones de forma lineales." << endl;
  cout << "\t-Pesos de Galerkin." << endl;
  cout << "************************************************" << endl;
}
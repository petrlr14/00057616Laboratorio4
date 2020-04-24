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
    cout<<"que pex";
//    zeroes(K, mesh.getSize(NODES));
//    zeroes(b, mesh.getSize(NODES));
//
//    createLocalSystem(mesh, localKs, localBs);
//    assembly(mesh, localKs, localBs, K, b);
//
//    applyNeumann(mesh, b);
//    applyDirichlet(mesh, K, b);
//
//    zeroes(T, b.size());
//    calculate(K, b, T);
//
//    cout << "La respuesta es:" << endl;
//    showVector(T);

    return 0;
}

void about() {
    cout << "Implementacion de los metodos finitos" << endl;
    cout << "\t-Transferencia de calor." << endl;
    cout << "\t-1 dimension." << endl;
    cout << "\t-Funciones de forma lineales." << endl;
    cout << "\t-Pesos de Galerkin." << endl;
    cout << "************************************************" << endl;
}
#include <fstream>

void getData(istream &file, int lines, int n, int mode, item *itemList) {
    string line;
    file >> line;
    if (lines == DOUBLELINE) {
        file >> line;
    }
    for (int i = 0; i < n; i++) {
        switch (mode) {
            case INT_FLOAT:
                int e;
                float f;
                file >> e >> f;
                cout<<e<<" "<<f<<endl;
                itemList[i].setIntFloat(e, f);
                break;
            case INT_INT_INT:
                int e1, e2, e3;
                file >> e1 >> e2 >> e3;
                cout<<e1<<" "<<e2<<" "<<e3<<endl;
                itemList[i].setIntIntInt(e1, e2, e3);
                break;
        }
    }
}

void readMeshAndConditions(mesh &mesh) {
    char filename[11];
    ifstream file;
    float k, Q;
    int nnodes, nelem, ndirch, nneu;
    do {
        cout << "Ingrese nombre del archivo: ";
        cin >> filename;
        file.open(filename);
    } while (!file);
    file >> k >> Q;
    file >> nnodes >> nelem >> ndirch >> nneu;
    mesh.setParameters(k, Q);
    mesh.setSizes(nnodes, nelem, ndirch, nneu);
    mesh.createData();
    getData(file, SINGLELINE, nnodes, INT_FLOAT, mesh.getNodes());
    getData(file, DOUBLELINE, nelem, INT_INT_INT, mesh.getElements());
    getData(file, DOUBLELINE, ndirch, INT_FLOAT, mesh.getDirichlet());
    getData(file, DOUBLELINE, nneu, INT_FLOAT, mesh.getNeumann());
    cout<<"Que paso ";
    file.close();
    cout<<"Que paso ";
}
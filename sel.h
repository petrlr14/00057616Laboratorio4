Matrix createLocalK(int element, mesh &mesh) {
    Matrix k;
    Vector row1, row2;
    float K = mesh.getParamenter(THERMAL_CONDUCTIVITY);
    float l = mesh.getNode(element + 1).getX() - mesh.getNode(element).getX();
    float value = K / l;
    row1.push_back(value);
    row1.push_back(-(value));
    row2.push_back(-(value));
    row2.push_back(value);
    k.push_back(row1);
    k.push_back(row2);
    return k;
}

Vector createLocalB(int element, mesh &mesh) {
    Vector b;
    float Q = mesh.getParamenter(HEAT_SOURCE);
    float l = mesh.getNode(element + 1).getX() - mesh.getNode(element).getX();
    b.push_back((Q * (l)) / 2);
    b.push_back((Q * (l)) / 2);
    return b;
}

void createLocalSystem(mesh &mesh, vector<Matrix> &localKs, vector<Vector> &localBs) {
    for (int i = 0; i < mesh.getSize(ELEMENTS); i++) {
        localKs.push_back(createLocalK(i, mesh));
        localBs.push_back(createLocalB(i, mesh));
    }
}

void assemblyK(element e, Matrix &localK, Matrix &K) {
    int index1 = e.getNode1() - 1;
    int index2 = e.getNode2() - 1;
    K.at(index1).at(index1) += localK.at(0).at(0);
    K.at(index1).at(index2) += localK.at(0).at(1);
    K.at(index2).at(index1) += localK.at(1).at(0);
    K.at(index2).at(index2) += localK.at(1).at(1);
}

void assemblyB(element e, Vector &localB, Vector &b) {
    int index1 = e.getNode1() - 1;
    int index2 = e.getNode2() - 1;
    b.at(index1) += localB.at(0);
    b.at(index2) += localB.at(1);
}

void assembly(mesh &mesh, vector<Matrix> &localKs, vector<Vector> &localBs, Matrix &K, Vector &b) {
    for (int i = 0; i < mesh.getSize(ELEMENTS); i++) {
        element e = mesh.getElement(i);
        assemblyK(e, localKs.at(i), K);
        assemblyB(e, localBs.at(i), b);
    }
}

void applyNeumann(mesh &mesh, Vector &b) {
    for (int i = 0; mesh.getSize(NEUMANN); i++) {
        condition c = mesh.getCondition(i, NEUMANN);
        b.at(c.getNode1() - 1) += c.getValue();
    }
}

void applyDirichlet(mesh &mesh, Matrix &K, Vector &b) {
    for (int i = 0; i < mesh.getSize(DIRICHLET); i++) {
        condition c = mesh.getCondition(i, DIRICHLET);
        int index = c.getNode1() - 1;
        K.erase(K.begin() + index);
        b.erase(b.begin() + index);
        for (int row = 0; row < K.size(); row++) {
            float cell = K.at(row).at(index);
            K.at(row).erase(K.at(row).begin() + index);
            b.at(row) += -1 * cell * c.getValue();
        }
    }
}

void calculate(Matrix &K, Vector &b, Vector &T) {
    Matrix Kinv;
    inverse(K, Kinv);
    productMatrixVector(K, b, T);
}
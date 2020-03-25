#include <vector>
#include "math.h"
#include "stdlib.h"

using namespace std;

typedef vector<float> Vector;
typedef vector<Vector> Matrix;

void zeroes(Vector &v, int n) {
  for (int i = 0; i < n; i++) {
    v.push_back(0.0);
  }
}

void zeroes(Matrix &m, int n) {
  for (int i = 0; i < n; i++) {
    Vector row(n, 0.0);
    m.push_back(row);
  }
}

void copyVector(Vector v, Vector &copy) {
  zeroes(copy, v.size());
  for (int i = 0; i < v.size(); i++) copy.at(i) = v.at(i);
}

void copyMatrix(Matrix m, Matrix &copy) {
  zeroes(copy, m.size());
  for (int i = 0; i < m.size(); i++) copyVector(m.at(i), copy.at(i));
}

void productMatrixVector(Matrix A, Vector v, Vector &R) {
  for (int row = 0; row < A.size(); row++) {
    Vector aux = A.at(row);
    float sum = 0.0;
    for (int col = 0; col < A.size(); col++) {
      sum += (aux.at(col) * v.at(col));
    }
    R.at(row) += sum;
  }
}

void productFloatMatrix(Matrix m, float num, Matrix &R) {
  zeroes(R, m.size());
  for (int row = 0; row < m.size(); row++) {
    Vector aux = m.at(row);
    for (int col = 0; col < aux.size(); col++) {
      R.at(row).at(col) = aux.at(col) * num;
    }
  }
}

Vector sumVector(Vector A, Vector B, int n) {
  Vector R;
  zeroes(R, n);
  for (int i = 0; i < n; i++) {
    R.at(i) = A.at(i) + B.at(i);
  }
  return R;
}

Matrix sumMatrix(Matrix A, Matrix B, int rows, int cols) {
  Matrix R;
  zeroes(R, rows);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      R.at(i).at(j) = A.at(i).at(j) + B.at(i).at(j);
    }
  }
  return R;
}

void transpose(Matrix M, Matrix &T) {
  zeroes(T, M.size());
  for (int row = 0; row < M.size(); row++) {
    Vector aux = M.at(row);
    for (int col = 0; col < aux.size(); col++) {
      T.at(col).at(row) = M.at(row).at(col);
    }
  }
}

void getMinor(Matrix &M, int i, int j) {
  M.erase(M.begin() + i);
  for (int i = 0; i < M.size(); i++) {
    M.at(i).erase(M.at(i).begin() + j);
  }
}

float determinant(Matrix M) {
  if (M.size() == 1) {
    return M.at(0).at(0);
  } else {
    float det = 0.0;
    for (int i = 0; i < M.at(0).size(); i++) {
      Matrix minor;
      copyMatrix(M, minor);
      getMinor(minor, 0, i);
      det += pow(-1, i) * M.at(0).at(i) * determinant(minor);
    }
    return det;
  }
}

void cofactors(Matrix M, Matrix &Cof) {
  zeroes(Cof, M.size());
  for (int i = 0; i < M.size(); i++) {
    for (int j = 0; j < M.at(0).size(); j++) {
      Matrix minor;
      copyMatrix(M, minor);
      getMinor(minor, i, j);
      Cof.at(i).at(j) = pow(-1, i + j) * determinant(minor);
    }
  }
}

void inverse(Matrix M, Matrix &invM) {
  float det = determinant(M);
  if (det == 0) exit(EXIT_FAILURE);
  Matrix cof, cofT, R;
  cofactors(M, cof);
  transpose(cof, cofT);
  productFloatMatrix(cofT, (1 / det), invM);
}
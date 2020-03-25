#include <iostream>
#include "math_tools.h"
#include "display_tools.h"

int main() {
  Matrix eg, R;
  zeroes(eg, 3);
  eg.at(0).at(0) = 2;
  eg.at(0).at(1) = 2;
  eg.at(0).at(2) = 3;
  eg.at(1).at(0) = 4;
  eg.at(1).at(1) = 5;
  eg.at(1).at(2) = 6;
  eg.at(2).at(0) = 7;
  eg.at(2).at(1) = 8;
  eg.at(2).at(2) = 9;
  inverse(eg, R);
  showMatrix(R);
  return 0;
}
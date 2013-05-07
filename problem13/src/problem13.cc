#include "src/randomer.h"

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::vector;
using std::pair;

int main() {
  int cases;

  cin >> cases;
  cin.ignore();

  for (int c =0; c < cases; ++c) {
    int n, l;

    cin >> n;
    cin >> l; // length of cases
    cin.ignore();

    vi in;
    for (int i = 0; i < n; ++i) {
      int x;
      cin >> x;
      in.push_back(x);
    }

    Randomer r(in);
    std::cout << "Test case #" << (c+1)<<std::endl;
    for (int i = 0; i < l; ++i) {
      int x, y;
      cin >> x;
      cin >> y;
      std::cout << r.Random(x - 1, y - 1) << std::endl; // fuck 1based indexing
    }
  }

  return 0;
}

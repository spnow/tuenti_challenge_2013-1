#include "src/kerrigan.h"

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
    int w, h, s, c, g;

    cin >> w;
    cin >> h;
    cin >> s;
    cin >> c;
    cin >> g;
    cin.ignore();

    // go do the work
    Kerrigan k(w, h, s, c, g);
    std::cout << k.Kill() << std::endl;
  }

  return 0;
}

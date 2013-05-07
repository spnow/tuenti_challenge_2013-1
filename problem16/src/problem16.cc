#include "src/turinger.h"

#include <iostream>
#include <fstream>
#include <string>

int main() {
  Turinger t;
  std::string s;
  while (! std::cin.eof()) {
    getline(std::cin, s);
    vs in(s.begin(), s.end());
    vs out = t.Turing(in);

    for (char c : out) {
      std::cout << c;
    }
    std::cout << std::endl;
  }

  return 0;
}

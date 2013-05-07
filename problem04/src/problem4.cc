#include "src/grinder.h"

#include <iostream>
#include <string>
#include <sstream>

using std::cin;
typedef vector<string>::iterator QueryIter;

int main() {
  // parse input
  int cases;

  cin >> cases;
  cin.ignore();

  std::vector<int> query;
  for (int i = 0; i < cases; ++i) {
    int num;
    cin >> num;
    cin.ignore();
    query.push_back(num);
  }

  // do the work
  Grinder g;
  std::vector<int>* missing = g.Grind(query);
  for (int i = 0; i < missing->size(); ++i) {
    std::cout << missing->at(i) << std::endl;
  }

  // be nice
  delete missing;
}

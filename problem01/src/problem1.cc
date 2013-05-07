#include "src/profiter.h"

#include <iostream>
#include <string>
#include <sstream>

using std::cin;

int main() {
  Profiter p;
  int cases;

  cin >> cases;
  cin.ignore();

  for (int i =0; i< cases; ++i) {
    std::string line;
    int64_t initial, n;

    // read initial moneyz
    cin >> initial;
    cin.ignore();

    // get a stream of temporal values
    getline(cin, line);
    std::istringstream is(line);
    std::vector<int64_t> input;
    while(is >> n) {
      input.push_back(n);
    }

    // go
    std::cout << p.MaxProfit(initial, &input) << std::endl;
  }

  return 0;
}

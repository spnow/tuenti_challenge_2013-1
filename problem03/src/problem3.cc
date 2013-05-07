#include "src/finder.h"

#include <boost/algorithm/string.hpp>

#include <iostream>
#include <string>
#include <sstream>

using std::cin;

int main() {
  Finder f;

  int cases;
  cin >> cases;
  cin.ignore();

  for (int i =0; i< cases; ++i) {
    vector<string> in;
    std::string line;

    getline(cin, line);
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of(".><"));
    int len = 0;
    for (int i = 1; i < parts.size(); ++i) {
      in.push_back(line[len] + parts[i]);
      len += parts[i].length() + 1;
    }

    vector<string>* r = f.Find(in);

    if (r == NULL) {
      std::cout << "invalid" << std::endl;
    } else if (r->size() == 1 && r->at(0).compare("valid") == 0) {
      std::cout << "valid" << std::endl;
    } else {
      std::cout << r->at(0);
      for (int i = 1; i < r->size(); ++i) {
        std::cout << "," << r->at(i);
      }
      std::cout << std::endl;
    }
    delete r;
  }

  return 0;
}

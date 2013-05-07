#include "src/crawler.h"

#include <boost/algorithm/string.hpp>

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::vector;
using std::pair;

int main() {
  int cases, x, y;
  int n, m;
  int z, g;

  cin >> cases;
  cin.ignore();

  for (int c =0; c < cases; ++c) {
    cin >> n;
    cin.ignore(1);
    cin >> m;
    cin.ignore();

    cin >> x;
    cin.ignore(1);
    cin >> y;
    cin.ignore();

    cin >> z;
    cin.ignore();

    cin >> g;
    cin.ignore();

    // init matrix
    vector<vector<int> > in(n);
    for (int i = 0; i < n; ++i) {
      in[i] = vector<int>(m);
      for (int j = 0; j < m; ++j) {
        in[i][j] = 0;
      }
    }

    // parse gems
    std::string line;
    getline(cin, line);
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of("#"));
    for (int i = 1; i < parts.size(); ++i) {
      int a, b, c;
      sscanf(parts[i].c_str(), "%d,%d,%d", &a, &b, &c);
      in[a][b] = c;
    }

    Crawler c(n, m, z);
    std::cout << c.Crawl(in, pair<int, int>(x, y)) << std::endl;
  }

  return 0;
}

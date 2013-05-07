#include "src/mazer.h"

#include <boost/algorithm/string.hpp>

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>

using std::cin;
using std::vector;
using std::pair;

int main() {
  int cases;
  int h, w;
  int v, t;

  cin >> cases;
  cin.ignore();

  for (int c =0; c < cases; ++c) {
    cin >> w;
    cin.ignore(1);
    cin >> h;
    cin.ignore(1);
    cin >> v;
    cin.ignore(1);
    cin >> t;
    cin.ignore();

    // init matrix
    vector<vector<Map> > in(h);
    std::pair<int, int> pos;
    for (int i = 0; i < h; ++i) {
      in[i] = vector<Map>(w);
      char ch;
      for (int j = 0; j < w; ++j) {
        cin.get(ch);
        if (int(ch) == -62) {
          cin.get(ch); // read the fucking utf-8 dot
          ch = '.'; // don't forget to output the fucking dot
        }

        switch (ch) {
          case '#':
            in[i][j] = WALL;
            break;
          case 'X':
            in[i][j] = ME;
            pos.first = i;
            pos.second = j;
            break;
          case '.':
            in[i][j] = ICE;
            break;
          case 'O':
            in[i][j] = EXIT;
            break;
        }
      }
      cin.ignore();
    }

    Mazer m;
    std::cout << m.Maze(in, w, h, v, t, pos) << std::endl;
  }


  return 0;
}

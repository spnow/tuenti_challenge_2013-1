#include "src/boozzler.h"

#include <boost/algorithm/string.hpp>

#include <cstdio>
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using std::cin;
using std::vector;
using std::pair;


int main() {
  int cases;

  cin >> cases;
  cin.ignore();

  // prepare prefix dawg
  dawgdic::DawgBuilder dawg_builder;
  std::ifstream dict;
  std::string line;
  dict.open ("build/sorted-dict.txt");
  while(!dict.eof()) {
    getline(dict, line);
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    dawg_builder.Insert(line.c_str());
  }
  dict.close();

  // build a dawg for the dict
  dawgdic::Dawg* dawg = new dawgdic::Dawg;
  dawg_builder.Finish(dawg);
  dawgdic::Dictionary* dic = new dawgdic::Dictionary;
  dawgdic::DictionaryBuilder::Build(*dawg, dic);

  for (int c =0; c < cases; ++c) {
    int w[28];
    int dur, n, m;

    std::string line;
    getline(cin, line);
    line = line.substr(1, line.length() - 2); // get rid of {}
    std::remove(line.begin(), line.end(), ' ');
    std::transform(line.begin(), line.end(), line.begin(), ::tolower);
    vector<string> parts;
    boost::split(parts, line, boost::is_any_of(","));

    for (int i = 0; i < parts.size(); ++i) {
      vector<string> inner;
      boost::split(inner, parts[i], boost::is_any_of(":"));
      char ch;
      int val;
      sscanf(parts[i].c_str(), "'%c':%d", &ch, &val);
      w[ch - 'a'] = val;
    }

    cin >> dur;
    cin.ignore(1);
    cin >> n;
    cin.ignore(1);
    cin >> m;
    cin.ignore(1);

    vve board(n);
    for (int i = 0; i < n; ++i) {
      board[i] = vector<Entry*>(m);
      for (int j = 0; j < m; ++j) {
        board[i][j] = NULL;
      }
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        std::string s;
        cin >> s;
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);

        Entry* e = new Entry;
        e->c = (char)s[0];
        e->m = s[1] == '1' ? CHAR : WORD;
        e->mVal = atoi(&s[2]);

        board[i][j] = e;
      }
    }
    cin.ignore(2);

    // go do the work
    Boozzler b(dic);
    std::cout << b.Boozzle(board, w, n, m, dur) << std::endl;
  }

  return 0;
}

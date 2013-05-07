#include "src/suggester.h"

#include <iostream>
#include <string>
#include <sstream>

using std::cin;
typedef vector<string>::iterator QueryIter;

int main() {
    vector<string> queries;
    string line, file;
    int count;

    // parse -- handle case if opopa wants to scr*w us with reordered sections
    while (!cin.eof()) {
      getline(cin, line);

      if (line[0] == '#') {
        // handle comments
        if (line[1] == 'D') {
          // handle Dictionary file
          getline(cin, file);
        } else if (line[1] == 'S') {
          cin >> count;
        } else if (line[1] == 'F') {
          for (int i = 0; i< count; ++i) {
            getline(cin, line);
            queries.push_back(line);
          }
        }
      }
    }

  Suggester s(file);
  for (QueryIter it = queries.begin() ; it != queries.end(); ++it) {
    std::cout << *it << " ->";
    vector<string>* sug = s.Suggest(*it);

    for (vector<string>::iterator si = sug->begin(); si != sug->end(); ++si) {
      std::cout << " " << *si;
    }
    std::cout << std::endl;

    delete sug;
  }

  return 0;
}

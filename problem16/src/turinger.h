#ifndef TURINGER_H
#define TURINGER_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>

#define START -1
#define END   -2
#define BLANK '_'

using std::string;

typedef std::vector<char> vs;
typedef std::pair<int, char> ic;

enum Motion {L, R, S};

typedef struct _trans {
  ic new_state;
  Motion m;
} Transition;

class Turinger {
  public:
    Turinger();
    vs Turing(vs in);

  private:
    std::set<char> g_;
    std::map<ic, Transition*> d_;

    std::map<ic, Transition*> ParseTransitions();
};

#endif  // TURINGER_H

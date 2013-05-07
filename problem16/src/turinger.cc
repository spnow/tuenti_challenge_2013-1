#include "src/turinger.h"

#include <algorithm>
#include <iostream>

#define DEBUG if(0)

Turinger::Turinger() {
  d_ = ParseTransitions();
}

vs Turinger::Turing(vs tape) {
  // simulate the machine

  int state = START;
  int pos = 0;

  int max_used = tape.size()-1;
  while (state != END) {
    // never run out of tape
    if (tape.size() <= pos) {
      for (int i = pos; i < 2*pos; ++i) {
        tape.push_back(BLANK);
      }
    }
    if (d_.find(ic(state, tape[pos])) == d_.end()) {
      std::cerr << "CANNOT FIND TRANSITION" << std::endl;
      std::cout << state << "," << tape[pos] << " pos" << pos;
      exit(1);
    }
    Transition* t = d_[ic(state, tape[pos])];

    // do the transition
    DEBUG std::cout << state << "," << tape[pos] << " -> " <<
      t->new_state.first << " write " << t->new_state.second<< " " <<
      t->m <<  "   ";
    DEBUG for (char c : tape) std::cout << c<< " ";
    DEBUG std::cout << std::endl;

    state = t->new_state.first;
    tape[pos] = t->new_state.second;

    // optimization -- remember last position used for printing
    max_used = std::max(max_used, pos);

    // move the head
    switch (t->m) {
      case L:
        --pos;
        break;
      case R:
        ++pos;
        break;
      case S:  // stay
        break;
    }
  }

  bool found = false;
  pos = 0;
  for (int i = max_used; i >=0; --i) {
    if (!found) {
      if (tape[i] != BLANK) {
        found = true;
        pos = i;
        break;
      }
    }
  }

  return vs(tape.begin(), tape.begin() + pos + 1);
}

std::map<ic, Transition*> Turinger::ParseTransitions() {
  std::ifstream f("build/transitions");
  std::map<ic, Transition*> d;
  while (!f.eof()) {
    Transition* t = new Transition();
    std::string in, out, motion, state, new_state;
    getline(f, state, ',');
    getline(f, in, ':');
    getline(f, out, ',');
    getline(f, motion, ',');
    getline(f, new_state, '\n');
    if (state.length() == 0) {
      continue;
    }

    if (motion.compare("R") == 0) {
      t->m = R;
    } else if (motion.compare("L") == 0) {
      t->m = L;
    } else {
      t->m = S;
    }

    int state1, state2;
    if (state.compare("start") == 0) {
      state1 = START;
    } else if (state.compare("end") == 0) {
      state1 = END;
    } else {
      state1 = std::stoi(state.substr(5));
    }

    if (new_state.compare("start") == 0) {
      state2 = START;
    } else if (new_state.compare("end") == 0) {
      state2 = END;
    } else {
      state2 = std::stoi(new_state.substr(5));
    }
    t->new_state = ic(state2, out[0]);

    d[ic(state1, in[0])] = t;
  }
  return d;
}

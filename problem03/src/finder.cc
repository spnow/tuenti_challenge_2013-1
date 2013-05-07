#include "src/finder.h"

#include<iostream>
#include<set>
#include<fstream>
#include<algorithm>

using std::pair;
using std::string;
using std::set;

typedef struct _node {
  set<string> before;
  set<string> after;
  _node* next;
  _node* prev;
  string value;
} Node;

// Caller is responsable for memory cleanup.
vector<string>* Finder::Find(vector<string>& scenes) {
  vector<string>* s = new vector<string>;
  Node *current = NULL;
  Node *first = NULL;
  Node *last = NULL;
  int total_before = 0;
  int total_after = 0;

  for (vector<string>::iterator i = scenes.begin(); i != scenes.end(); ++i) {
    char start = (*i)[0];

    if (start == '.') {
      Node* n = new Node;
      n->value = i->substr(1);
      n->next = NULL;
      n->prev = NULL;
      if (current != NULL) {
        n->prev = current;
        current->next = n;
      } else {
        first = n;
      }
      current = n;
    } else if (start == '<') {
      if (current == NULL) {
        return NULL; // cannot be before nothing
      }
      ++total_before;
      current->before.insert(i->substr(1));
    } else if (start == '>') {
      if (current == NULL) {
        return NULL; // cannot be after nothing
      }
      current->after.insert(i->substr(1));
      ++total_after;
    } else {
      return NULL;
    }
  }
  last = current;

  // check forward sanity
  set<string> blacklist;
  current = first;
  while (current) {
    blacklist.insert(current->before.begin(), current->before.end());

    // must not contain self as a predecessor
    if (blacklist.find(current->value) != blacklist.end()) {
      return NULL;
    }

    // must not contain any accumulated predecessor in the future
    for(set<string>::iterator i = current->after.begin();
        i != current->after.end(); ++i) {
      if (blacklist.find(*i) != blacklist.end()) {
        return NULL;
      }
    }

    current = current->next;
  }

  // check backward sanity
  blacklist.clear();
  current = last;
  while (current) {
    blacklist.insert(current->after.begin(), current->after.end());

    // must not contain self as a successor
    if (blacklist.find(current->value) != blacklist.end()) {
      return NULL;
    }

    // must not contain any accumulated successor in the future
    for(set<string>::iterator i = current->before.begin();
        i != current->before.end(); ++i) {
      if (blacklist.find(*i) != blacklist.end()) {
        return NULL;
      }
    }

    current = current->prev;
  }

  // check for multiple possible solutions
  // it can only happen that tere are multiple < and >
  // in a unique-solution query IF they are deterministic in a way
  // that they are of a the form:
  //    .A
  //    >B
  //    .C
  //    <B
  // i.e. the only place where B could be is between A and C.
  // If this is not the case, 'valid' should be the output,
  // since having more than 1 < or > that is not deterministic
  // like described will spawn more than one correct solution.
  if (total_before > 1 || total_after > 1) {
    int valid_count = 0;
    int valid_attempt = 0;

    current = first;
    while (current) {
      if (current->after.size() == 1 && current->next) {
        ++valid_attempt;
        if(current->next->before.size() == 1) {
          std::set<string> difference;
          std::set_difference(current->after.begin(), current->after.end(),
                              current->next->before.begin(),
                              current->next->before.end(),
                              std::inserter(difference, difference.begin()));
          if (difference.size() == 0) {
            current->next->before.clear();
            ++valid_count;
          }
        }
      }
      current = current->next;
    }
    if (valid_count != valid_attempt) {
      s->push_back("valid");
      return s;
    }
  }

  // construct result since the only remaining chance is that it's unique
  current = first;
  while (current) {
    s->insert(s->end(), current->before.begin(), current->before.end());
    s->push_back(current->value);
    s->insert(s->end(), current->after.begin(), current->after.end());

    current = current->next;
  }

  return s;
}

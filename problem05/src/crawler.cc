#include "src/crawler.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <functional>

Crawler::Crawler(int n, int m, int z) : N_(n), M_(m), Z_(z) {
}

// Structure neccesarry to run the grap search.
// Idea is the following:
//   * keep the position of the node
//   * keep where we're coming from (not to go back)
//   * keep the health (seconds left); discard node after time is out
//   * keep the current value of the path traversed (a potential max)
//   * keep the list of visited nodes, so coming back yieds 0 points (eaten)
typedef struct _node {
  ii pos;
  ii from;
  int health;
  int value;
  std::set<ii> seen;
} Node;

struct CompareNode : public std::binary_function<Node*, Node*, bool> {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->value < rhs->value;
    }
};

int Crawler::Crawl(vector<vector<int> > G, ii start) {
  std::priority_queue<Node*, vector<Node*>, CompareNode > Q;

  // initial setup
  Node* node = new Node();
  node->pos = start;
  node->from = start;
  node->health = Z_;
  node->value = G[start.first][start.second];
  node->seen.insert(node->pos);
  Q.push(node);

  // run the search
  int max = -1;
  vector<ii> pot;
  while(!Q.empty()) {
    Node* top = Q.top();
    Q.pop();

    // handle dead node
    // this means the time has elapsed for this path and the current value is
    // taken into account for the possible maximum
    if (top->health == 0) {
      max = max < top->value ? top->value : max;
      delete top;
      continue;
    }

    // fill 4 possible directions
    // we can teorieticall go up, down, right, left
    pot.clear();
    pot.push_back(ii(top->pos.first - 1, top->pos.second));
    pot.push_back(ii(top->pos.first + 1, top->pos.second));
    pot.push_back(ii(top->pos.first, top->pos.second + 1));
    pot.push_back(ii(top->pos.first, top->pos.second - 1));

    // enqueue at most 3 new directions (mind not to go back)
    // dont enqueue over the edge as well (G[][] would segfault)
    for (vii::iterator k = pot.begin(); k != pot.end(); ++k) {
      if (*k != node->from
          && k->first >=0 && k->first < N_
          && k->second >=0 && k->second < M_
         ) {
        Node* t = new Node();
        t->pos = *k;
        t->from = top->pos;
        t->seen.insert(top->seen.begin(), top->seen.end());
        t->health = top->health - 1;
        t->value = t->seen.find(t->pos) != t->seen.end() ? top->value :
          top->value + G[t->pos.first][t->pos.second];
        t->seen.insert(t->pos);

        // push the new node with updated fields:
        //  * health decreases each step
        //  * seen nodes are copied from the last + that last, not to duplicate
        //  * set the from/position values for t new node
        Q.push(t);
      }
    }
  }

  return max;
}

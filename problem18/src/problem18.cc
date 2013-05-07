#include <fstream>
#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::vector;

#define DEBUG if (0)

typedef struct _node {
  double w;
  int n;
} Node;

bool BellmanFord(vector<vector<Node*> >);

// Bellman-Ford algorithm with a step from Johnson's algorithm to add a new
// node, connect it with zero-weight (in this case 1 becuase of multiplicating
// percentages), and running BF from there. This is enough to find cycles,
// although it does not find shortest paths (would require the rest of Johnson)
//
// Weights are 1.2 for 20%, 0.7 for -30%.
//
// Node relaxation is done with multiplication, e.g. getting 1*1.2*0.7 is the
// new potential gain. A cycle that has a positive gain must not exist, and
// that is detected in in the weights for going from a node back to itself,
// if there is a negative cycle, there must exist a node where the gain of
// going back itself if bigger than one.
int main() {
  int cases;
  cin >> cases;
  cin.ignore();

  for (int c = 0; c < cases; ++c) {
    int v, e;
    cin >> v;
    cin.ignore();
    cin >> e;
    cin.ignore();

    vector<vector<Node*> > w(v + 1);

    for (int i = 0; i < e; ++i) {
      int from, to, value;
      cin >> from;
      cin >> to;
      cin >> value;
      cin.ignore();
      Node* n = new Node;
      n->w = 1 + 1.0 * value/100.0;
      n->n = to;
      w[from].push_back(n);
    }
    std::cout << (BellmanFord(w) ? "True" : "False") << std::endl;
  }

  return 0;
}

bool BellmanFord(vector<vector<Node*> > w) {
  int v = w.size();
  vector<double> d(v);

  // a new node q is added to the graph, connected by zero-weight edges to each
  // of the other nodes. see johnson's algorithm.
  for (int i = 0; i < v; i++) {
    Node* n = new Node;
    n->w = 1;
    n->n = i;
    w[v - 1].push_back(n);
  }

  // set the new node as a start node for bellman/ford.
  for (int i = 0; i < v - 1; i++) {
    d[i] = 0;
  }
  d[v - 1] = 1;

  // relax nodes
  for (int k = 1; k < v - 1; k++) {
    for (int i = 0; i < v; i++) {
      for (Node* n : w[i]) {
        if (d[n->n] < d[i] * n->w) {
          d[n->n] = d[i] * n->w;
        }
      }
    }
  }

  // if we can relax a node further, there's a negative cycle (energy leak)
  for (int i = 0; i < v; i++) {
    for (Node* n : w[i]) {
      if (d[n->n] < d[i] * n->w) {
        return true;
      }
    }
  }

  return false;
}

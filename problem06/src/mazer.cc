#include "src/mazer.h"

#include <cmath>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <deque>
#include <functional>

typedef struct _node {
  pair<int, int> pos;
  double cost;
  std::set<ii> visited;
} Node;

struct CompareNode : public std::binary_function<Node*, Node*, bool> {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost < rhs->cost;
    }
};

int Round(double v) {
  double diff = v - int(v);
  if (diff <= 0) diff *= -1;
  if (diff > .5) {
    return ceil(v);
  } else{
    return floor(v);
  }
}

// Algorithm is quite simple.
// Do BFS until you expand all possible nodes.
// Then take the minimal solution that succeded.
// Difference from BFS is that we cannot know optimally that the first solution
// is the correct one since we skip more than 1 step in any jump, and incur
// additional costs that BFS does not handle. Easy solutionis just wait till
// all the succeeding paths return.
//
// Usuall -- keep track of position and current path value, seen nodes per path
// so there's no multiple node expansions.
//
// Use a normal Queue.
//
// Code is a bit duplicated but I don't care, it's correct and there's a test.
int Mazer::Maze(vector<vector<Map> > in, int w, int h, int v, int time, ii pos) {
  std::queue<Node*, std::deque<Node*> > Q;

  Node* start = new Node;
  start->pos = pos;
  start->cost = 0;
  Q.push(start);

  int min = INT_MAX;
  while (!Q.empty()) {
    Node* top = Q.front();
    Q.pop();

    if (top->visited.find(top->pos) != top->visited.end()) {
      // no revisiting
      continue;
    }
    top->visited.insert(top->pos);

    // end condition, if we come to the exit
    if (in[top->pos.first][top->pos.second] == EXIT) {
      int candidate = Round(top->cost);
      if (candidate < min) {
        min = candidate;
      }
    }


    // OLA KE ASE?
    // A lot of Duplication here but I am lazy. Sorry:P I have unit tests.
    // find where we can land -- hit the first wall or exit
    // try up - if it's not a wall
    if (top->pos.first - 1 >= 0 &&
        in[top->pos.first -1][top->pos.second] != WALL) {
      int i = top->pos.first - 1;
      int dist = 1;
      while (in[i][top->pos.second] != WALL &&
             in[i][top->pos.second] != EXIT) {
        --i;
        ++dist;
      }
      // if wall, go back from the wall
      if (in[i][top->pos.second] == WALL) {
        ++i;
        --dist;
      }

      // we must find a wall or exist because those are the borders of the maze
      // now push that position to the queue
      Node* t = new Node;
      t->pos = ii(i, top->pos.second);
      t->cost = top->cost + 1.0*dist/v + time;
      t->visited.insert(top->visited.begin(), top->visited.end());
      Q.push(t);
    }
    // dry down
    if (top->pos.first + 1 < h &&
        in[top->pos.first +1][top->pos.second] != WALL) {
      int i = top->pos.first + 1;
      int dist = 1;

      while (in[i][top->pos.second] != WALL &&
             in[i][top->pos.second] != EXIT) {
        ++i;
        ++dist;
      }
      // if wall, go back from the wall
      if (in[i][top->pos.second] == WALL) {
        --i;
        --dist;
      }

      // we must find a wall or exist because those are the borders of the maze
      // now push that position to the queue
      Node* t = new Node;
      t->pos = ii(i, top->pos.second);
      t->visited.insert(top->visited.begin(), top->visited.end());
      t->cost = top->cost + 1.0*dist/v + time;
      Q.push(t);
    }
    // try left
    if (top->pos.second - 1 >= 0 &&
        in[top->pos.first][top->pos.second - 1] != WALL) {
      int i = top->pos.second - 1;
      int dist = 1;
      while (in[top->pos.first][i] != WALL &&
             in[top->pos.first][i] != EXIT) {
        --i;
        ++dist;
      }
      // if wall, go back from the wall
      if (in[top->pos.first][i] == WALL) {
        ++i;
        --dist;
      }

      // we must find a wall or exist because those are the borders of the maze
      // now push that position to the queue
      Node* t = new Node;
      t->pos = ii(top->pos.first, i);
      t->cost = top->cost + 1.0*dist/v + time;
      t->visited.insert(top->visited.begin(), top->visited.end());
      Q.push(t);
    }
    // try right
    if (top->pos.second + 1 < w &&
        in[top->pos.first][top->pos.second + 1] != WALL) {
      int i = top->pos.second + 1;
      int dist = 1;
      while (in[top->pos.first][i] != WALL &&
             in[top->pos.first][i] != EXIT) {
        ++i;
        ++dist;
      }
      // if wall, go back from the wall
      if (in[top->pos.first][i] == WALL) {
        --i;
        --dist;
      }

      // we must find a wall or exist because those are the borders of the maze
      // now push that position to the queue
      Node* t = new Node;
      t->pos = ii(top->pos.first, i);
      t->cost = top->cost + 1.0*dist/v + time;
      t->visited.insert(top->visited.begin(), top->visited.end());
      Q.push(t);
    }
  }

  return min;
}

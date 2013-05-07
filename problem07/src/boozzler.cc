#include "src/boozzler.h"

#include <iostream>
#include <map>
#include <climits>
#include <algorithm>
#include <fstream>
#include <vector>

Boozzler::Boozzler(dawgdic::Dictionary *dic) : dic_(dic) {
}

int Knapsack(int value[], int weight[], int C, int n) {
  vector<vector<int> > M(n+1);
  for(int j = 0; j <n; j++) {
    M[j].resize(C+1);
  }

  for(int i = 1; i <= C; i++) {
    for(int j = 0; j <n; j++) {
      if(j > 0) {
        M[j][i] = M[j-1][i];
        if (weight[j] <= i) {
          M[j][i] = std::max(M[j][i], M[j-1][i-weight[j]]+value[j]);
        }
      }
      else{
        M[j][i] = 0;
        if(weight[j] <= i){
          M[j][i] = std::max(M[j][i], value[j]);
        }
      }
    }
  }

  return M[n-1][C];
}

// puto boozzle
// Step 1: Recursivly find all valid words, starting from each position
// Step 2: Decide which to take using bound knapsack (price = length + 1)
int Boozzler::Boozzle(vve board, int w[28], int n, int m, int dur) {
  vector<Node*> result;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      sii seen;
      FindWords(board, w, n, m, i, j, "", result, 0, 1, seen, dur);
    }
  }

  // remove duplicate words, prefer most scoring ones
  std::map<string, ii> values;
  int new_size = 0;
  for(int i = 0; i< result.size(); ++i) {
    Node* n = result[i];
    if (values.find(n->word) == values.end()) {
      values[n->word] = ii(n->award, n->cost);
      ++new_size;
    } else {
      // replace with current if the award is better
      if (n->award > values[n->word].first) {
        values[n->word] = ii(n->award, n->cost);
      }
    }
  }

  int* value = new int[new_size];
  int* weight = new int[new_size];
  int i = 0;
  for(auto r : values) {
    value[i] = r.second.first;
    weight[i] = r.second.second;;
    ++i;
  }
  int max = Knapsack(value, weight, dur, new_size);
  delete[] value;
  delete[] weight;

  return max;
}

// recursion
void Boozzler::FindWords(vve board, int w[28], int n, int m, int i, int j,
    string c, vector<Node*>& result, int value, int maxWM, sii& seen, int C) {
  // optimize -- dont consider words that have length bigger than our time
  // - 1 for the submit because they are not eligible and helps recursion
  if (c.length() + 1 > C) {
    return;
  }
  Entry* e = board[i][j];

  // bookkeeping
  if (e->m == CHAR) {
    value +=  w[e->c - 'a'] * e->mVal;
  } else {
    value +=  w[e->c - 'a'] * 1;
    maxWM = e->mVal > maxWM ? e->mVal : maxWM;
  }
  c += e->c;

  // is it valid word
  if (dic_->Contains(c.c_str())) {
    Node* t = new Node;
    t->word = c;
    t->award = value * maxWM + c.length(); // Σ(w[i]*cm[i]) * maxWM + j
    t->cost = c.length() + 1; // 1 more second to submit
    result.push_back(t);
  }

  // is it a valid word prefix -- if so, then recurse in all possible ways
  dawgdic::BaseType index = dic_->root();
  if (dic_->Follow(c.c_str(), &index)) {
    vector<ii> new_coords;
    if (i > 0) {
      // up
      new_coords.push_back(ii(i-1, j));
      // up-left
      if (j > 0) {
        new_coords.push_back(ii(i-1, j-1));
      }
      // up-right
      if (j < m-1) {
        new_coords.push_back(ii(i-1, j+1));
      }
    }
    if (i < n-1) {
      // down
      new_coords.push_back(ii(i+1, j));
      // left
      if (j > 0) {
        new_coords.push_back(ii(i+1, j-1));
      }
      // right
      if (j < m-1) {
        new_coords.push_back(ii(i+1, j+1));
      }
    }
    // left
    if (j > 0) {
      new_coords.push_back(ii(i, j-1));
    }
    // right
    if (j < m-1) {
      new_coords.push_back(ii(i, j+1));
    }

    for (int x = 0; x < new_coords.size(); ++x) {
      ii next = new_coords[x];
      if (seen.find(next) == seen.end()) {
        seen.insert(ii(i,j));
        sii new_seen(seen);
        FindWords(board, w, n, m, next.first, next.second, c, result, value,
            maxWM, new_seen, C);
      }
    }
  }
}

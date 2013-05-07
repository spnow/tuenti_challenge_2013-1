#include "src/randomer.h"

#include <algorithm>
#include <iostream>
#include <map>

#define DEBUG if(0)

Randomer::Randomer(vi in): d_(in) {
}

int Randomer::Random(int i, int j) {
  std::map<int,int> counts;
  int max = -1;
  for (int x = i ; x <= j ; x++) {
    if (counts.find(d_[x]) == counts.end()) {
      counts[d_[x]] = 1;
    } else {
      counts[d_[x]] = counts[d_[x]] + 1;
    }
    max = std::max(max, counts[d_[x]]);
  }

  return max;
}

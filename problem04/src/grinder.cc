#include "src/grinder.h"

#include<iostream>
#include<map>
#include<algorithm>
#include<fstream>

using std::pair;
using std::ifstream;
using std::ios;

// Read the whole 8GB file in a bitmap.
// std::bitmap is pretty smart so it does not use
// much space.
Grinder::Grinder() : cursor_(-1), final_(false) {
  cache_ = new int[CACHE_SIZE];
  f_ = fopen("build/integers", "rb");
  flags_ = new std::bitset<2147483648>;

  while (1) {
    int n = Next();
    if (n == -1) {
      break;
    }
    flags_->set(n, true);
  }
  delete[] cache_;
}

Grinder::~Grinder() {
  fclose(f_);
  delete flags_;
}

// First sort the query vector so we can optimally answer,
// then find first n unset bits in the bitmap, which correspond
// to first n missing numbers. Stop after servicing the whole query.
// Caller is responsible for cleaning up memory.
vector<int>* Grinder::Grind(vector<int> pos) {
  vector<int>* missing = new vector<int>;
  std::map<int, int> mappings;

  int index = 0;
  int total = 0;
  for (int i = 0; i < 2^31-1; ++i) {
    if (!(*flags_)[i]) {
      ++index;
      vector<int>::iterator item = std::find(pos.begin(), pos.end(), index);
      if (item != pos.end()) {
        mappings[index] = i;
        total++;
      }
      if (pos.size() == total) {
        break;
      }
    }
  }

  for (int i = 0; i < pos.size(); ++i) {
    missing->push_back(mappings[pos[i]]);
  }

  return missing;
}

// Read smartly, in buckets of CACHE_SIZE.  Reread only when neccesary,
// to minimize read() system calls.
int Grinder::Next() {
  if (cursor_ == -1 || cursor_ >= CACHE_SIZE) {
    if (final_) {
      return -1;
    }
    int size = fread(cache_, sizeof(cursor_), CACHE_SIZE, f_);
    if (size < CACHE_SIZE) {
      final_ = true;
    }
    cursor_ = 0;
  }
  return cache_[cursor_++];
}

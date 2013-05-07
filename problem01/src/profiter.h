#include <stdint.h>
#include <inttypes.h>

#include <vector>

using std::vector;

class Profiter {
  public:
    int64_t MaxProfit(int64_t initial, vector<int64_t> *values);
};


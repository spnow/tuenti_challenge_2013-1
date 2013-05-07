#include "src/profiter.h"

// Find local extremes (monotonically increasing intervals), and
// use the for buy-sell. This is optimal in O(n).
int64_t Profiter::MaxProfit(int64_t initial, std::vector<int64_t> *in) {
    int64_t i, min, max, stocks, moneyz;
    i = stocks = 0;
    moneyz = initial;

    while (i < in->size() - 1) {
      // find fist point of inflection
      while ((i < in->size() - 1) && (in->at(i+1) <= in->at(i)) && ++i);

      min = i++;

      // find end of the interval (next inflection point)
      while ((i < in->size()) && (in->at(i) >= in->at(i-1)) && ++i);

      max = i - 1;

      // buy all at min, sell all at max
      stocks = moneyz/in->at(min);
      moneyz -= stocks * in->at(min);
      moneyz += stocks * in->at(max);
      stocks = 0; // just for consistency
    }

    return moneyz;
}

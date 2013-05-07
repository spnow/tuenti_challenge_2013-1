#include "src/kerrigan.h"

#include <algorithm>

Kerrigan::Kerrigan(int w, int h, int s, int c, int g)
  : w_(w),
    h_(h),
    s_(s),
    c_(c),
    g_(g) {
}

// Very nice problem!
//
// Problem: maximize time choosing #soldiers and #nukes, s.t.
//    s_ * #soldiers + c_ * #nuke <= g_
//
// Solution:
//  * Find max solders that I can buy
//  * For each possible number of soldiers, find number of available nukes
//    and how long it takes for zerg to reach the wall.
//  * Best scenario for that number of soldiers is how long it takes them to
//    come times 1 + number of nukes (so they have to come again)
//  * Solution is the best of the subsolutions
//
//  Kudos to problem maker.
int Kerrigan::Kill() {
  // if we can buy enough soldiers to cover the whole area,
  // all zerglings will be killed at each step, we can last forever
  if (g_ >= w_ * s_) {
    return -1;
  }

  int max_soldiers = std::min(w_, g_ / s_);

  int solution = -1;
  for (int soldiers = 0; soldiers <= max_soldiers; ++soldiers) {
    int zerg_at_gates = (h_ - 1) * w_ / (w_ - soldiers) + 1 ;
    int number_of_nukes = (g_ - soldiers * s_) / c_;

    int potential_solution = zerg_at_gates * (1 + number_of_nukes);
    solution = std::max(solution, potential_solution);
  }

  return solution;
}

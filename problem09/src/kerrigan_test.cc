#include "gtest/gtest.h"

#include "src/kerrigan.h"

TEST(Kerrigan, SimpleDeath) {
  Kerrigan k(10, 20, 50, 100, 400);

  ASSERT_EQ(100, k.Kill());
}

TEST(Kerrigan, Stall) {
  Kerrigan k(10, 20, 50, 100, 500);

  ASSERT_EQ(-1, k.Kill());
}

TEST(Kerrigan, ExpensiveSoldiers) {
  Kerrigan k(2, 87, 999, 2, 1000);

  ASSERT_EQ(43587, k.Kill());
}

TEST(Kerrigan, CornerForSpeedCount) {
  Kerrigan k(872, 728, 2, 62, 1592);

  ASSERT_EQ(19370, k.Kill());
}

TEST(Kerrigan, Breeze) {
  Kerrigan k(5, 20, 100, 10, 400);

  ASSERT_EQ(820, k.Kill());
}

TEST(Kerrigan, ExpensiveNuke) {
  Kerrigan k(72, 268, 68, 1946, 4815);

  ASSERT_EQ(9613, k.Kill());
}

TEST(Kerrigan, Penultimum) {
  Kerrigan k(30, 2693, 10, 100, 100);

  ASSERT_EQ(5386, k.Kill());
}

TEST(Kerrigan, Ultimum) {
  Kerrigan k(99, 5, 267, 281, 691);

  ASSERT_EQ(15, k.Kill());
}

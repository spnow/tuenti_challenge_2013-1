#include "gtest/gtest.h"

#include "src/randomer.h"

TEST(Randomer, Simple) {
  vi ex;
  ex.push_back(1);
  ex.push_back(1);
  ex.push_back(2);
  ex.push_back(4);
  ex.push_back(7);
  ex.push_back(7);
  ex.push_back(11);
  ex.push_back(11);
  ex.push_back(11);
  ex.push_back(15);
  ex.push_back(17);
  ex.push_back(17);
  Randomer r(ex);

  ASSERT_EQ(2, r.Random(0, 4));
  ASSERT_EQ(3, r.Random(6, 8));
}

// no hard cases :)

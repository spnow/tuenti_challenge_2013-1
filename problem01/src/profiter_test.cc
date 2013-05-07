#include "gtest/gtest.h"

#include "src/profiter.h"

TEST(Profiter, Simple) {
  Profiter p;

  std::vector<int64_t> t;
  t.push_back(1);
  t.push_back(2);
  t.push_back(6);
  t.push_back(10);

  ASSERT_EQ(30, p.MaxProfit(3, &t));
}

TEST(Profiter, CannotBuyAtAll) {
  Profiter p;

  std::vector<int64_t> t;
  t.push_back(10);
  t.push_back(9);
  t.push_back(6);
  t.push_back(4);

  ASSERT_EQ(100, p.MaxProfit(100, &t));
}

TEST(Profiter, NoMoney) {
  Profiter p;

  std::vector<int64_t> t;
  t.push_back(1);
  t.push_back(2);
  t.push_back(6);
  t.push_back(10);

  ASSERT_EQ(0, p.MaxProfit(0, &t));
}

TEST(Profiter, Big) {
  Profiter p;

  std::vector<int64_t> t;
  for (int i = 9999999; i > 0; --i) {
    t.push_back(i);
  }

  ASSERT_EQ(100, p.MaxProfit(100, &t));
}

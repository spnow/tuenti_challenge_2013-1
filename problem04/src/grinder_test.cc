#include "gtest/gtest.h"

#include "src/grinder.h"

TEST(Grinder, AllSinceItLoadsInConstructor) {
  Grinder g;

  vector<int> in;
  in.push_back(3);
  in.push_back(98);

  vector<int> exp;
  exp.push_back(9854);
  exp.push_back(2147478824);

  vector<int>* s = g.Grind(in);
  for (int i = 0; i < exp.size(); ++i) {
    EXPECT_EQ(exp[i], s->at(i)) << "Vectors differ at index " << i;
  }

  in.clear();
  in.push_back(4);
  in.push_back(100);

  exp.clear();
  exp.push_back(12009);
  exp.push_back(2147480904);

  s = g.Grind(in);
  for (int i = 0; i < exp.size(); ++i) {
    EXPECT_EQ(exp[i], s->at(i)) << "Vectors differ at index " << i;
  }
  delete s;
}

#include "gtest/gtest.h"

#include "src/mazer.h"

TEST(Mazer, Simple) {
  int n = 5; int m = 4;
  vector<vector<Map> > in(n);

  for (int i = 0; i < n; ++i) {
    in[i] = vector<Map>(m);
    for (int j = 0; j < m; ++j) {
      in[i][j] = ICE;
    }
  }

  for (int i = 0; i < n; ++i) {
    in[i][0] = WALL;
    in[i][m-1] = WALL;
  }
  for (int j = 0; j < m; ++j) {
    in[0][j] = WALL;
    in[n-1][j] = WALL;
  }

  in[3][3] = EXIT;
  in[1][1] = ME;

  Mazer ma;
  ASSERT_EQ(10, ma.Maze(in, m, n, 1, 3, ii(1, 1)));
}

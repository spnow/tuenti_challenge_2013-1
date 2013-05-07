#include "gtest/gtest.h"

#include "src/crawler.h"

TEST(Crawler, Simple) {
    int n = 5; int m = 5;
    vector<vector<int> > in(n);

    for (int i = 0; i < n; ++i) {
      in[i] = vector<int>(m);
      for (int j = 0; j < m; ++j) {
        in[i][j] = 0;
      }
    }

    in[0][0] = 2;
    in[1][0] = 2;
    in[2][0] = 2;
    in[1][1] = 2;
    in[1][2] = 2;
    in[3][2] = 5;
    in[3][3] = 5;

    Crawler c(5, 5, 6);
    ASSERT_EQ(14, c.Crawl(in, ii(2, 2)));
}

TEST(Crawler, CornerCase) {
    int n = 4; int m = 4;
    vector<vector<int> > in(n);

    for (int i = 0; i < n; ++i) {
      in[i] = vector<int>(m);
      for (int j = 0; j < m; ++j) {
        in[i][j] = 0;
      }
    }

    in[1][0] = 5;
    in[1][1] = 1;
    in[2][1] = 2;
    in[1][2] = 1;
    in[3][2] = 2;
    in[2][3] = 5;
    in[3][3] = 2;

    Crawler c(4, 4, 5);
    ASSERT_EQ(12, c.Crawl(in, ii(2, 2)));
}

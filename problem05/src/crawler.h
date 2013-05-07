#include <string>
#include <vector>

using std::string;
using std::vector;

typedef std::pair<int,int> ii;
typedef std::vector<ii> vii;
typedef std::vector<vii> vvii;

class Crawler {
  public:
    Crawler(int n, int m, int z);

    int Crawl(vector<vector<int> > G, ii start);

  private:
    int N_, M_, Z_;
};

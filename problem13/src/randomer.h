#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

class Randomer {
  public:
    Randomer(vi in);

    int Random(int i, int j);

  private:
    vi d_;
};

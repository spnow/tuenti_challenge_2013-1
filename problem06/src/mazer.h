#include <string>
#include <vector>

using std::string;
using std::vector;
using std::pair;

enum Map {ICE, WALL, EXIT, ME};

typedef std::pair<int,int> ii;
typedef std::vector<ii> vii;

class Mazer {
  public:
    int Maze(vector<vector<Map> > in, int w, int h, int v, int t, ii pos);

  private:
};

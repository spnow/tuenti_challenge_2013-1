#include <string>
#include <vector>
#include <set>

using std::string;
using std::vector;
using std::pair;

class Kerrigan {
  public:
    Kerrigan(int w, int h, int s, int c, int g);
    int Kill();

  private:
    int w_, h_, s_, c_, g_;
};

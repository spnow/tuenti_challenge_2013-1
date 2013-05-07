#include <map>
#include <string>
#include <vector>

using std::multimap;
using std::string;
using std::vector;

class Suggester {
  public:
    Suggester(string filename);

    vector<string>* Suggest(string word);

  private:
    multimap<string, string> dict_;
};

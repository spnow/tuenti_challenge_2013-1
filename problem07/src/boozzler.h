#include <string>
#include <vector>
#include <set>

#include <dawgdic/dawg-builder.h>
#include <dawgdic/dictionary-builder.h>

using std::string;
using std::vector;
using std::pair;

enum Multiplier {CHAR = 1, WORD};
typedef struct _entry {
  char c;
  Multiplier m;
  int mVal;
} Entry;
typedef vector<vector<Entry*> > vve;
typedef std::set<string> ss;
typedef pair<int, int> ii;
typedef std::set<ii> sii;

typedef struct _node {
  string word;
  int award;
  int cost;
} Node;

class Boozzler {
  public:
    Boozzler (dawgdic::Dictionary* dic);

    int Boozzle(vve board, int w[28], int n, int m, int dur);

  private:
    dawgdic::Dictionary* dic_;

    void FindWords(vve board, int w[28], int n, int m, int i, int j,
      string c, vector<Node*>& result, int value, int maxWM, sii& seen, int C);
};

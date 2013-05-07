#include <map>
#include <string>
#include <vector>
#include<bitset>

using std::string;
using std::vector;

typedef std::bitset<2147483648> Flags;

#define CACHE_SIZE 939524096

class Grinder {
  public:
    Grinder();
    ~Grinder();

    vector<int>* Grind(vector<int> pos);
    inline int Next();

  private:
    FILE* f_;
    int* cache_;
    int cursor_;
    bool final_;
    Flags* flags_;
};

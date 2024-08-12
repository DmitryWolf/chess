#include "tools.h"
using namespace Tools;

class Board {
public:
    Board();
    ~Board();

    inline virtual void print(const Pieces id = Pieces::noth);

    inline virtual unordered_set<pair<int, int>, hash_pair> getPositions(const boardPieces id);

    static vector<vector<int>> map;
};
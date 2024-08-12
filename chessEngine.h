#include "blackAndWhitePieces.h"

class ChessEngine : protected Piece {
public:
    inline void update();
    inline void updateWhite();
    inline void updateBlack();

    ChessEngine();
    ~ChessEngine();

    inline bool makeSomething(pair<int, int> pos, pair<int, int> from, pair<int, int> to, Pieces piece, Colors col);

    retNewMove getNextMove(Colors col);

    retNewMove makeNextMove(Colors col);

    // предполагаем, что сделан корректный ход\
    защиты от дурака пока что не будет
    void setNextMove(int from1, int from2, int to1, int to2, Colors col);

    void printAttackBoard(Colors col) {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (col == Colors::white) {
                    cout << pw.attackByEnemies[i][j];
                }
                else {
                    cout << pb.attackByEnemies[i][j];
                }
                cout << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

private:
    vector<vector<pair<int, int>>> getAllMoves(Colors col);

    PieceWhite pw;
    PieceBlack pb;

    rnd dist;
};
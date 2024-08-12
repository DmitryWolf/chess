#include "Board.h"

class Piece : public Board {
public:
    vector<unordered_set<pair<int, int>, hash_pair>> figures;
    vector<vector<bool>> attackByEnemies;
    bool isCheck;
    bool isCheckMate;
    bool isStaleMate;

    Piece();
    ~Piece();
    void updateAttackByEnemies(const vector<vector<bool>>& newMap);
protected:
    inline void print(const Pieces id) override final;
    inline unordered_set<pair<int, int>, hash_pair> getPositions(const boardPieces id) override final;
    vector<pair<int, int>> pawnMoves(int i, int j, Colors col);

    vector<pair<int, int>> knightMoves(int i, int j, Colors col);

    vector<pair<int, int>> rookMoves(int i, int j, Colors col);

    vector<pair<int, int>> bishopMoves(int i, int j, Colors col);

    // ������� ����� ��� ����� ��� ����� + ����\
    -30 ����� ����
    vector<pair<int, int>> queenMoves(int i, int j, Colors col);

    vector<pair<int, int>> kingMoves(int i, int j, Colors col);


    bool checkKing(int i, int j, Colors col);

    //protected:
    boardPieces returnFigure(Pieces piece, Colors col);

    // �������� �� ������� �����
    inline bool checkRange(int i, int j);


    // ���������, ��������� �� �� ��������� ������ (����� ������, � ��� �����-�� ����� �����)
    inline bool checkCell(int i, int j, Colors col);

    Colors changeColor(Colors col);

    vector<vector<bool>> getAllAttacks(Colors col);

    void printAttacks();
};
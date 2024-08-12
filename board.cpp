#include "Board.h"
Board::Board() = default;
Board::~Board() = default;

inline void Board::print(const Pieces id) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}
inline unordered_set<pair<int, int>, hash_pair> Board::getPositions(const boardPieces id) {
    unordered_set<pair<int, int>, hash_pair> ret;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (map[i][j] == id) {
                ret.insert({ i, j });
            }
        }
    }
    return ret;
}
vector<vector<int>> Board::map = {
    {boardPieces::blackRook, boardPieces::blackKnight, boardPieces::blackBishop, boardPieces::blackQueen, boardPieces::blackKing, boardPieces::blackBishop, boardPieces::blackKnight, boardPieces::blackRook}, // RANK_8
    {boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn, boardPieces::blackPawn},
    {boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt},
    {boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt},
    {boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt},
    {boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt, boardPieces::empt},
    {boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn, boardPieces::whitePawn},
    {boardPieces::whiteRook, boardPieces::whiteKnight, boardPieces::whiteBishop, boardPieces::whiteQueen, boardPieces::whiteKing, boardPieces::whiteBishop, boardPieces::whiteKnight, boardPieces::whiteRook} // RANK_1
};
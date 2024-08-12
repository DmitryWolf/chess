#include "pieceClass.h"

class PieceWhite : public Piece {
public:
    PieceWhite();
    ~PieceWhite();
    void get(const Pieces id);
    void getAttacks();
};

class PieceBlack : public Piece {
public:
    PieceBlack();
    ~PieceBlack();
    void get(const Pieces id);
    void getAttacks();
};
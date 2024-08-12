#include "blackAndWhitePieces.h"

PieceWhite::PieceWhite() {
    figures[Pieces::pawn] = Piece::getPositions(boardPieces::whitePawn);
    figures[Pieces::knight] = Piece::getPositions(boardPieces::whiteKnight);
    figures[Pieces::bishop] = Piece::getPositions(boardPieces::whiteBishop);
    figures[Pieces::king] = Piece::getPositions(boardPieces::whiteKing);
    figures[Pieces::rook] = Piece::getPositions(boardPieces::whiteRook);
    figures[Pieces::queen] = Piece::getPositions(boardPieces::whiteQueen);
}
PieceWhite::~PieceWhite() = default;
void PieceWhite::get(const Pieces id) {
    this->print(id);
}
void PieceWhite::getAttacks() {
    this->printAttacks();
}

//---

PieceBlack::PieceBlack() {
    figures[Pieces::pawn] = Piece::getPositions(boardPieces::blackPawn);
    figures[Pieces::knight] = Piece::getPositions(boardPieces::blackKnight);
    figures[Pieces::bishop] = Piece::getPositions(boardPieces::blackBishop);
    figures[Pieces::king] = Piece::getPositions(boardPieces::blackKing);
    figures[Pieces::rook] = Piece::getPositions(boardPieces::blackRook);
    figures[Pieces::queen] = Piece::getPositions(boardPieces::blackQueen);
}
PieceBlack::~PieceBlack() = default;
void PieceBlack::get(const Pieces id) {
    this->print(id);
}
void PieceBlack::getAttacks() {
    this->printAttacks();
}
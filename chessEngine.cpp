#include "chessEngine.h"

ChessEngine::ChessEngine() {
    update();
    pw.getAttacks();
    pb.getAttacks();
}
ChessEngine::~ChessEngine() = default;

inline void ChessEngine::update() {
    updateWhite();
    updateBlack();
}
inline void ChessEngine::updateWhite() {
    pw.updateAttackByEnemies(Piece::getAllAttacks(Colors::black));
}
inline void ChessEngine::updateBlack() {
    pb.updateAttackByEnemies(Piece::getAllAttacks(Colors::white));
}

inline bool ChessEngine::makeSomething(pair<int, int> pos, pair<int, int> from, pair<int, int> to, Pieces piece, Colors col) {
    if (col == Colors::white) {
        if (Board::map[to.first][to.second] == boardPieces::empt) {
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pw.figures[Pieces::pawn].erase(from);
            pw.figures[Pieces::pawn].insert(to);
            update();
            if (pw.attackByEnemies[pos.first][pos.second] == false) {
                pw.isCheck = false;
            }
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pw.figures[Pieces::pawn].insert(from);
            pw.figures[Pieces::pawn].erase(to);
            update();
            return !pw.isCheck;
        }
        else {
            auto tempPos = Board::map[to.first][to.second] - 6 - 1;
            pw.figures[Pieces::pawn].erase(from);
            pw.figures[Pieces::pawn].insert(to);
            pb.figures[tempPos].erase(to);
            Board::map[to.first][to.second] = boardPieces::empt;
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            update();
            if (pw.attackByEnemies[pos.first][pos.second] == false) {
                pw.isCheck = false;
            }
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pb.figures[tempPos].insert(to);
            pw.figures[Pieces::pawn].insert(from);
            pw.figures[Pieces::pawn].erase(to);
            update();
            return !pw.isCheck;
        }
    }
    else { // если черные
        if (Board::map[to.first][to.second] == boardPieces::empt) {
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pb.figures[Pieces::pawn].erase(from);
            pb.figures[Pieces::pawn].insert(to);
            update();
            if (pb.attackByEnemies[pos.first][pos.second] == false) {
                pb.isCheck = false;
            }
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pb.figures[Pieces::pawn].insert(from);
            pb.figures[Pieces::pawn].erase(to);
            update();
            return !pb.isCheck;
        }
        else {
            auto tempPos = Board::map[to.first][to.second] - 1;
            pb.figures[Pieces::pawn].erase(from);
            pb.figures[Pieces::pawn].insert(to);
            pw.figures[tempPos].erase(to);
            Board::map[to.first][to.second] = boardPieces::empt;
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            update();
            if (pb.attackByEnemies[pos.first][pos.second] == false) {
                pb.isCheck = false;
            }
            swap(Board::map[from.first][from.second], Board::map[to.first][to.second]);
            pw.figures[tempPos].insert(to);
            pb.figures[Pieces::pawn].insert(from);
            pb.figures[Pieces::pawn].erase(to);
            update();
            return !pb.isCheck;
        }
    }
}

retNewMove ChessEngine::getNextMove(Colors col) {
    update();
    if (col == Colors::white) {
        // если король под шахом
        pair<int, int> newMove;
        auto pos = *pw.figures[Pieces::king].begin();
        if (pw.attackByEnemies[pos.first][pos.second] == true) {
            pw.isCheck = true;
            // 2 выхода: уйти от шаха\
                или закрытьс€ от шаха
                /*
                * если мы можем уйти, то супер
                * далее, если не можем уйти, то провер€ем, можем ли мы закрытьс€ любой из наших фигур
                * если нет, то нам поставили мат
                */ //\
                                                                                                                пытаемс€ уйти королем
            pair<int, int> newPos;
            vector<pair<int, int>> temp = Piece::kingMoves(pos.first, pos.second, col); // получили ходы
            for (auto it : temp) {
                // если нашли куда отойти
                if (pw.attackByEnemies[it.first][it.second] == false) {
                    newPos = it;
                    pw.isCheck = false;
                    return retNewMove(boardPieces::whiteKing, pos.first, pos.second, it.first, it.second);
                }
            }
            // иначе пытаемс€ закрытьс€
            // получаем все возможные ходы
            // пешка
            unordered_set<pair<int, int>, hash_pair> tempSet = pw.figures[Pieces::pawn];
            for (auto it : tempSet) {
                temp = Piece::pawnMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::pawn, col)) {
                        // нашли ход
                        pw.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // конь
            tempSet = pw.figures[Pieces::knight];
            for (auto it : tempSet) {
                temp = Piece::knightMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::knight, col)) {
                        // нашли ход
                        pw.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // слон
            tempSet = pw.figures[Pieces::bishop];
            for (auto it : tempSet) {
                temp = Piece::bishopMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::bishop, col)) {
                        pw.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // ладь€
            tempSet = pw.figures[Pieces::rook];
            for (auto it : tempSet) {
                temp = Piece::rookMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::rook, col)) {
                        pw.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // ферзь
            tempSet = pw.figures[Pieces::queen];
            for (auto it : tempSet) {
                temp = Piece::queenMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::queen, col)) {
                        pw.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            pw.isCheckMate = true;
            return retNewMove(boardPieces::empt, -1, -1, -1, -1);
        }
        else {
            // —ƒ≈Ћј“№ –јЌƒќћ

            // getAllMoves()\
                rand()
            vector<vector<pair<int, int>>> allMoves = getAllMoves(col);
            int cntMoves = 0;
            for (auto it : allMoves) {
                cntMoves += it.size();
            }
            if (cntMoves == 0) {
                pw.isStaleMate = true;
                // јче дальше делать - то?\
                    наверн просто ретурн + проверка в другом файле на сталемате
                return retNewMove(boardPieces::empt, -1, -1, -1, -1);
            }
            // ищем рандомный ход
            int randMove = dist.get_rand() % cntMoves;
            int tempCnt = 0;
            vector<pair<int, int>> temp;
            for (int i = 0; i <= 5; i++) {
                for (auto it : pw.figures[i]) {
                    if ((Pieces)i == Pieces::pawn) {
                        temp = Piece::pawnMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::knight) {
                        temp = Piece::knightMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::bishop) {
                        temp = Piece::bishopMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::rook) {
                        temp = Piece::rookMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::queen) {
                        temp = Piece::queenMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::king) {
                        temp = Piece::kingMoves(it.first, it.second, col);
                    }
                    for (auto it2 : temp) {
                        if (tempCnt == randMove) {
                            return retNewMove((boardPieces)(i + 1),
                                it.first, it.second,
                                it2.first, it2.second);
                        }
                        tempCnt++;
                    }
                }
            }
        }
    }
    else { // ≈—Ћ» ’ќƒя“ „≈–Ќџ≈
        // если король под шахом
        pair<int, int> newMove;
        auto pos = *pb.figures[Pieces::king].begin();
        if (pb.attackByEnemies[pos.first][pos.second] == true) {
            pb.isCheck = true;
            // 2 выхода: уйти от шаха\
                    или закрытьс€ от шаха
                    /*
                    * если мы можем уйти, то супер
                    * далее, если не можем уйти, то провер€ем, можем ли мы закрытьс€ любой из наших фигур
                    * если нет, то нам поставили мат
                    */ //\
                                                                                                                                            пытаемс€ уйти королем
            pair<int, int> newPos;
            vector<pair<int, int>> temp = Piece::kingMoves(pos.first, pos.second, col); // получили ходы
            for (auto it : temp) {
                // если нашли куда отойти
                if (pb.attackByEnemies[it.first][it.second] == false) {
                    pb.isCheck = false;
                    return retNewMove(boardPieces::blackKing,
                        pos.first, pos.second, it.first, it.second);
                }
            }
            // иначе пытаемс€ закрытьс€
            // получаем все возможные ходы
                // пешка
            unordered_set<pair<int, int>, hash_pair> tempSet = pb.figures[Pieces::pawn];
            for (auto it : tempSet) {
                temp = Piece::pawnMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::pawn, col)) {
                        pb.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // конь
            tempSet = pb.figures[Pieces::knight];
            for (auto it : tempSet) {
                temp = Piece::knightMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::knight, col)) {
                        pb.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // слон
            tempSet = pb.figures[Pieces::bishop];
            for (auto it : tempSet) {
                temp = Piece::bishopMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::bishop, col)) {
                        pb.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // ладь€
            tempSet = pb.figures[Pieces::rook];
            for (auto it : tempSet) {
                temp = Piece::rookMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::rook, col)) {
                        pb.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            // ферзь
            tempSet = pb.figures[Pieces::queen];
            for (auto it : tempSet) {
                temp = Piece::queenMoves(it.first, it.second, col);
                for (auto it2 : temp) {
                    if (makeSomething(pos, it, it2, Pieces::queen, col)) {
                        pb.isCheck = false;
                        return retNewMove((boardPieces)Board::map[it.first][it.second],
                            it.first, it.second, it2.first, it2.second);
                    }
                }
            }
            pb.isCheckMate = true;
            return retNewMove(boardPieces::empt, -1, -1, -1, -1);
        }
        else {
            // —ƒ≈Ћј“№ –јЌƒќћ

            // getAllMoves()\
                    rand()
            vector<vector<pair<int, int>>> allMoves = getAllMoves(col);
            int cntMoves = 0;
            for (auto it : allMoves) {
                cntMoves += it.size();
            }
            if (cntMoves == 0) {
                pb.isStaleMate = true;
                // јче дальше делать - то?\
                    наверн просто ретурн + проверка в другом файле на сталемате
                return retNewMove(boardPieces::empt, -1, -1, -1, -1);
            }
            // ищем рандомный ход
            int randMove = dist.get_rand() % cntMoves;
            int tempCnt = 0;
            vector<pair<int, int>> temp;
            for (int i = 0; i <= 5; i++) {
                for (auto it : pb.figures[i]) {
                    if ((Pieces)i == Pieces::pawn) {
                        temp = Piece::pawnMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::knight) {
                        temp = Piece::knightMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::bishop) {
                        temp = Piece::bishopMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::rook) {
                        temp = Piece::rookMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::queen) {
                        temp = Piece::queenMoves(it.first, it.second, col);
                    }
                    else if ((Pieces)i == Pieces::king) {
                        temp = Piece::kingMoves(it.first, it.second, col);
                    }
                    for (auto it2 : temp) {
                        if (tempCnt == randMove) {
                            return retNewMove((boardPieces)(i + 6 + 1),
                                it.first, it.second,
                                it2.first, it2.second);
                        }
                        tempCnt++;
                    }
                }
            }
        }
    }
}
retNewMove ChessEngine::makeNextMove(Colors col) {
    retNewMove rnm = getNextMove(col);
    if (col == Colors::white) {
        if (pw.isCheckMate == true) {
            return retNewMove(boardPieces::empt, -1, -1, -1, -1);
        }
        if (pw.isStaleMate == true) {
            return retNewMove(boardPieces::empt, -2, -2, -2, -2);
        }
        // если кого-то едим, то должны удалить чужую фигуру
        if (Board::map[rnm.to1][rnm.to2] != boardPieces::empt) {
            pb.figures[Board::map[rnm.to1][rnm.to2] - 6 - 1].erase({ rnm.to1, rnm.to2 });
            Board::map[rnm.to1][rnm.to2] = boardPieces::empt;
        }
        pw.figures[rnm.bp - 1].erase({ rnm.from1, rnm.from2 });
        pw.figures[rnm.bp - 1].insert({ rnm.to1, rnm.to2 });
        swap(Board::map[rnm.from1][rnm.from2], Board::map[rnm.to1][rnm.to2]);
        update();

        return rnm;
    }
    else {
        if (col == Colors::black && pb.isCheckMate == true) {
            return retNewMove(boardPieces::empt, -1, -1, -1, -1);
        }
        if (col == Colors::black && pb.isStaleMate == true) {
            return retNewMove(boardPieces::empt, -2, -2, -2, -2);
        }
        // если кого-то едим, то должны удалить чужую фигуру
        if (Board::map[rnm.to1][rnm.to2] != boardPieces::empt) {
            pw.figures[Board::map[rnm.to1][rnm.to2] - 1].erase({ rnm.to1, rnm.to2 });
            Board::map[rnm.to1][rnm.to2] = boardPieces::empt;
        }
        pb.figures[rnm.bp - 6 - 1].erase({ rnm.from1, rnm.from2 });
        pb.figures[rnm.bp - 6 - 1].insert({ rnm.to1, rnm.to2 });
        swap(Board::map[rnm.from1][rnm.from2], Board::map[rnm.to1][rnm.to2]);
        update();
        return rnm;
    }
}

// предполагаем, что сделан корректный ход\
    защиты от дурака пока что не будет
void ChessEngine::setNextMove(int from1, int from2, int to1, int to2, Colors col) {
    if (col == Colors::white) {
        if (Board::map[to1][to2] == boardPieces::empt) {
            // обновили бд
            pw.figures[Board::map[from1][from2] - 1].insert({ to1, to2 });
            pw.figures[Board::map[from1][from2] - 1].erase({ from1, from2 });

            // обновили карту
            swap(Board::map[from1][from2], Board::map[to1][to2]);
        }
        else {
            pb.figures[Board::map[to1][to2] - 6 - 1].erase({ to1, to2 });

            pw.figures[Board::map[from1][from2] - 1].insert({ to1, to2 });
            pw.figures[Board::map[from1][from2] - 1].erase({ from1, from2 });

            Board::map[to1][to2] = boardPieces::empt;
            swap(Board::map[from1][from2], Board::map[to1][to2]);
        }

        // дошли пешкой до конца доски
        if (Board::map[to1][to2] == boardPieces::whitePawn && to1 == 0) {
            pw.figures[Pieces::pawn].erase({ to1, to2 });
            pw.figures[Pieces::queen].insert({ to1, to2 });
            Board::map[to1][to2] = boardPieces::whiteQueen;
        }
    }
    else { // ход черных
        if (Board::map[to1][to2] == boardPieces::empt) {
            // обновили бд
            pb.figures[Board::map[from1][from2] - 6 - 1].insert({ to1, to2 });
            pb.figures[Board::map[from1][from2] - 6 - 1].erase({ from1, from2 });

            // обновили карту
            swap(Board::map[from1][from2], Board::map[to1][to2]);
        }
        else {
            // удалили вражескую фигуру
            pw.figures[Board::map[to1][to2] - 1].erase({ to1, to2 });

            // обновили бд
            pb.figures[Board::map[from1][from2] - 6 - 1].insert({ to1, to2 });
            pb.figures[Board::map[from1][from2] - 6 - 1].erase({ from1, from2 });

            Board::map[to1][to2] = boardPieces::empt;
            swap(Board::map[from1][from2], Board::map[to1][to2]);
        }

        // дошли пешкой до конца доски
        if (Board::map[to1][to2] == boardPieces::blackPawn && to1 == 0) {
            pb.figures[Pieces::pawn].erase({ to1, to2 });
            pb.figures[Pieces::queen].insert({ to1, to2 });
            Board::map[to1][to2] = boardPieces::blackQueen;
        }
    }
    update();
}



vector<vector<pair<int, int>>> ChessEngine::getAllMoves(Colors col) {
    vector<vector<pair<int, int>>> tempMoves(6);
    vector<pair<int, int>> temp;
    for (int i = 0; i <= 5; i++) {
        unordered_set<pair<int, int>, hash_pair> tempUs;
        if (col == Colors::white) {
            tempUs = pw.figures[i];
        }
        else {
            tempUs = pb.figures[i];
        }
        for (auto it : tempUs) {
            if ((Pieces)i == Pieces::pawn) {
                temp = Piece::pawnMoves(it.first, it.second, col);
            }
            else if ((Pieces)i == Pieces::knight) {
                temp = Piece::knightMoves(it.first, it.second, col);
            }
            else if ((Pieces)i == Pieces::bishop) {
                temp = Piece::bishopMoves(it.first, it.second, col);
            }
            else if ((Pieces)i == Pieces::rook) {
                temp = Piece::rookMoves(it.first, it.second, col);
            }
            else if ((Pieces)i == Pieces::queen) {
                temp = Piece::queenMoves(it.first, it.second, col);
            }
            else if ((Pieces)i == Pieces::king) {
                temp = Piece::kingMoves(it.first, it.second, col);
            }
            tempMoves[i].insert(tempMoves[i].end(), temp.begin(), temp.end());
        }
    }
    return tempMoves;
}
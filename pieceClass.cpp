#include "pieceClass.h"

Piece::Piece() {
    isCheck = false;;
    isCheckMate = false;
    isStaleMate = false;
    figures.resize(6);
    attackByEnemies.resize(8, vector<bool>(8));
}
Piece::~Piece() = default;
void Piece::updateAttackByEnemies(const vector<vector<bool>>& newMap) {
    attackByEnemies = newMap;
}


inline void Piece::print(const Pieces id) {
    for (auto& it : figures[id]) {
        cout << it.first << " " << it.second << "\n";
    }
}
inline unordered_set<pair<int, int>, hash_pair> Piece::getPositions(const boardPieces id) {
    return Board::getPositions(id);
}
vector<pair<int, int>> Piece::pawnMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret;
    if (col == white) {
        // первый ход на 2 клетки вверх
        if (i == 6 && Board::map[5][j] == boardPieces::empt && Board::map[4][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(4, j));
        }
        // ход на 1 клетку вверх
        if (i - 1 > 0 && Board::map[i - 1][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(i - 1, j));
        }
        // кушание влево вверх
        if (checkRange(i - 1, j - 1) && checkCell(i - 1, j - 1, Colors::white)) {
            ret.push_back(pair<int, int>(i - 1, j - 1));
        }
        // кушание вправо вверх
        if (checkRange(i - 1, j + 1) && checkCell(i - 1, j + 1, Colors::white)) {
            ret.push_back(pair<int, int>(i - 1, j + 1));
        }
    }
    else { // black
        // первый ход на 2 клетки вниз
        if (i == 1 && Board::map[2][j] == boardPieces::empt && Board::map[3][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(3, j));
        }
        // ход на 1 клетку вниз
        if (i + 1 <= 7 && Board::map[i + 1][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(i + 1, j));
        }
        // кушание влево вниз
        if (checkRange(i + 1, j - 1) && checkCell(i + 1, j - 1, Colors::black)) {
            ret.push_back(pair<int, int>(i + 1, j - 1));
        }
        // кушание вправо вниз
        if (checkRange(i + 1, j + 1) && checkCell(i + 1, j + 1, Colors::black)) {
            ret.push_back(pair<int, int>(i + 1, j + 1));
        }
    }
    return ret;
}
vector<pair<int, int>> Piece::knightMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret;
    // пони ходят буковкой Г
    if (checkRange(i + 2, j - 1) && (Board::map[i + 2][j - 1] == boardPieces::empt || checkCell(i + 2, j - 1, col))) {
        ret.push_back(pair<int, int>(i + 2, j - 1));
    }
    if (checkRange(i + 2, j + 1) && (Board::map[i + 2][j + 1] == boardPieces::empt || checkCell(i + 2, j + 1, col))) {
        ret.push_back(pair<int, int>(i + 2, j + 1));
    }
    if (checkRange(i + 1, j - 2) && (Board::map[i + 1][j - 2] == boardPieces::empt || checkCell(i + 1, j - 2, col))) {
        ret.push_back(pair<int, int>(i + 1, j - 2));
    }
    if (checkRange(i + 1, j + 2) && (Board::map[i + 1][j + 2] == boardPieces::empt || checkCell(i + 1, j + 2, col))) {
        ret.push_back(pair<int, int>(i + 1, j + 2));
    }
    if (checkRange(i - 1, j - 2) && (Board::map[i - 1][j - 2] == boardPieces::empt || checkCell(i - 1, j - 2, col))) {
        ret.push_back(pair<int, int>(i - 1, j - 2));
    }
    if (checkRange(i - 1, j + 2) && (Board::map[i - 1][j + 2] == boardPieces::empt || checkCell(i - 1, j + 2, col))) {
        ret.push_back(pair<int, int>(i - 1, j + 2));
    }
    if (checkRange(i - 2, j - 1) && (Board::map[i - 2][j - 1] == boardPieces::empt || checkCell(i - 2, j - 1, col))) {
        ret.push_back(pair<int, int>(i - 2, j - 1));
    }
    if (checkRange(i - 2, j + 1) && (Board::map[i - 2][j + 1] == boardPieces::empt || checkCell(i - 2, j + 1, col))) {
        ret.push_back(pair<int, int>(i - 2, j + 1));
    }
    return ret;
}
vector<pair<int, int>> Piece::rookMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret;
    // смотрим клетки сверху
    for (int k = i - 1; k >= 0; k--) {
        if (Board::map[k][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(k, j));
        }
        // если встретили вражескую фигуру, то можем ее съесть
        else if (checkCell(k, j, col)) {
            ret.push_back(pair<int, int>(k, j));
            break;
        }
        else if (checkCell(k, j, changeColor(col)) || checkKing(k, j, col)) {
            break;
        }
        else {
            break;
        }
    }
    // смотрим клетки снизу
    for (int k = i + 1; k <= 7; k++) {
        if (Board::map[k][j] == boardPieces::empt) {
            ret.push_back(pair<int, int>(k, j));
        }
        // если встретили вражескую фигуру, то можем ее съесть
        else if (checkCell(k, j, col)) {
            ret.push_back(pair<int, int>(k, j));
            break;
        }
        else if (checkCell(k, j, changeColor(col)) || checkKing(k, j, col)) {
            break;
        }
        else {
            break;
        }
    }
    // смотрим клетки слева
    for (int k = i - 1; k >= 0; k--) {
        if (Board::map[i][k] == boardPieces::empt) {
            ret.push_back(pair<int, int>(i, k));
        }
        // если встретили вражескую фигуру, то можем ее съесть
        else if (checkCell(i, k, col)) {
            ret.push_back(pair<int, int>(i, k));
            break;
        }
        else if (checkCell(i, k, changeColor(col)) || checkKing(i, k, col)) {
            break;
        }
        else {
            break;
        }
    }
    // смотрим клетки справа
    for (int k = i + 1; k <= 7; k++) {
        if (Board::map[i][k] == boardPieces::empt) {
            ret.push_back(pair<int, int>(i, k));
        }
        // если встретили вражескую фигуру, то можем ее съесть
        else if (checkCell(i, k, col)) {
            ret.push_back(pair<int, int>(i, k));
            break;
        }
        else if (checkCell(i, k, changeColor(col)) || checkKing(i, k, col)) {
            break;
        }
        else {
            break;
        }
    }
    return ret;
}
vector<pair<int, int>> Piece::bishopMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret;

    // все диагонали диагональ
    for (auto ii : { -1, 1 }) {
        for (auto jj : { -1, 1 }) {
            int dx = ii, dy = jj;
            while (checkRange(i + ii, j + jj)) {
                if (Board::map[i + ii][j + jj] == empt) {
                    ret.push_back(pair<int, int>(i + ii, j + jj));
                }
                else if (checkCell(i + ii, j + jj, col)) {
                    ret.push_back(pair<int, int>(i + ii, j + jj));
                    break;
                }
                else if (checkCell(i + ii, j + jj, changeColor(col)) || checkKing(i + ii, j + jj, col)) {
                    break;
                }
                else break;
                if (dx == -1) ii--;
                else if (dx == 1) ii++;
                if (dy == -1) jj--;
                else if (dy == 1) jj++;
            }
            ii = dx;
        }
    }
    return ret;
}
// спасибо ферзю что ходит как ладья + слон\
    -30 строк кода
vector<pair<int, int>> Piece::queenMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret = rookMoves(i, j, col);
    vector<pair<int, int>> temp = bishopMoves(i, j, col);
    ret.insert(ret.end(), temp.begin(), temp.end());
    return ret;
}
vector<pair<int, int>> Piece::kingMoves(int i, int j, Colors col) {
    vector<pair<int, int>> ret;
    for (auto ii : { -1, 0, 1 }) {
        for (auto jj : { -1, 0, 1 }) {
            if (ii == 0 && jj == 0) {
                continue;
            }
            if (checkRange(i + ii, j + jj) &&
                (Board::map[i + ii][j + jj] == boardPieces::empt || checkCell(i + ii, j + jj, col)
                    && attackByEnemies[i + ii][j + jj] == false)) {
                ret.push_back({ i + ii, j + jj });
            }
        }
    }
    return ret;
}


bool Piece::checkKing(int i, int j, Colors col) {
    if (col == Colors::white) {
        return Board::map[i][j] == boardPieces::whiteKing;
    }
    else {
        return Board::map[i][j] == boardPieces::blackKing;
    }
}

//protected:
boardPieces Piece::returnFigure(Pieces piece, Colors col) {
    if (col == Colors::white) {
        int id = piece + 1;
        return static_cast<boardPieces>(id);
    }
    else {
        int id = piece + 1 + 6;
        return static_cast<boardPieces>(id);
    }
}

// проверка на границы доски
inline bool Piece::checkRange(int i, int j) {
    return i >= 0 && i <= 7 && j >= 0 && j <= 7;
}
// проверяем, встретили ли мы вражескую фигуру (кроме короля, с ним какая-то пиздень будет)
inline bool Piece::checkCell(int i, int j, Colors col) {
    // проверяем, если кодировка вражеской фигуры, кроме короля
    if (col == white) {
        return Board::map[i][j] >= 7 && Board::map[i][j] <= /*12*/ 11;
    }
    else { // black
        return Board::map[i][j] >= 1 && Board::map[i][j] <= /*6*/ 5;
    }
}
Colors Piece::changeColor(Colors col) {
    return (col == Colors::white ? Colors::black : Colors::white);
}

vector<vector<bool>> Piece::getAllAttacks(Colors col) {
    vector<vector<bool>> nm(8, vector<bool>(8));
    for (int i = 0; i <= 5; i++) {
        Pieces temp = static_cast<Pieces>(i);
        unordered_set<pair<int, int>, hash_pair> tempUs = Board::getPositions(returnFigure(temp, col));
        // белые пешки
        if (temp == Pieces::pawn && col == Colors::white) {
            for (auto it : tempUs) {
                for (auto it2 : { -1, 1 }) {
                    if (checkRange(it.first - 1, it.second + it2)) {
                        nm[it.first - 1][it.second + it2] = true;
                    }
                }
            }
        }
        // черные пешки
        else if (temp == Pieces::pawn && col == Colors::black) {
            for (auto it : tempUs) {
                for (auto it2 : { -1, 1 }) {
                    if (checkRange(it.first + 1, it.second + it2)) {
                        nm[it.first + 1][it.second + it2] = true;
                    }
                }
            }
        }
        // ладья 
        else if (temp == Pieces::rook) {
            for (auto it : tempUs) {
                for (int k = i + 1; k <= 7; k++) {
                    if (checkRange(k, it.second)) {
                        if (Board::map[k][it.second] == boardPieces::empt ||
                            checkKing(k, it.second, changeColor(col))) {
                            nm[k][it.second] = true;
                        }
                        else if (checkCell(k, it.second, col)
                            || checkCell(k, it.second, changeColor(col))) {
                            nm[k][it.second] = true;
                            break;
                        }
                        else break;
                    }
                }
                for (int k = i - 1; k >= 0; k--) {
                    if (checkRange(k, it.second)) {
                        if (Board::map[k][it.second] == boardPieces::empt ||
                            checkKing(k, it.second, changeColor(col))) {
                            nm[k][it.second] = true;
                        }
                        else if (checkCell(k, it.second, col)
                            || checkCell(k, it.second, changeColor(col))) {
                            nm[k][it.second] = true;
                            break;
                        }
                        else break;
                    }
                }

                for (int k = i + 1; k <= 7; k++) {
                    if (checkRange(k, it.second)) {
                        if (Board::map[it.first][k] == boardPieces::empt ||
                            checkKing(it.first, k, changeColor(col))) {
                            nm[it.first][k] = true;
                        }
                        else if (checkCell(it.first, k, col)
                            || checkCell(it.first, k, changeColor(col))) {
                            nm[it.first][k] = true;
                            break;
                        }
                        else break;
                    }
                }
                for (int k = i - 1; k >= 0; k--) {
                    if (checkRange(it.first, k)) {
                        if (Board::map[it.first][k] == boardPieces::empt ||
                            checkKing(it.first, k, changeColor(col))) {
                            nm[it.first][k] = true;
                        }
                        else if (checkCell(it.first, k, col)
                            || checkCell(it.first, k, changeColor(col))) {
                            nm[it.first][k] = true;
                            break;
                        }
                        else break;
                    }
                }
            }
        }
        // слон
        else if (temp == Pieces::bishop) {
            for (auto it : tempUs) {
                for (auto ii : { -1, 1 }) {
                    for (auto jj : { -1, 1 }) {
                        int dx = ii, dy = jj;
                        while (checkRange(it.first + ii, it.second + jj)) {
                            if (Board::map[it.first + ii][it.second + jj] == empt ||
                                checkKing(it.first + ii, it.second + jj, changeColor(col))) {
                                nm[it.first + ii][it.second + jj] = true;
                            }
                            else if (checkCell(it.first + ii, it.second + jj, col)
                                || checkCell(it.first + ii, it.second + jj, changeColor(col))) {
                                nm[it.first + ii][it.second + jj] = true;
                                break;
                            }
                            else break;
                            if (dx == -1) ii--;
                            else if (dx == 1) ii++;
                            if (dy == -1) jj--;
                            else if (dy == 1) jj++;
                        }
                        ii = dx;
                    }
                }
            }
        }
        // конь
        else if (temp == Pieces::knight) {
            for (auto it : tempUs) {
                vector<pair<int, int>> v = knightMoves(it.first, it.second, col);
                for (auto it2 : v) {
                    nm[it2.first][it2.second] = true;
                }
            }
        }
        // ферзь
        else if (temp == Pieces::queen) {
        for (auto it : tempUs) {

            for (int k = i + 1; k <= 7; k++) {
                if (checkRange(k, it.second)) {
                    if (Board::map[k][it.second] == boardPieces::empt ||
                        checkKing(k, it.second, changeColor(col))) {
                        nm[k][it.second] = true;
                    }
                    else if (checkCell(k, it.second, col)
                        || checkCell(k, it.second, changeColor(col))) {
                        nm[k][it.second] = true;
                        break;
                    }
                    else break;
                }
            }
            for (int k = i - 1; k >= 0; k--) {
                if (checkRange(k, it.second)) {
                    if (Board::map[k][it.second] == boardPieces::empt ||
                        checkKing(k, it.second, changeColor(col))) {
                        nm[k][it.second] = true;
                    }
                    else if (checkCell(k, it.second, col)
                        || checkCell(k, it.second, changeColor(col))) {
                        nm[k][it.second] = true;
                        break;
                    }
                    else break;
                }
            }

            for (int k = i + 1; k <= 7; k++) {
                if (checkRange(k, it.second)) {
                    if (Board::map[it.first][k] == boardPieces::empt ||
                        checkKing(it.first, k, changeColor(col))) {
                        nm[it.first][k] = true;
                    }
                    else if (checkCell(it.first, k, col)
                        || checkCell(it.first, k, changeColor(col))) {
                        nm[it.first][k] = true;
                        break;
                    }
                    else break;
                }
            }
            for (int k = i - 1; k >= 0; k--) {
                if (checkRange(it.first, k)) {
                    if (Board::map[it.first][k] == boardPieces::empt ||
                        checkKing(it.first, k, changeColor(col))) {
                        nm[it.first][k] = true;
                    }
                    else if (checkCell(it.first, k, col)
                        || checkCell(it.first, k, changeColor(col))) {
                        nm[it.first][k] = true;
                        break;
                    }
                    else break;
                }
            }

            for (auto ii : { -1, 1 }) {
                for (auto jj : { -1, 1 }) {
                    int dx = ii, dy = jj;
                    while (checkRange(it.first + ii, it.second + jj)) {
                        if (Board::map[it.first + ii][it.second + jj] == empt ||
                            checkKing(it.first + ii, it.second + jj, changeColor(col))) {
                            nm[it.first + ii][it.second + jj] = true;
                        }
                        else if (checkCell(it.first + ii, it.second + jj, col)
                            || checkCell(it.first + ii, it.second + jj, changeColor(col))) {
                            nm[it.first + ii][it.second + jj] = true;
                            break;
                        }
                        else break;
                        if (dx == -1) ii--;
                        else if (dx == 1) ii++;
                        if (dy == -1) jj--;
                        else if (dy == 1) jj++;
                    }
                    ii = dx;
                }
            }
        }
        }
        // король
        else if (temp == Pieces::king) {
            auto q = *tempUs.begin();
            for (auto it : { -1, 0, 1 }) {
                for (auto it2 : { -1, 0, 1 }) {
                    if (it == 0 && it2 == 0) continue;
                    if (checkRange(q.first + it, q.second + it2)) {
                        nm[q.first + it][q.second + it2] = true;
                    }
                }
            }
        }
    }
    return nm;
}
void Piece::printAttacks() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << attackByEnemies[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}
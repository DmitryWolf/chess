#include "tools.h"
namespace Tools {
    retNewMove::retNewMove(boardPieces newBp, int newFrom1, int newFrom2, int newTo1, int newTo2) :
        bp(newBp), from1(newFrom1), from2(newFrom2), to1(newTo1), to2(newTo2) {};
    rnd::rnd() {
        minR = 1;
        maxR = 10000;
        random_device rd;
        mt19937 mt(rd());
    }
    int rnd::get_rand() {
        uniform_int_distribution<int> dist(minR, maxR);
        return dist(mt);
    }
}
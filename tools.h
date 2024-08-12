#pragma once
#include <random>
#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

namespace Tools {
    // size_t rand_num = dist(mt);

    struct rnd {
        int minR;
        int maxR;
        uniform_int_distribution<int> dist;
        mt19937 mt;
        rnd();
        int get_rand();
    };

    struct hash_pair {
        template <class T1, class T2>
        size_t operator()(const std::pair<T1, T2>& p) const {
            uintmax_t hash = std::hash<T1>{}(p.first);
            hash <<= sizeof(uintmax_t) * 4;
            hash ^= std::hash<T2>{}(p.second);
            return std::hash<uintmax_t>{}(hash);
        }
    };

    enum Colors : int {
        white = 0,
        black
    };
    enum Pieces : int {
        pawn = 0,
        knight,
        bishop,
        rook,
        queen,
        king,
        noth
    };

    enum boardPieces : int {
        empt = 0,
        whitePawn,  // 1
        whiteKnight,// 2
        whiteBishop,// 3
        whiteRook,  // 4
        whiteQueen, // 5
        whiteKing,  // 6

        blackPawn,  // 7
        blackKnight,// 8
        blackBishop,// 9
        blackRook,  // 10
        blackQueen,  // 11
        blackKing  // 12
    };


    struct retNewMove {
        boardPieces bp;
        int from1;
        int from2;
        int to1;
        int to2;
        retNewMove(boardPieces newBp, int newFrom1, int newFrom2, int newTo1, int newTo2);
    };

}
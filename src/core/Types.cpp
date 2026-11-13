#ifndef REWINDCHESS_TYPES_CPP
#define REWINDCHESS_TYPES_CPP

#include <string>

using namespace std;

// Named integer constants keep the choices readable without special types.
const int WHITE_PLAYER = 0, BLACK_PLAYER = 1;
const int NO_PIECE = 0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 6;

// A board location; default coordinates (-1, -1) mean no square is selected.
class Square {
public:
    int row; // 0 = rank 8; 7 = rank 1
    int col; // 0 = file a; 7 = file h

    Square(int newRow = -1, int newCol = -1) {
        row = newRow;
        col = newCol;
    }

    bool valid() const { return row >= 0 && row < 8 && col >= 0 && col < 8; }

    bool sameAs(Square other) const { return row == other.row && col == other.col; }
};

// A default Piece represents an empty square; its side is then irrelevant.
class Piece {
public:
    int type;
    int side;

    Piece(int newType = NO_PIECE, int newSide = WHITE_PLAYER) {
        type = newType;
        side = newSide;
    }

    bool empty() const { return type == NO_PIECE; }
};

// Stores the endpoints of a move; Rules.cpp checks whether it is allowed.
class Move {
public:
    Square from;
    Square to;

    Move(Square start = Square(), Square destination = Square()) {
        from = start;
        to = destination;
    }
};


// A complete prototype position: the board and the player whose turn it is.
class State {
public:
    // Each array element starts as an empty Piece.
    Piece board[8][8];
    int turn = WHITE_PLAYER;

    // A reference (&) accesses the piece already stored in the board.
    Piece &at(Square square) { return board[square.row][square.col]; }

    // A const state gives read-only access to that same piece.
    const Piece &at(Square square) const { return board[square.row][square.col]; }
};


#endif

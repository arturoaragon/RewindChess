#ifndef REWINDCHESS_TYPES_CPP
#define REWINDCHESS_TYPES_CPP

#include <string>

using namespace std;

// Named integer constants keep the choices readable without special types.
const int WHITE_PLAYER = 0, BLACK_PLAYER = 1;
const int NO_PIECE = 0, PAWN = 1, KNIGHT = 2, BISHOP = 3, ROOK = 4, QUEEN = 5, KING = 6;
const int GAME_PLAYING = 0, CHECKMATE = 1, STALEMATE = 2, INSUFFICIENT_MATERIAL = 3;
const int FIVEFOLD_REPETITION = 4, SEVENTY_FIVE_MOVES = 5, CLAIMED_DRAW = 6;

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

class Move {
public:
    Square from;
    Square to;
    int promotion;

    Move(Square start = Square(), Square destination = Square(), int promotionType = NO_PIECE) {
        from = start;
        to = destination;
        promotion = promotionType;
    }
};

class CastlingRights {
public:
    bool kingSide[2] = {true, true};
    bool queenSide[2] = {true, true};
};

class State {
public:
    Piece board[8][8];
    int turn = WHITE_PLAYER;
    CastlingRights castling;
    Square enPassant;
    int halfmoveClock = 0;
    int fullmoveNumber = 1;
    Move lastMove;
    string moveText = "Start";
    string repetitionKey;

    // A reference (&) accesses the piece already stored in the board.
    Piece &at(Square square) { return board[square.row][square.col]; }

    // A const state gives read-only access to that same piece.
    const Piece &at(Square square) const { return board[square.row][square.col]; }
};

class Player {
public:
    int rewindsUsed = 0;
};

#endif

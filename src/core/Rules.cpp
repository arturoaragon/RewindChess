#ifndef REWINDCHESS_RULES_CPP
#define REWINDCHESS_RULES_CPP
// This file is included by Game.cpp; the guard prevents repeated definitions.
// Rules work with board data only, so they do not depend on the graphical interface.
#include "Types.cpp"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// Switch between the two players after a move.
int opposite(int side) {
    if (side == WHITE_PLAYER) return BLACK_PLAYER;
    return WHITE_PLAYER;
}

// Convert the player constant into text for the interface.
string sideName(int side) {
    if (side == WHITE_PLAYER) return "White";
    return "Black";
}

// Row 0 is at the top: White moves toward smaller rows, Black toward larger rows.
int pawnDirection(int side) {
    if (side == WHITE_PLAYER) return -1;
    return 1;
}

// Piece constants are array indexes; these letters also form asset filenames.
char pieceLetter(int type) {
    const char letters[] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K'};
    return letters[type];
}

// Translate array coordinates into chess notation, for example (7, 0) becomes a1.
string squareName(Square square) {
    if (!square.valid()) return "-";
    return string(1, char('a' + square.col)) + char('8' - square.row);
}

// Default pieces are empty; fill only the four occupied starting rows.
State initialState() {
    State state;
    int backRow[8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    for (int col = 0; col < 8; col++) {
        state.board[0][col] = Piece(backRow[col], BLACK_PLAYER);
        state.board[1][col] = Piece(PAWN, BLACK_PLAYER);
        state.board[6][col] = Piece(PAWN, WHITE_PLAYER);
        state.board[7][col] = Piece(backRow[col], WHITE_PLAYER);
    }
    return state;
}

// For a straight or diagonal move, inspect the squares between the endpoints.
// The caller checks the movement shape and destination separately.
bool clearPath(const State &state, Square from, Square to) {
    int rowChange = 0;
    int colChange = 0;
    if (to.row > from.row) {
        rowChange = 1;
    } else if (to.row < from.row) {
        rowChange = -1;
    }
    if (to.col > from.col) {
        colChange = 1;
    } else if (to.col < from.col) {
        colChange = -1;
    }
    // Each step changes a coordinate by -1, 0 or 1, moving toward the destination.
    Square square(from.row + rowChange, from.col + colChange);
    while (!square.sameAs(to)) {
        if (!square.valid() || !state.at(square).empty()) return false;
        square.row += rowChange;
        square.col += colChange;
    }
    return true;
}

// Check movement shapes and obstacles. Pawns attack diagonally, unlike their walk.
// Turn ownership and destination occupancy are checked by isLegalMove.
bool pieceAttacks(const State &state, Square from, Square to) {
    if (from.sameAs(to)) return false;
    Piece piece = state.at(from);
    int rowChange = to.row - from.row;
    int rows = abs(rowChange), cols = abs(to.col - from.col);
    switch (piece.type) {
    case PAWN: return rowChange == pawnDirection(piece.side) && cols == 1;
    case KNIGHT: return rows * cols == 2; // A 1-by-2 or 2-by-1 jump.
    case KING: return max(rows, cols) == 1;
    case BISHOP: return rows == cols && clearPath(state, from, to);
    case ROOK: return (rows == 0 || cols == 0) && clearPath(state, from, to);
    case QUEEN: return (rows == cols || rows == 0 || cols == 0) && clearPath(state, from, to);
    }
    return false;
}

// Prototype validation: king safety and special chess rules arrive in week 3.
// These checks implement basic movement, not full chess legality (such as check).
bool isLegalMove(const State &state, const Move &move) {
    // Reject invalid coordinates before using them as board indexes.
    if (!move.from.valid() || !move.to.valid() || move.from.sameAs(move.to)) return false;
    Piece piece = state.at(move.from), target = state.at(move.to);
    if (piece.empty() || piece.side != state.turn) return false;
    if (!target.empty() && (target.side == piece.side || target.type == KING)) return false;
    if (piece.type == PAWN) {
        // Pawns capture one square diagonally, but move forward into empty squares.
        int forward = pawnDirection(piece.side);
        int rowChange = move.to.row - move.from.row;
        int colChange = abs(move.to.col - move.from.col);
        if (colChange == 1) return rowChange == forward && !target.empty();
        if (colChange != 0 || !target.empty()) return false;
        if (rowChange == forward) return true;
        int startRow = 1;
        if (piece.side == WHITE_PLAYER) startRow = 6;
        // The initial two-square move must also have an empty intermediate square.
        return move.from.row == startRow && rowChange == 2 * forward &&
               state.at(Square(move.from.row + forward, move.from.col)).empty();
    }
    return pieceAttacks(state, move.from, move.to);
}

// Assume the move was validated. Return a changed copy and keep the input intact.
// Replacing the destination piece handles captures; clearing the source moves it.
State applyMove(const State &state, const Move &move) {
    State next = state;
    next.at(move.to) = state.at(move.from);
    next.at(move.from) = Piece();
    next.turn = opposite(state.turn);
    return next;
}

// Try all 64 starting squares against all 64 destinations and keep valid pairs.
// This simple exhaustive approach uses the same validation as Game::play.
vector<Move> getLegalMoves(const State &state) {
    vector<Move> moves;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            for (int r = 0; r < 8; r++) {
                for (int c = 0; c < 8; c++) {
                    Move move(Square(row, col), Square(r, c));
                    if (isLegalMove(state, move)) moves.push_back(move);
                }
            }
        }
    }
    return moves;
}
#endif

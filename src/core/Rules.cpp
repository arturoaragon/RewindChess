#ifndef REWINDCHESS_RULES_CPP
#define REWINDCHESS_RULES_CPP
#include "Types.cpp"
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int opposite(int side) {
    if (side == WHITE_PLAYER) return BLACK_PLAYER;
    return WHITE_PLAYER;
}

string sideName(int side) {
    if (side == WHITE_PLAYER) return "White";
    return "Black";
}

int pawnDirection(int side) {
    if (side == WHITE_PLAYER) return -1;
    return 1;
}

char pieceLetter(int type) {
    const char letters[] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K'};
    return letters[type];
}

string squareName(Square square) {
    if (!square.valid()) return "-";
    return string(1, char('a' + square.col)) + char('8' - square.row);
}

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
    Square square(from.row + rowChange, from.col + colChange);
    while (!square.sameAs(to)) {
        if (!square.valid() || !state.at(square).empty()) return false;
        square.row += rowChange;
        square.col += colChange;
    }
    return true;
}

bool pieceAttacks(const State &state, Square from, Square to) {
    if (from.sameAs(to)) return false;
    Piece piece = state.at(from);
    int rowChange = to.row - from.row;
    int rows = abs(rowChange), cols = abs(to.col - from.col);
    switch (piece.type) {
    case PAWN: return rowChange == pawnDirection(piece.side) && cols == 1;
    case KNIGHT: return rows * cols == 2;
    case KING: return max(rows, cols) == 1;
    case BISHOP: return rows == cols && clearPath(state, from, to);
    case ROOK: return (rows == 0 || cols == 0) && clearPath(state, from, to);
    case QUEEN: return (rows == cols || rows == 0 || cols == 0) && clearPath(state, from, to);
    }
    return false;
}

// Prototype validation: king safety and special chess rules arrive in week 3.
bool isLegalMove(const State &state, const Move &move) {
    if (!move.from.valid() || !move.to.valid() || move.from.sameAs(move.to)) return false;
    Piece piece = state.at(move.from), target = state.at(move.to);
    if (piece.empty() || piece.side != state.turn) return false;
    if (!target.empty() && (target.side == piece.side || target.type == KING)) return false;
    if (piece.type == PAWN) {
        int forward = pawnDirection(piece.side);
        int rowChange = move.to.row - move.from.row;
        int colChange = abs(move.to.col - move.from.col);
        if (colChange == 1) return rowChange == forward && !target.empty();
        if (colChange != 0 || !target.empty()) return false;
        if (rowChange == forward) return true;
        int startRow = 1;
        if (piece.side == WHITE_PLAYER) startRow = 6;
        return move.from.row == startRow && rowChange == 2 * forward &&
               state.at(Square(move.from.row + forward, move.from.col)).empty();
    }
    return pieceAttacks(state, move.from, move.to);
}

State applyMove(const State &state, const Move &move) {
    State next = state;
    next.at(move.to) = state.at(move.from);
    next.at(move.from) = Piece();
    next.turn = opposite(state.turn);
    return next;
}

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

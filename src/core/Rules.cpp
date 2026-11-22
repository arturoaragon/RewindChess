#ifndef REWINDCHESS_RULES_CPP
#define REWINDCHESS_RULES_CPP

#include "Types.cpp"
#include <vector>

#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

// These functions handle chess rules. Game handles resources and timelines;
// the separate App class handles the graphical interface.
bool isSquareAttacked(const State &state, Square square, int bySide);
bool isInCheck(const State &state, int side);
bool isLegalMove(const State &state, const Move &move);
vector<Move> getLegalMoves(const State &state);
State applyMove(const State &state, const Move &move);
string getMoveNotation(const State &state, const Move &move, const State &next);
bool hasInsufficientMaterial(const State &state);
string getPositionKey(const State &state);

int opposite(int side) {
    if (side == WHITE_PLAYER) return BLACK_PLAYER;
    return WHITE_PLAYER;
}

string sideName(int side) {
    if (side == WHITE_PLAYER) return "White";
    return "Black";
}

int homeRow(int side) {
    if (side == WHITE_PLAYER) return 7;
    return 0;
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

// Used for both ordinary moves and check detection. Pawn pushes and castling
// are handled separately because they do not attack squares in the same way.
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

bool canCastle(const State &state, const Move &move) {
    int side = state.turn;
    int row = homeRow(side);
    if (!move.from.sameAs(Square(row, 4)) || move.to.row != row || (move.to.col != 2 && move.to.col != 6)) {
        return false;
    }
    bool kingSide = move.to.col == 6;
    bool hasRight = state.castling.queenSide[side];
    int rookCol = 0;
    int middleCol = 3;
    if (kingSide) {
        hasRight = state.castling.kingSide[side];
        rookCol = 7;
        middleCol = 5;
    }
    if (!hasRight) return false;
    Square corner(row, rookCol);
    Piece rook = state.at(corner);
    if (rook.type != ROOK || rook.side != side || !clearPath(state, move.from, corner) ||
        isInCheck(state, side)) {
        return false;
    }
    State transit = state;
    transit.at(move.from) = Piece();
    Square middle(row, middleCol);
    transit.at(middle) = Piece(KING, side);
    return !isSquareAttacked(transit, middle, opposite(side));
}

Square promotionSquare(const State &state, const Move &move) {
    if (state.at(move.from).type == PAWN && (move.to.row == 0 || move.to.row == 7)) return move.to;
    return Square();
}

bool matchesPieceMovement(const State &state, const Move &move) {
    if (!move.from.valid() || !move.to.valid() || move.from.sameAs(move.to)) return false;
    Piece piece = state.at(move.from), target = state.at(move.to);
    if (piece.empty() || piece.side != state.turn) return false;
    if (!target.empty() && (target.side == piece.side || target.type == KING)) {
        return false;
    }
    bool promotes = promotionSquare(state, move).valid();
    bool choice = move.promotion == QUEEN || move.promotion == ROOK || move.promotion == BISHOP ||
                  move.promotion == KNIGHT;
    if (promotes) {
        if (!choice) return false;
    } else if (move.promotion != NO_PIECE) {
        return false;
    }
    int rowChange = move.to.row - move.from.row, colChange = move.to.col - move.from.col;
    int rowDistance = abs(rowChange), colDistance = abs(colChange);
    int forward = pawnDirection(piece.side);
    if (piece.type == PAWN) {
        int startRow = 1;
        int enPassantRow = 4;
        if (piece.side == WHITE_PLAYER) {
            startRow = 6;
            enPassantRow = 3;
        }
        if (colChange == 0 && target.empty()) {
            if (rowChange == forward) return true;
            return move.from.row == startRow && rowChange == 2 * forward &&
                   state.at(Square(move.from.row + forward, move.from.col)).empty();
        }
        if (colDistance != 1 || rowChange != forward) return false;
        if (!target.empty()) return true;
        Piece behind = state.at(Square(move.from.row, move.to.col));
        return move.to.sameAs(state.enPassant) && behind.type == PAWN && behind.side != piece.side &&
               move.from.row == enPassantRow;
    }
    if (piece.type == KING && colDistance == 2) return canCastle(state, move);
    return pieceAttacks(state, move.from, move.to);
}

void removeRookRight(State &state, Square square, Piece piece) {
    if (piece.type != ROOK || square.row != homeRow(piece.side)) return;
    if (square.col == 0) {
        state.castling.queenSide[piece.side] = false;
    }
    if (square.col == 7) {
        state.castling.kingSide[piece.side] = false;
    }
}

bool isSquareAttacked(const State &state, Square square, int bySide) {
    if (!square.valid()) return false;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = state.board[row][col];
            if (!piece.empty() && piece.side == bySide && pieceAttacks(state, Square(row, col), square)) {
                return true;
            }
        }
    }
    return false;
}

bool isInCheck(const State &state, int side) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (state.board[row][col].type == KING && state.board[row][col].side == side) {
                return isSquareAttacked(state, Square(row, col), opposite(side));
            }
        }
    }
    return true; // A position without its king is never legal.
}

State applyMove(const State &state, const Move &move) {
    State next = state;
    Piece piece = state.at(move.from), target = state.at(move.to);
    next.at(move.from) = Piece();
    next.at(move.to) = piece;
    if (piece.type == PAWN && move.to.sameAs(state.enPassant) && move.from.col != move.to.col &&
        target.empty()) {
        next.at(Square(move.from.row, move.to.col)) = Piece();
    }
    if (piece.type == KING) {
        next.castling.kingSide[piece.side] = false;
        next.castling.queenSide[piece.side] = false;
        if (piece.type == KING && abs(move.to.col - move.from.col) == 2) {
            int rookCol = 0;
            int newCol = 3;
            if (move.to.col == 6) {
                rookCol = 7;
                newCol = 5;
            }
            next.at(Square(move.from.row, newCol)) = next.at(Square(move.from.row, rookCol));
            next.at(Square(move.from.row, rookCol)) = Piece();
        }
    }
    removeRookRight(next, move.from, piece);
    removeRookRight(next, move.to, target);
    next.enPassant = Square();
    if (piece.type == PAWN && abs(move.to.row - move.from.row) == 2) {
        next.enPassant = Square((move.from.row + move.to.row) / 2, move.from.col);
    }
    if (move.promotion != NO_PIECE) {
        next.at(promotionSquare(state, move)).type = move.promotion;
    }
    next.halfmoveClock = state.halfmoveClock + 1;
    if (piece.type == PAWN || (!target.empty() && (target.side != piece.side || target.type == PAWN))) {
        next.halfmoveClock = 0;
    }
    next.fullmoveNumber = state.fullmoveNumber;
    if (state.turn == BLACK_PLAYER) {
        next.fullmoveNumber++;
    }
    next.turn = opposite(state.turn);
    next.lastMove = move;
    next.moveText.clear();
    next.repetitionKey.clear();
    return next;
}

bool isLegalMove(const State &state, const Move &move) {
    return matchesPieceMovement(state, move) && !isInCheck(applyMove(state, move), state.turn);
}

vector<Move> getLegalMoves(const State &state) {
    vector<Move> moves;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Piece piece = state.board[row][col];
            if (piece.empty() || piece.side != state.turn) continue;
            for (int r = 0; r < 8; ++r) {
                for (int c = 0; c < 8; ++c) {
                    Move move(Square(row, col), Square(r, c));
                    if (promotionSquare(state, move).valid()) {
                        int choices[4] = {QUEEN, ROOK, BISHOP, KNIGHT};
                        for (int i = 0; i < 4; i++) {
                            move.promotion = choices[i];
                            if (isLegalMove(state, move)) {
                                moves.push_back(move);
                            }
                        }
                    } else if (isLegalMove(state, move)) {
                        moves.push_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

string getMoveNotation(const State &state, const Move &move, const State &next) {
    Piece piece = state.at(move.from);
    string text;
    if (piece.type == KING && abs(move.to.col - move.from.col) == 2) {
        if (move.to.col == 6) {
            text = "O-O";
        } else {
            text = "O-O-O";
        }
    } else {
        bool capture = !state.at(move.to).empty() || (piece.type == PAWN && move.from.col != move.to.col);
        if (piece.type != PAWN) {
            text += pieceLetter(piece.type);
            bool ambiguous = false, sameFile = false, sameRank = false;
            vector<Move> alternatives = getLegalMoves(state);
            for (int i = 0; i < int(alternatives.size()); i++) {
                Move other = alternatives[i];
                if (other.to.sameAs(move.to) && !other.from.sameAs(move.from) &&
                    state.at(other.from).type == piece.type) {
                    ambiguous = true;
                    if (other.from.col == move.from.col) {
                        sameFile = true;
                    }
                    if (other.from.row == move.from.row) {
                        sameRank = true;
                    }
                }
            }
            if (ambiguous) {
                if (!sameFile || sameRank) {
                    text += char('a' + move.from.col);
                }
                if (sameFile) {
                    text += char('8' - move.from.row);
                }
            }
        } else if (capture) {
            text += char('a' + move.from.col);
        }
        if (capture) {
            text += 'x';
        }
        text += squareName(move.to);
    }
    if (move.promotion != NO_PIECE) {
        text += '=';
        text += pieceLetter(move.promotion);
    }
    if (isInCheck(next, next.turn)) {
        text += '+'; // Game upgrades this to # after checking legal replies.
    }
    return text;
}

bool hasInsufficientMaterial(const State &state) {
    int minors = 0, bishops = 0, bishopColor = -1;
    bool sameColor = true;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int type = state.board[row][col].type;
            if (type == NO_PIECE || type == KING) continue;
            if (type == PAWN || type == ROOK || type == QUEEN) return false;
            ++minors;
            if (type == BISHOP) {
                ++bishops;
                int color = (row + col) % 2;
                if (bishopColor >= 0 && color != bishopColor) {
                    sameColor = false;
                }
                bishopColor = color;
            }
        }
    }
    if (minors == 0) return true;
    return minors == 1 || (minors == bishops && sameColor);
}

string getPositionKey(const State &state) {
    string key;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece piece = state.board[row][col];
            char ch = pieceLetter(piece.type);
            if (!piece.empty() && piece.side == BLACK_PLAYER) {
                ch = char(tolower(ch));
            }
            key += ch;
        }
    }
    if (state.turn == WHITE_PLAYER) {
        key += 'w';
    } else {
        key += 'b';
    }
    for (int side = 0; side < 2; ++side) {
        if (state.castling.kingSide[side]) {
            key += 'K';
        } else {
            key += '-';
        }
        if (state.castling.queenSide[side]) {
            key += 'Q';
        } else {
            key += '-';
        }
    }
    // En passant distinguishes positions only when a legal capture actually exists.
    bool usable = false;
    if (state.enPassant.valid()) {
        int row = state.enPassant.row - pawnDirection(state.turn);
        for (int colChange = -1; colChange <= 1; colChange += 2) {
            Square from(row, state.enPassant.col + colChange);
            if (from.valid() && state.at(from).type == PAWN &&
                isLegalMove(state, Move(from, state.enPassant))) {
                usable = true;
            }
        }
    }
    if (usable) {
        key += squareName(state.enPassant);
    } else {
        key += "-";
    }
    return key;
}

#endif

// Sprint 2 engine tests: start position, turns, movement, blocking, captures.
// Only includes src/core, so you don't need raylib to build it.
// Run from the repo root:
//   g++ -std=c++17 -Wall -Wextra qa/tests/engine_checks.cpp -o engine_checks
//   .\engine_checks.exe
// Prints PASS/FAIL for each check and returns 1 if anything failed.
// TC numbers are the same as in qa/test-plan-sprint2.md

#include "../../src/core/Game.cpp"

#include <iostream>
#include <string>

using namespace std;

static int passed = 0;
static int failed = 0;

static void check(const string &id, const string &description, bool ok) {
    if (ok) {
        passed++;
        cout << "PASS  " << id << "  " << description << '\n';
    } else {
        failed++;
        cout << "FAIL  " << id << "  " << description << '\n';
    }
}

// "e2" -> Square(6, 4). careful: row 0 is rank 8 in our board, col 0 is file a
static Square sq(const string &name) {
    return Square('8' - name[1], name[0] - 'a');
}

static Move mv(const string &from, const string &to) {
    return Move(sq(from), sq(to));
}

// empty board for custom positions
static State emptyBoard(int turn = WHITE_PLAYER) {
    State state;
    state.turn = turn;
    return state;
}

static bool sameBoard(const State &a, const State &b) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (a.board[row][col].type != b.board[row][col].type) return false;
            if (!a.board[row][col].empty() && a.board[row][col].side != b.board[row][col].side) return false;
        }
    }
    return a.turn == b.turn;
}

static int countPieces(const State &state, int side) {
    int count = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (!state.board[row][col].empty() && state.board[row][col].side == side) count++;
        }
    }
    return count;
}

static bool isPiece(const State &state, const string &square, int type, int side) {
    const Piece &piece = state.at(sq(square));
    return piece.type == type && piece.side == side;
}

static bool legal(const State &state, const string &from, const string &to) {
    return isLegalMove(state, mv(from, to));
}

// plays moves like "e2e4 e7e5", returns false if one of them is rejected
static bool playAll(Game &game, const string &moves) {
    for (size_t i = 0; i + 4 <= moves.size(); i += 5) {
        if (!game.play(mv(moves.substr(i, 2), moves.substr(i + 2, 2)))) return false;
    }
    return true;
}

// counts all possible move sequences up to depth, so we can compare with the
// known chess numbers (20, 400, 8902)
static long long perft(const State &state, int depth) {
    if (depth == 0) return 1;
    long long nodes = 0;
    vector<Move> moves = getLegalMoves(state);
    for (size_t i = 0; i < moves.size(); i++) nodes += perft(applyMove(state, moves[i]), depth - 1);
    return nodes;
}

static void initialPosition() {
    cout << "\n== Initial position ==\n";
    State start = initialState();
    check("TC-01", "32 pieces on the board, 16 per side",
          countPieces(start, WHITE_PLAYER) == 16 && countPieces(start, BLACK_PLAYER) == 16);

    const int order[8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    bool backRanks = true, pawns = true, middleEmpty = true;
    for (int col = 0; col < 8; col++) {
        string file(1, char('a' + col));
        backRanks = backRanks && isPiece(start, file + "1", order[col], WHITE_PLAYER) &&
                    isPiece(start, file + "8", order[col], BLACK_PLAYER);
        pawns = pawns && isPiece(start, file + "2", PAWN, WHITE_PLAYER) &&
                isPiece(start, file + "7", PAWN, BLACK_PLAYER);
        for (int rank = 3; rank <= 6; rank++) {
            middleEmpty = middleEmpty && start.at(sq(file + char('0' + rank))).empty();
        }
    }
    check("TC-02", "Back ranks are R N B Q K B N R for both sides (queen on d-file)", backRanks);
    check("TC-03", "White pawns on rank 2, black pawns on rank 7", pawns);
    check("TC-04", "Ranks 3 to 6 are empty", middleEmpty);
    check("TC-05", "Kings start on e1 and e8, and h1 is a light square",
          isPiece(start, "e1", KING, WHITE_PLAYER) && isPiece(start, "e8", KING, BLACK_PLAYER) &&
              (sq("h1").row + sq("h1").col) % 2 == 0);

    Game game;
    check("TC-06", "White moves first and the status reads \"White to move\"",
          game.live().turn == WHITE_PLAYER && game.statusText() == "White to move");
    check("TC-07", "White has exactly 20 moves in the initial position", getLegalMoves(start).size() == 20);
}

static void turnSwitching() {
    cout << "\n== Turn switching ==\n";
    Game game;
    State before = game.live();
    bool blackFirst = game.play(mv("e7", "e5"));
    check("TC-08", "Black cannot move first; the move is rejected with \"Illegal move.\"",
          !blackFirst && game.error() == "Illegal move.");
    check("TC-09", "A rejected move leaves the board and turn unchanged", sameBoard(before, game.live()));

    check("TC-10", "After a valid white move it is Black to move",
          game.play(mv("e2", "e4")) && game.live().turn == BLACK_PLAYER && game.statusText() == "Black to move");
    check("TC-11", "The error message is cleared after a valid move", game.error().empty());
    check("TC-12", "White cannot move twice in a row", !game.play(mv("d2", "d4")) && game.live().turn == BLACK_PLAYER);
    check("TC-13", "After a valid black move it is White to move again",
          game.play(mv("e7", "e5")) && game.live().turn == WHITE_PLAYER);

    Game longer;
    bool ok = playAll(longer, "e2e4 e7e5 g1f3 b8c6 f1c4 g8f6");
    check("TC-14", "Six alternating moves are all accepted and White is to move", ok && longer.live().turn == WHITE_PLAYER);

    longer.newGame();
    check("TC-15", "New game restores the initial position, White to move and no error",
          sameBoard(longer.live(), initialState()) && longer.error().empty());
}

static void basicMovement() {
    cout << "\n== Basic movement ==\n";
    State start = initialState();
    check("TC-16", "Pawn moves one or two squares from its starting rank",
          legal(start, "e2", "e3") && legal(start, "e2", "e4"));
    check("TC-17", "Pawn cannot move three squares, sideways or backwards",
          !legal(start, "e2", "e5") && !legal(start, "e2", "d2") && !legal(start, "e2", "e1"));

    Game game;
    playAll(game, "e2e3 a7a6");
    check("TC-18", "Pawn cannot move two squares after leaving its starting rank", !legal(game.live(), "e3", "e5"));

    check("TC-19", "Knight jumps over pieces from the initial position",
          legal(start, "g1", "f3") && legal(start, "b1", "c3") && legal(start, "b1", "a3"));
    check("TC-20", "Knight cannot make a non-L move", !legal(start, "g1", "g3") && !legal(start, "g1", "e3"));

    Game opened;
    playAll(opened, "e2e4 e7e5");
    const State &s = opened.live();
    check("TC-21", "After 1.e4 e5 the bishop, queen and king can use the opened lines",
          legal(s, "f1", "c4") && legal(s, "f1", "a6") && legal(s, "d1", "h5") && legal(s, "e1", "e2"));
    check("TC-22", "King moves only one square", !legal(s, "e1", "e3"));
    check("TC-23", "Bishop cannot move in a straight line", !legal(s, "f1", "f3"));
    check("TC-24", "Rook cannot move diagonally (custom position)", [] {
        State board = emptyBoard();
        board.at(sq("d4")) = Piece(ROOK, WHITE_PLAYER);
        return !legal(board, "d4", "f6") && legal(board, "d4", "d8") && legal(board, "d4", "a4");
    }());
    check("TC-25", "Queen moves in straight lines and diagonals only (custom position)", [] {
        State board = emptyBoard();
        board.at(sq("d4")) = Piece(QUEEN, WHITE_PLAYER);
        return legal(board, "d4", "h8") && legal(board, "d4", "d1") && legal(board, "d4", "a4") &&
               !legal(board, "d4", "e6");
    }());

    check("TC-26", "Perft depth 1 / 2 / 3 from the start = 20 / 400 / 8902 (standard chess values)",
          perft(start, 1) == 20 && perft(start, 2) == 400 && perft(start, 3) == 8902);
}

static void blocking() {
    cout << "\n== Blocking ==\n";
    State start = initialState();
    check("TC-27", "Bishop, rook and queen are blocked in the initial position",
          !legal(start, "f1", "c4") && !legal(start, "a1", "a3") && !legal(start, "d1", "d3") &&
              !legal(start, "d1", "h5"));

    Game game;
    playAll(game, "e2e4 e7e5");
    check("TC-28", "Pawn cannot move forward into an occupied square", !legal(game.live(), "e4", "e5"));

    State knight = initialState();
    knight.at(sq("e3")) = Piece(KNIGHT, BLACK_PLAYER);
    check("TC-29", "Pawn double step is blocked when the first square is occupied", !legal(knight, "e2", "e4"));

    State slider = emptyBoard();
    slider.at(sq("a1")) = Piece(ROOK, WHITE_PLAYER);
    slider.at(sq("a4")) = Piece(PAWN, BLACK_PLAYER);
    slider.at(sq("c1")) = Piece(BISHOP, WHITE_PLAYER);
    slider.at(sq("e3")) = Piece(PAWN, WHITE_PLAYER);
    check("TC-30", "Sliding pieces stop at the first occupied square and cannot jump",
          legal(slider, "a1", "a3") && legal(slider, "a1", "a4") && !legal(slider, "a1", "a5") &&
              legal(slider, "c1", "d2") && !legal(slider, "c1", "f4"));
}

static void captures() {
    cout << "\n== Captures ==\n";
    Game game;
    playAll(game, "e2e4 d7d5");
    bool captured = game.play(mv("e4", "d5"));
    const State &s = game.live();
    check("TC-31", "Pawn captures diagonally (1.e4 d5 2.exd5)",
          captured && isPiece(s, "d5", PAWN, WHITE_PLAYER) && s.at(sq("e4")).empty());
    check("TC-32", "Captured piece is removed: Black has 15 pieces, White 16",
          countPieces(s, BLACK_PLAYER) == 15 && countPieces(s, WHITE_PLAYER) == 16);
    check("TC-33", "Black recaptures with the queen (2...Qxd5)",
          game.play(mv("d8", "d5")) && isPiece(game.live(), "d5", QUEEN, BLACK_PLAYER) &&
              countPieces(game.live(), WHITE_PLAYER) == 15);

    Game straight;
    playAll(straight, "e2e4 e7e5");
    check("TC-34", "Pawn cannot capture straight ahead and cannot move diagonally to an empty square",
          !legal(straight.live(), "e4", "e5") && !legal(straight.live(), "e4", "d5") && !legal(straight.live(), "e4", "f5"));

    State start = initialState();
    check("TC-35", "Pieces cannot capture their own side",
          !legal(start, "a1", "a2") && !legal(start, "g1", "e2") && !legal(start, "d1", "e1"));

    State board = emptyBoard();
    board.at(sq("d4")) = Piece(KNIGHT, WHITE_PLAYER);
    board.at(sq("e6")) = Piece(BISHOP, BLACK_PLAYER);
    board.at(sq("h1")) = Piece(ROOK, WHITE_PLAYER);
    board.at(sq("h7")) = Piece(QUEEN, BLACK_PLAYER);
    board.at(sq("h4")) = Piece(PAWN, BLACK_PLAYER);
    check("TC-36", "Knight captures an enemy piece; rook captures only the first enemy piece in line",
          legal(board, "d4", "e6") && legal(board, "h1", "h4") && !legal(board, "h1", "h7"));

    State kings = emptyBoard();
    kings.at(sq("e1")) = Piece(KING, WHITE_PLAYER);
    kings.at(sq("e8")) = Piece(KING, BLACK_PLAYER);
    kings.at(sq("e4")) = Piece(ROOK, WHITE_PLAYER);
    check("TC-37", "A king can never be captured (prototype rule)", !legal(kings, "e4", "e8"));
}

static void invalidInput() {
    cout << "\n== Invalid input ==\n";
    Game game;
    State before = game.live();
    bool offBoard = game.play(Move(Square(6, 4), Square(-1, 4))) || game.play(Move(Square(6, 4), Square(6, 8))) ||
                    game.play(Move(Square(8, 0), Square(7, 0))) || game.play(Move(Square(), Square()));
    check("TC-38", "Off-board squares are rejected without changing the game", !offBoard && sameBoard(before, game.live()));
    check("TC-39", "A move to the same square is rejected", !game.play(mv("e2", "e2")));
    check("TC-40", "A move from an empty square is rejected", !game.play(mv("e4", "e5")));
}

int main() {
    cout << "RewindChess engine checks - Sprint 2\n";
    initialPosition();
    turnSwitching();
    basicMovement();
    blocking();
    captures();
    invalidInput();
    cout << "\nResult: " << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}

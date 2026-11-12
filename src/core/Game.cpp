#ifndef REWINDCHESS_GAME_CPP
#define REWINDCHESS_GAME_CPP
#include "Rules.cpp"
using namespace std;

class Game {
public:
    Game(const State &start = initialState()) { newGame(start); }

    void newGame(const State &start = initialState()) {
        state_ = start;
        error_.clear();
    }

    const State &live() const { return state_; }
    const string &error() const { return error_; }

    vector<Move> availableMoves() const { return getLegalMoves(live()); }

    bool play(const Move &move) {
        error_.clear();
        if (!isLegalMove(live(), move)) return reject("Illegal move.");
        state_ = applyMove(live(), move);
        return true;
    }

    string statusText() const { return sideName(live().turn) + " to move"; }

private:
    State state_;
    string error_;

    bool reject(const string &message) {
        error_ = message;
        return false;
    }
};
#endif

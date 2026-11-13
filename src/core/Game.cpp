#ifndef REWINDCHESS_GAME_CPP
#define REWINDCHESS_GAME_CPP
#include "Rules.cpp"
using namespace std;

// Owns the current position and exposes game actions to the interface.
class Game {
public:
    Game(const State &start = initialState()) { newGame(start); }

    // Accept a custom position, or use the standard starting board by default.
    void newGame(const State &start = initialState()) {
        state_ = start;
        error_.clear();
    }

    // Const references let callers read the stored data without copying or changing it.
    const State &live() const { return state_; }
    const string &error() const { return error_; }

    // The interface uses this list to match a selected piece and destination.
    vector<Move> availableMoves() const { return getLegalMoves(live()); }

    // Validate before replacing the position, so a rejected move leaves it unchanged.
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

    // Store feedback and return false so the caller can handle a failed action.
    bool reject(const string &message) {
        error_ = message;
        return false;
    }
};
#endif

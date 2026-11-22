#ifndef REWINDCHESS_GAME_CPP
#define REWINDCHESS_GAME_CPP
#include "Rules.cpp"
using namespace std;

class Game {
public:
    Game(const State &start = initialState()) { newGame(start); }

    void newGame(const State &start = initialState()) {
        vector<State> firstTimeline(1, start);
        timelines_.assign(1, firstTimeline);
        timelines_[0][0].repetitionKey = getPositionKey(start);
        error_.clear();
        updateResult();
    }

    const State &live() const { return timelines_[0].back(); }
    const vector<vector<State>> &timelines() const { return timelines_; }
    const string &error() const { return error_; }

    int result() const { return result_; }
    bool finished() const { return result_ != GAME_PLAYING; }

    vector<Move> availableMoves() const {
        if (finished()) return vector<Move>();
        return getLegalMoves(live());
    }

    bool play(const Move &move) {
        error_.clear();
        if (finished()) return reject("This game has ended.");
        if (!isLegalMove(live(), move)) return reject("Illegal move. Your king must stay safe.");
        State next = applyMove(live(), move);
        next.moveText = getMoveNotation(live(), move, next);
        next.repetitionKey = getPositionKey(next);
        timelines_[0].push_back(next);
        updateResult();
        if (result_ == CHECKMATE && !timelines_[0].back().moveText.empty() && timelines_[0].back().moveText.back() == '+') {
            timelines_[0].back().moveText.back() = '#';
        }
        return true;
    }

    string statusText() const {
        switch (result_) {
        case CHECKMATE: return sideName(opposite(live().turn)) + " wins by checkmate";
        case STALEMATE: return "Draw by stalemate";
        case INSUFFICIENT_MATERIAL: return "Draw by insufficient material";
        case FIVEFOLD_REPETITION: return "Draw by fivefold repetition";
        case SEVENTY_FIVE_MOVES: return "Draw by the 75-move rule";
        case CLAIMED_DRAW: return "Draw claimed";
        }
        string text = sideName(live().turn) + " to move";
        if (isInCheck(live(), live().turn)) text += " - CHECK";
        return text;
    }

    bool canClaimDraw() const {
        return !finished() && (live().halfmoveClock >= 100 || repetitions() >= 3);
    }

    bool claimDraw() {
        if (!canClaimDraw()) return reject("A draw cannot be claimed in this position.");
        result_ = CLAIMED_DRAW;
        return true;
    }

private:
    int repetitions() const {
        string key = getPositionKey(live());
        int count = 0;
        for (int i = 0; i < int(timelines_[0].size()); i++) {
            if (timelines_[0][i].repetitionKey == key) {
                count++;
            }
        }
        return count;
    }

    void updateResult() {
        result_ = GAME_PLAYING;
        if (getLegalMoves(live()).empty()) {
            if (isInCheck(live(), live().turn)) result_ = CHECKMATE;
            else result_ = STALEMATE;
        } else if (hasInsufficientMaterial(live())) {
            result_ = INSUFFICIENT_MATERIAL;
        } else if (live().halfmoveClock >= 150) {
            result_ = SEVENTY_FIVE_MOVES;
        } else if (repetitions() >= 5) {
            result_ = FIVEFOLD_REPETITION;
        }
    }
    vector<vector<State>> timelines_;
    string error_;
    int result_ = GAME_PLAYING;

    bool reject(const string &message) {
        error_ = message;
        return false;
    }
};
#endif

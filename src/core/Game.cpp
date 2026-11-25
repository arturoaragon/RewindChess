#ifndef REWINDCHESS_GAME_CPP
#define REWINDCHESS_GAME_CPP

#include "Rules.cpp"
#include <vector>

using namespace std;

class Game {
public:
    Game(const State &start = initialState()) {
        newGame(start);
    }

    void newGame(const State &start = initialState()) {
        for (int side = 0; side < 2; side++) {
            players_[side] = Player();
        }
        // Start with one timeline containing one position.
        vector<State> firstTimeline(1, start);
        timelines_.assign(1, firstTimeline);
        parentTimelineIds_.assign(1, -1);
        forkStateIndices_.assign(1, 0);
        activeTimeline_ = 0;
        viewedTimeline_ = 0;
        viewedState_ = 0;
        result_ = GAME_PLAYING;
        error_.clear();
        timelines_[0][0].repetitionKey = repetitionKey(start);
        updateResult();
    }

    const State &live() const { return timelines_[activeTimeline_].back(); }

    const State &viewed() const { return timelines_[viewedTimeline_][viewedState_]; }

    const vector<vector<State>> &timelines() const { return timelines_; }

    const vector<int> &parentTimelineIds() const { return parentTimelineIds_; }

    const vector<int> &forkStateIndices() const { return forkStateIndices_; }

    int activeTimeline() const { return activeTimeline_; }

    int viewedTimeline() const { return viewedTimeline_; }

    int viewedState() const { return viewedState_; }

    bool previewing() const {
        return viewedTimeline_ != activeTimeline_ ||
               viewedState_ != int(timelines_[activeTimeline_].size()) - 1;
    }


    int result() const { return result_; }

    bool finished() const { return result_ != GAME_PLAYING; }

    int rewindLimit() const { return 5; }

    int rewindsLeft(int side) const { return rewindLimit() - players_[side].rewindsUsed; }



    bool preview(int timeline, int state) {
        if (timeline < 0 || timeline >= int(timelines_.size()) || state < 0 ||
            state >= int(timelines_[timeline].size())) {
            return false;
        }
        viewedTimeline_ = timeline;
        viewedState_ = state;
        error_.clear();
        return true;
    }

    void backToLive() {
        viewedTimeline_ = activeTimeline_;
        viewedState_ = int(timelines_[activeTimeline_].size()) - 1;
        error_.clear();
    }
    // requester is checked against the LIVE turn, never the preview's turn.
    bool canRewind(int requester) const {
        return previewing() && requester == live().turn && rewindsLeft(requester) > 0;
    }

    bool rewind(int requester) {
        error_.clear();
        if (requester != live().turn) return reject("Only the player to move can rewind.");
        if (!previewing()) return reject("Choose a saved position first.");
        if (rewindsLeft(requester) == 0) return reject("No rewinds left for this player.");
        // Copy the saved positions one by one. The old timeline stays intact.
        vector<State> branch;
        for (int state = 0; state <= viewedState_; state++) {
            branch.push_back(timelines_[viewedTimeline_][state]);
        }
        parentTimelineIds_.push_back(viewedTimeline_);
        forkStateIndices_.push_back(viewedState_);
        timelines_.push_back(branch);
        ++players_[requester].rewindsUsed;
        activeTimeline_ = int(timelines_.size()) - 1;
        // Keep the restored position key consistent with the continued timeline.
        timelines_.back().back().repetitionKey = repetitionKey(live());
        backToLive();
        updateResult();
        return true;
    }

    vector<Move> availableMoves() const {
        if (previewing() || finished()) return vector<Move>();
        return getLegalMoves(live());
    }

    bool play(const Move &move) {
        error_.clear();
        if (previewing()) return reject("History is read-only. Return to live or spend a rewind.");
        if (finished()) return reject("This game has ended. You can still inspect or rewind.");
        if (!isLegalMove(live(), move)) return reject("Illegal move. Your king must stay safe.");
        State next = applyMove(live(), move);
        next.moveText = getMoveNotation(live(), move, next);
        next.repetitionKey = repetitionKey(next);
        timelines_[activeTimeline_].push_back(next);
        backToLive();
        updateResult();
        if (result_ == CHECKMATE) {
            string &text = timelines_[activeTimeline_].back().moveText;
            if (!text.empty() && text.back() == '+') {
                text.back() = '#';
            }
        }
        return true;
    }

    bool canClaimDraw() const {
        return !previewing() && !finished() && (live().halfmoveClock >= 100 || repetitions() >= 3);
    }

    bool claimDraw() {
        if (!canClaimDraw()) return reject("A draw cannot be claimed in this position.");
        result_ = CLAIMED_DRAW;
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

    const string &error() const { return error_; }

private:
    Player players_[2]; // Session resources: intentionally outside State.
    vector<vector<State>> timelines_;
    vector<int> parentTimelineIds_;
    vector<int> forkStateIndices_;
    int activeTimeline_ = 0;
    int viewedTimeline_ = 0;
    int viewedState_ = 0;
    int result_ = GAME_PLAYING;
    string error_;

    bool reject(const string &message) {
        error_ = message;
        return false;
    }

    string repetitionKey(const State &state) const { return getPositionKey(state); }

    int repetitions() const {
        string key = repetitionKey(live());
        int count = 0;
        for (int i = 0; i < int(timelines_[activeTimeline_].size()); i++) {
            if (timelines_[activeTimeline_][i].repetitionKey == key) {
                count++;
            }
        }
        return count;
    }

    bool hasLegalMove() const { return !getLegalMoves(live()).empty(); }

    void updateResult() {
        result_ = GAME_PLAYING;
        if (!hasLegalMove()) {
            if (isInCheck(live(), live().turn)) {
                result_ = CHECKMATE;
            } else {
                result_ = STALEMATE;
            }
        } else if (hasInsufficientMaterial(live())) {
            result_ = INSUFFICIENT_MATERIAL;
        } else if (live().halfmoveClock >= 150) {
            result_ = SEVENTY_FIVE_MOVES;
        } else if (repetitions() >= 5) {
            result_ = FIVEFOLD_REPETITION;
        }
    }
};

#endif

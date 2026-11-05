#ifndef REWINDCHESS_GAME_CPP
#define REWINDCHESS_GAME_CPP
#include "Types.cpp"
using namespace std;

// Architecture only. Board setup and gameplay are implemented next week.
class Game {
public:
    const State &live() const { return state_; }
    string statusText() const { return "Architecture ready - no playable board yet"; }
private:
    State state_;
};
#endif

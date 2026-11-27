# RewindChess User Guide

## 1. Standard Chess Rules (Sprint 3)

### Board Coordinates and Turns
- The board uses an `8x8` grid (`row 0..7` from Rank 8 down to Rank 1; `col 0..7` from File `a` to File `h`).
- White moves first (`WHITE_PLAYER = 0`), followed by Black (`BLACK_PLAYER = 1`).
- Moves that leave or expose the active player's King in check are rejected (`"Illegal move. Your king must stay safe."`).

### Special Moves
- **Castling:** Available kingside (`O-O`) or queenside (`O-O-O`) when neither the King nor the chosen Rook has previously moved, the squares between them are empty, the King is not currently in check, and none of the squares the King passes through or lands on are attacked. Moving the King forfeits both castling rights for that side; moving or capturing a Rook forfeits castling on that flank.
- **En Passant:** When a Pawn advances two squares from its starting rank and lands horizontally adjacent to an enemy Pawn, the opponent may capture it diagonally onto the skipped square **only on the immediately following turn**. The `enPassant` target square expires automatically after one ply if unused.
- **Pawn Promotion:** When a Pawn reaches the furthest rank (Rank 8 for White, Rank 1 for Black), the player promotes it to a **Queen**, **Rook**, **Bishop**, or **Knight** (`promotion` field in `Move`).

### Game Endings and Draw Rules
- **Checkmate (`CHECKMATE`):** The active player is in check and has zero legal moves; the opposing side wins.
- **Stalemate (`STALEMATE`):** The active player is not in check and has zero legal moves; the game ends in a draw.
- **Insufficient Material (`INSUFFICIENT_MATERIAL`):** Automatic draw when neither side has enough material to force checkmate (e.g., K vs. K, K+B vs. K, K+N vs. K).
- **Claimed Draw (`CLAIMED_DRAW`):** Either player on their live turn may claim a draw when `halfmoveClock >= 100` (50 full moves without a pawn push or capture) or when the current position has occurred at least 3 times (`repetitions() >= 3`) on the active timeline.
- **Automatic Draw Limits:** The game ends automatically at 75 full moves without a pawn push or capture (`halfmoveClock >= 150`, `SEVENTY_FIVE_MOVES`) or upon fivefold repetition (`repetitions() >= 5`, `FIVEFOLD_REPETITION`).

### Glossary
- **Ply (Halfmove):** A single turn taken by one player.
- **Live Position (`live()`):** The latest state at the end of the currently active timeline (`timelines_[activeTimeline_].back()`).
- **Preview Mode (`previewing()`):** Inspecting any saved state earlier than the live head of the active timeline, or inspecting any state on an inactive branch.
- **Timeline / Branch:** An independent sequence of saved `State` snapshots (`vector<State>`) starting from the initial board position.

---

## 2. Branching Rewind Mechanics (Sprint 5)

### Free Read-Only Previews vs. Paid Continuation
1. **Browsing is Free (`preview(timeline, state)`):**
   - Players may click any move in the move list or any node in the timeline browser to inspect earlier positions across any timeline at zero resource cost.
   - While in view mode (`previewing() == true`), the board is strictly **read-only**: legal move generation returns empty (`availableMoves()`), piece movement is locked (`"History is read-only. Return to live or spend a rewind."`), and draw claims are disabled.
   - Clicking **Back to live game** (`backToLive()`) exits view mode and returns immediately to the active live position without spending any rewinds.
2. **Continuing from a Past State Costs 1 Rewind (`rewind(requester)`):**
   - To alter history and resume play from a previewed position, the player clicks **Continue from here**, reviews the confirmation dialog (**Use 1 rewind?**), and confirms (or clicks **Cancel** to remain in read-only view mode).

### Preservation of the Original Timeline
- Rewinding never deletes or overwrites played history.
- When a rewind is confirmed at index `viewedState_` on `viewedTimeline_`, the engine copies the exact prefix of states from index `0` up to and including `viewedState_` into a **new branch** (`timelines_.push_back(branch)`), records `parentTimelineIds_` and `forkStateIndices_`, and switches `activeTimeline_` to the new branch.
- The original timeline remains completely intact and can still be inspected at any time in view mode.

### Rewind Limits, Confirmation, and Paying Player Rules
- **Per-Player Limit:** Each player begins the match with **5 rewinds** (`rewindLimit() == 5` in Sprint 5 Practice mode, tracked via `players_[side].rewindsUsed`). Once `rewindsLeft(requester) == 0`, further rewind requests are disabled (`"No rewinds left for this player."`).
- **Confirmation Required:** Selecting a historical snapshot enters view mode first; a branch is created and charged **only after explicit confirmation** (`Use 1 rewind?`). Canceling (`Cancel`) leaves both timelines and rewind counters untouched.
- **Who Pays (`requester == live().turn`):** Rewind eligibility and payment are always evaluated against the **live turn** (`live().turn`), never the side whose turn it happens to be inside the previewed snapshot. Only the player whose turn it currently is on the live board can initiate and pay 1 rewind (`"Only the player to move can rewind."`).
- **No Refunds Across Time Travel:** Player resource counters (`Player players_[2]`) are stored outside `State` snapshots. Rewinding to an earlier state or switching timelines never restores or refunds rewinds already spent earlier in the session.

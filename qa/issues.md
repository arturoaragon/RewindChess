# Prototype issue log

**Author:** Mladen Stamatoski · Started in Sprint 2 (build `8e8fc0a`)

Each issue should also be opened on GitHub with the **Bug report** template and the ID in the title (e.g. `BUG-01: hint stays after selecting a piece`). This file is the summary; GitHub is where the discussion and the fix happen.

Severity: **Critical** (crash, data loss, cannot play) · **Major** (wrong rule or result) · **Minor** (cosmetic or confusing, game still correct) · **Trivial** (wording, code tidiness).

## Summary

| ID | Title | Area | Severity | Owner | Status |
|---|---|---|---|---|---|
| BUG-01 | Red hint stays visible after a valid piece is selected | UI | Minor | Samuel | Open |
| CODE-01 | Leftover `|| false` in a condition in `App::drawBoard` | Code | Trivial | Samuel | Open |

Not bugs: king safety, castling, en passant and promotion are not in the prototype yet because they are planned for Sprint 3.

---

## BUG-01 · Red hint stays visible after a valid piece is selected

- **Area / severity:** UI, Minor
- **Build:** `8e8fc0a`, Linux run 12 Nov 2026 (to confirm on Windows)
- **Steps to reproduce:**
  1. Start a new game.
  2. Click an empty square, e.g. d4. The red hint "Select your piece, then a valid destination." appears.
  3. Click one of your own pieces, e.g. the e2 pawn.
- **Expected:** the pawn is selected and the hint disappears, because the player has now done the right thing.
- **Actual:** the pawn is selected, but the red hint stays until a move is completed. It looks like the selection was rejected.
- **Evidence:** [`UI-12`](evidence/sprint2/UI-12-empty-square.webp) → [`UI-13`](evidence/sprint2/UI-13-select-after-notice.webp)
- **Likely cause:** in `src/ui/App.cpp`, `drawBoard()` sets `selected_ = target;` for a valid piece but does not clear `notice_`.
- **Suggested fix:** clear `notice_` when a valid piece is selected (one line). Retest UI-12 → UI-13.

## CODE-01 · Leftover `|| false` in a condition

- **Area / severity:** Code, Trivial
- **Where:** `src/ui/App.cpp`, `drawBoard()`: `if (!click_ || false || !CheckCollisionPointRec(...)) return;`
- **Effect:** none (`|| false` never changes the result), but it looks like an unfinished condition.
- **Suggestion:** remove `|| false` during the Sprint 3 UI work.

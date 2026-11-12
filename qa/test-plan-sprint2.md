# Sprint 2 test plan and results

**Author:** Mladen Stamatoski · **Sprint 2 deliverable** · Build tested: commit `8e8fc0a` ("week 2 core game code update")

Covers the Sprint 2 QA backlog:

1. Test the initial position and turn switching → TC-01 – TC-15, UI-01 – UI-05
2. Check basic movement, blocking and captures → TC-16 – TC-40, UI-06 – UI-15
3. Record reproducible prototype issues → [`issues.md`](issues.md)

## Summary

| Part | Checks | Passed | Failed | Notes |
|---|---|---|---|---|
| Automated engine checks | 40 | 40 | 0 | |
| UI checks (Linux run) | 15 | 14 | 1 | UI-13 fails: BUG-01 |
| UI checks on Windows | 15 | – | – | **To do: run the checklist below on Windows** |

**Result:** the Sprint 2 acceptance criteria for the app are met (32 pieces, only the player to move can act, valid moves update the board, invalid moves leave it unchanged). One minor UI issue and one code clean-up were recorded.

## Test environment (run of 12 Nov 2026)

| Item | Value |
|---|---|
| OS | Ubuntu 24.04.5 LTS (Linux), virtual display Xvfb, software OpenGL (Mesa llvmpipe) |
| Compiler | g++ 13.3.0, C++17 |
| Build | CMake 3.28.3 + Ninja 1.11.1, Release, raylib 5.5 built from source (same tag as `CMakeLists.txt`) |
| UI input | Mouse clicks and Esc sent with `xdotool`; one screenshot per step |

The target platform is **Windows**. The Linux run proves the game logic and the interface behaviour; the Windows run of the UI checklist still has to be done and recorded in the last column.

## Part A – Automated engine checks

Program: [`tests/engine_checks.cpp`](tests/engine_checks.cpp). It includes only `src/core`, so raylib is not needed.

```powershell
g++ -std=c++17 -Wall -Wextra qa/tests/engine_checks.cpp -o engine_checks.exe
.\engine_checks.exe
```

Full output: [`evidence/sprint2/engine_checks_output.txt`](evidence/sprint2/engine_checks_output.txt).

| ID | Check | Result |
|---|---|---|
| **Initial position** | | |
| TC-01 | 32 pieces on the board, 16 per side | Pass |
| TC-02 | Back ranks are R N B Q K B N R for both sides (queen on the d-file) | Pass |
| TC-03 | White pawns on rank 2, black pawns on rank 7 | Pass |
| TC-04 | Ranks 3 to 6 are empty | Pass |
| TC-05 | Kings start on e1 and e8, and h1 is a light square | Pass |
| TC-06 | White moves first; status reads "White to move" | Pass |
| TC-07 | White has exactly 20 moves in the initial position | Pass |
| **Turn switching** | | |
| TC-08 | Black cannot move first; rejected with "Illegal move." | Pass |
| TC-09 | A rejected move leaves the board and turn unchanged | Pass |
| TC-10 | After a valid white move it is Black to move | Pass |
| TC-11 | The error message is cleared after a valid move | Pass |
| TC-12 | White cannot move twice in a row | Pass |
| TC-13 | After a valid black move it is White to move again | Pass |
| TC-14 | Six alternating moves are accepted; White to move | Pass |
| TC-15 | New game restores the initial position, White to move, no error | Pass |
| **Basic movement** | | |
| TC-16 | Pawn moves one or two squares from its starting rank | Pass |
| TC-17 | Pawn cannot move three squares, sideways or backwards | Pass |
| TC-18 | Pawn cannot move two squares after leaving its starting rank | Pass |
| TC-19 | Knight jumps over pieces from the initial position | Pass |
| TC-20 | Knight cannot make a non-L move | Pass |
| TC-21 | After 1.e4 e5 the bishop, queen and king can use the opened lines | Pass |
| TC-22 | King moves only one square | Pass |
| TC-23 | Bishop cannot move in a straight line | Pass |
| TC-24 | Rook cannot move diagonally | Pass |
| TC-25 | Queen moves in straight lines and diagonals only | Pass |
| TC-26 | Move counts from the start: depth 1 / 2 / 3 = 20 / 400 / 8902 (standard chess values) | Pass |
| **Blocking** | | |
| TC-27 | Bishop, rook and queen are blocked in the initial position | Pass |
| TC-28 | Pawn cannot move forward into an occupied square | Pass |
| TC-29 | Pawn double step is blocked when the first square is occupied | Pass |
| TC-30 | Sliding pieces stop at the first occupied square and cannot jump | Pass |
| **Captures** | | |
| TC-31 | Pawn captures diagonally (1.e4 d5 2.exd5) | Pass |
| TC-32 | Captured piece is removed (Black 15, White 16) | Pass |
| TC-33 | Black recaptures with the queen (2...Qxd5) | Pass |
| TC-34 | Pawn cannot capture straight ahead or move diagonally to an empty square | Pass |
| TC-35 | Pieces cannot capture their own side | Pass |
| TC-36 | Knight captures; a rook captures only the first enemy piece in line | Pass |
| TC-37 | A king can never be captured (prototype rule) | Pass |
| **Invalid input** | | |
| TC-38 | Off-board squares are rejected without changing the game | Pass |
| TC-39 | A move to the same square is rejected | Pass |
| TC-40 | A move from an empty square is rejected | Pass |

**Why TC-26 matters:** in the first three moves no checks, castling, en passant or promotion are possible, so the number of possible move sequences must equal the published chess values (20, 400, 8902). One test therefore covers every piece's movement in thousands of positions.

**Do the checks catch bugs?** Yes. As a control, two bugs were put into a temporary copy of `Rules.cpp` (bishops ignore blocking pieces; the turn does not switch). The checks then reported **13 failures**. The real code was not changed.

## Part B – UI checklist

Run on the real build. Screenshots of key steps: [`evidence/sprint2/`](evidence/sprint2/).

| ID | Steps | Expected | Linux 12 Nov | Windows (to fill in) |
|---|---|---|---|---|
| UI-01 | Start the game | Window opens; 32 pieces; "White to move" | Pass ([shot](evidence/sprint2/UI-01-launch.webp)) | |
| UI-02 | Click the e2 pawn | Amber frame on e2 | Pass | |
| UI-03 | Click e4 | Pawn moves to e4; "Black to move" | Pass ([shot](evidence/sprint2/UI-03-e2e4.webp)) | |
| UI-04 | Click a white piece (d2) on Black's turn | Nothing selected; red hint shown | Pass | |
| UI-05 | Play e7–e5 | Pawn moves; hint cleared; "White to move" | Pass | |
| UI-06 | Click the a1 rook, then a3 | Rook stays (blocked by a2); hint shown; still White to move | Pass ([shot](evidence/sprint2/UI-06-blocked-rook.webp)) | |
| UI-07 | Play Ng1–f3 | Knight jumps over the pawns | Pass | |
| UI-08 | Play Nb8–c6, then Bf1–c4 | Both moves accepted | Pass | |
| UI-09 | Play d7–d5, then e4xd5 | Black pawn removed; white pawn on d5 | Pass ([shot](evidence/sprint2/UI-09-capture.webp)) | |
| UI-10 | Click the c6 knight | Amber frame on c6 | Pass | |
| UI-11 | Press Esc | Frame disappears | Pass | |
| UI-12 | Click the empty square d4 | Red hint "Select your piece, then a valid destination." | Pass ([shot](evidence/sprint2/UI-12-empty-square.webp)) | |
| UI-13 | Click the c6 knight again | Knight selected **and the old hint disappears** | **Fail – hint stays (BUG-01)** ([shot](evidence/sprint2/UI-13-select-after-notice.webp)) | |
| UI-14 | Click the selected knight again | Knight stays selected (by design; Esc cancels) | Pass | |
| UI-15 | Click "New game" | Initial position; White to move; no hint | Pass ([shot](evidence/sprint2/UI-15-new-game.webp)) | |

## Exit criteria for Sprint 2

- [x] All engine checks pass.
- [x] No critical or major issue open.
- [x] Every failure has an issue with steps to reproduce (`issues.md`).
- [ ] UI checklist repeated on Windows and the last column filled in.

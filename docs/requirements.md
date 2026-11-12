# Scope, requirements and acceptance criteria

**Author:** Filip Sekulovski · **Version 2** (Sprint 2: requirements finalised, scope updated)

| Version | Sprint | Change |
|---|---|---|
| 1 | Sprint 1 (29 Oct – 1 Nov) | Scope and acceptance criteria written (sections 1 and 4) |
| 2 | Sprint 2 (2 – 8 Nov) | Functional and non-functional requirements added with status; scope updated after the prototype; open questions listed |

Sources: sprint backlog PDF (8 sprints), weekly project plan spreadsheet, website mockup, `weeklyInformation/updatesweek0.md`, the code in `src/`.

---

## 1. Scope

### Product

RewindChess is a **local two-player chess game for Windows**, written in C++17 with raylib. Players can rewind to an earlier position and continue in a new timeline. The original game is kept, so both outcomes can be compared.

### In scope

- Full standard chess rules for two players on one computer.
- Move history with a snapshot of the full game state after every valid move.
- Rewinding: free read-only viewing of past positions; continuing from a past position creates a new timeline and costs one rewind.
- Three game modes with different rewind and ability allowances.
- Three special abilities (one use per player, one mode only).
- A Windows executable with all images and fonts.
- An informational website with a download area.
- Documentation: README, user guide, technical documentation, final report.
- QA: test plan, automated engine checks, manual UI checks, issue tracking, demo.

### Out of scope

- Online or network play (the game is local).
- A computer opponent.
- Playing in the web browser (the website is informational and for downloads only).
- Platforms other than Windows for the delivered executable. (The code is portable; other platforms are not tested or supported.)

_To confirm with the team: saving games to a file and a chess clock are not mentioned in any plan, so they are treated as out of scope._

## 2. Functional requirements

Status after Sprint 2: **Done** = in the code and verified by QA (`qa/test-plan-sprint2.md`); **Planned** = scheduled in the backlog.

### Game (app team)

| ID | Requirement | Sprint | Status | Evidence |
|---|---|---|---|---|
| FR-01 | The game starts from the standard position with 32 pieces; White moves first. | 2 | Done | TC-01 – TC-07, UI-01 |
| FR-02 | Turns alternate after every valid move; only the player to move can act. | 2 | Done | TC-08 – TC-14, UI-03 – UI-05 |
| FR-03 | Every piece moves according to its basic movement rule. | 2 | Done | TC-16 – TC-26 |
| FR-04 | Pawns, bishops, rooks and queens cannot pass through occupied squares. | 2 | Done | TC-27 – TC-30, UI-06 |
| FR-05 | A move to a square with an enemy piece captures it; a player cannot capture their own pieces. | 2 | Done | TC-31 – TC-36, UI-09 |
| FR-06 | Moves to squares outside the board are rejected without changing the game. | 2 | Done | TC-38 – TC-40 |
| FR-07 | Mouse: click a piece, then its destination. Esc cancels. "New game" resets. | 2 | Done | UI-02, UI-11, UI-15 |
| FR-08 | A move that leaves the mover's king in check is rejected; check, checkmate and stalemate are detected. | 3 | Planned | |
| FR-09 | Castling (with loss of castling rights), en passant (one move only) and promotion to any of four pieces. | 3 | Planned | |
| FR-10 | Draws by insufficient material and the move-count clocks; no moves are allowed after the game ends. | 3 | Planned | |
| FR-11 | A full copy of the game state (board, turn, rights, clocks) is saved after every valid move. | 4 | Planned | |
| FR-12 | History is stored as a list of timelines, each a list of states (`vector<vector<State>>`). | 4 | Planned | |
| FR-13 | Draw rules that depend on history (position repetition) and a draw-claim action. | 4 | Planned | |
| FR-14 | Any earlier position can be viewed for free; pieces cannot be moved while viewing. | 5 | Planned | |
| FR-15 | "Continue from here" (only on the player's own turn, after confirmation) copies the history up to that point into a new timeline; the original timeline is unchanged. | 5 | Planned | |
| FR-16 | Each continuation costs the requesting player one rewind; counters are per player and never refunded. | 5 | Planned | |
| FR-17 | Three modes: Practice (5 rewinds, 0 abilities), Competitive (1, 0), Competitive + Abilities (1, 1). | 6 | Planned | |
| FR-18 | Abilities: Bishop Step, Pawn Strike and a knight ability (see open question Q1). One shared use per player; used only if the move is legal and the king is safe; not refunded by a rewind. | 6 | Planned | |
| FR-19 | Interface: move list, timeline browser, highlights, resource panel, alerts and shortcuts. | 7 | Planned | |
| FR-20 | Windows executable that starts on a clean computer with all resources. | 7 – 8 | Planned | |

### Website (Ivan)

| ID | Requirement | Sprint | Status |
|---|---|---|---|
| WR-01 | Four pages (Home, How to play, About, Download) with one shared header and navigation. | 2 | Done |
| WR-02 | Home introduces the project and gives an overview of modes and rewinds. | 2 | Done |
| WR-03 | Responsive styling based on the mockup. | 3 | Planned |
| WR-04 | Rules, game modes and visual explanations of rewinding. | 3 | Planned |
| WR-05 | Published on GitHub Pages, with a DuckDNS address if possible. | 4 – 5 | Planned |
| WR-06 | Ability descriptions and real screenshots of each mode. | 6 | Planned |
| WR-07 | Download area linked to the GitHub Release, verified from another computer. | 7 – 8 | Planned |

### Documentation (Filip) and QA (Mladen)

| ID | Requirement | Sprint | Status |
|---|---|---|---|
| DR-01 | README with requirements and build steps. | 2 | Done (app team + website/QA section) |
| DR-02 | Prototype structure and usage documented. | 2 | Done: `docs/prototype-guide.md` |
| DR-03 | User guide (rules, special rules, glossary). | 3 – 7 | Planned |
| DR-04 | Technical documentation of the classes, `State` fields and snapshots. | 4 | Planned |
| DR-05 | Final report with genuine test evidence. | 8 | Planned |
| QR-01 | Automated engine checks that anyone can build and run. | 2 | Done: `qa/tests/engine_checks.cpp` |
| QR-02 | Every confirmed issue recorded with steps to reproduce, then retested after a fix. | 2 – 8 | Started: `qa/issues.md` |
| QR-03 | Full regression run on the frozen version before delivery. | 8 | Planned |

## 3. Non-functional requirements

| ID | Requirement |
|---|---|
| NFR-01 | C++17, raylib 5.5, CMake 3.20 or newer with Ninja. |
| NFR-02 | The engine (`src/core`) does not include raylib; graphics and input stay in `src/ui`. |
| NFR-03 | Build output is written outside the source folder; no generated files are committed. |
| NFR-04 | All images and fonts are licensed for redistribution, and their licence files are kept next to them. |
| NFR-05 | The window can be resized (minimum 720 × 540) and the board scales with it. |
| NFR-06 | Any player action that is not allowed leaves the game state unchanged and shows a short message. |
| NFR-07 | The website is static HTML/CSS/JS, works from disk and on GitHub Pages, and needs no external services. |
| NFR-08 | Website text meets WCAG AA contrast and can be used with the keyboard. |

## 4. Acceptance criteria per sprint

The app criteria for Sprints 1–2 are taken from `weeklyInformation/updatesweek2.md`. Support-team criteria are new.

### Sprint 1 – Organisation and design

- [x] Classes, folders and the engine/UI separation are agreed and visible in the repository.
- [x] Website navigation, responsibilities and publishing plan are written down (`docs/website-plan.md`).
- [x] Scope and acceptance criteria exist (this document, version 1).
- [x] Ownership, weekly coordination, task tracking and review/QA process are written down (`qa/coordination.md`, `qa/qa-process.md`).

### Sprint 2 – Playable prototype

- [x] The board displays 32 pieces, and only the player to move can act.
- [x] Valid basic moves update the board; invalid moves leave the state unchanged.
- [x] The website skeleton (four pages, shared navigation) and the startup instructions are ready for review.
- [x] Requirements are finalised with a status per item (this document, version 2).
- [x] Initial position, turns, movement, blocking and captures are tested; results and issues are recorded.

### Sprints 3–8 (summary)

| Sprint | Accepted when |
|---|---|
| 3 | Check, checkmate, stalemate, castling, en passant and all four promotions work and are tested; rules pages and user guide started. |
| 4 | One saved state per valid move; restoring a state restores board, turn, rights and clocks; site hosted. |
| 5 | Viewing is free and read-only; continuing creates a branch and preserves the original; counters and limits tested. |
| 6 | Three modes and three abilities work; abilities spend only on success; modes documented and playtested. |
| 7 | Feature-complete release candidate; fixed issues retested; presentation draft. |
| 8 | Tagged final version, working executable, published website and downloads, final report with real evidence. |

## 5. Open questions

| ID | Question | Raised | Needed by |
|---|---|---|---|
| Q1 | **Knight ability:** the mockup and the older `.xlsx` plan say **Knight Step** (one square straight). The Week 1 report and the backlog (Sprint 6) say **Knight Swap** (jump onto a friendly piece and swap places). Which one is final? | Sprint 2 | Sprint 3 (website text), Sprint 6 (code) |
| Q2 | Confirm that the repository `.ods` plan and the backlog (8 sprints from 29 Oct) are the only current plan, and retire the older `.xlsx` copy (9 weeks from 20 Oct). This document follows the current plan. | Sprint 2 | Sprint 3 |
| Q3 | Are saving games and a chess clock definitely out of scope? | Sprint 1 | Sprint 3 |

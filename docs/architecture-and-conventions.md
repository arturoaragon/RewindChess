# Agreed classes and conventions

**Author:** Filip Sekulovski · **Sprint 1** ("Document the agreed classes and conventions")

The agreed classes and conventions, checked against the code in the repository.

## 1. File structure and include chain

The project is compiled as **one translation unit**: CMake compiles only `src/main.cpp`, and each file includes the one below it.

```text
src/main.cpp            entry point: creates App and calls run()
 └─ src/ui/App.cpp      window, drawing and mouse/keyboard input (raylib)
     └─ src/core/Game.cpp    game coordination: current state, play(), errors
         └─ src/core/Rules.cpp   movement rules, initial position, move generation
             └─ src/core/Types.cpp   constants and the basic classes
```

Each `.cpp` file has an include guard named `REWINDCHESS_<FILE>_CPP`. A new engine file must follow the same pattern and be included from the file that uses it.

**Engine/UI separation:** nothing in `src/core` includes `raylib.h`. This is what lets QA compile and test the engine without graphics (`qa/tests/engine_checks.cpp`). Keep it that way.

## 2. Board coordinates

| | Index 0 | Index 7 |
|---|---|---|
| `row` | rank 8 (Black's back rank) | rank 1 (White's back rank) |
| `col` | file a | file h |

So `e2` is `Square(6, 4)` and `e8` is `Square(0, 4)`. `squareName(Square)` converts back to text ("e2"). White pawns move towards row 0 (`pawnDirection(WHITE_PLAYER) == -1`).

## 3. Constants (`Types.cpp`)

| Constant | Values |
|---|---|
| Sides | `WHITE_PLAYER = 0`, `BLACK_PLAYER = 1` |
| Piece types | `NO_PIECE = 0`, `PAWN = 1`, `KNIGHT = 2`, `BISHOP = 3`, `ROOK = 4`, `QUEEN = 5`, `KING = 6` |

Plain `int` constants are used instead of `enum class` on purpose (agreed for readability in Sprint 1).

## 4. Agreed classes

| Class | File | Responsibility |
|---|---|---|
| `Square` | `src/core/Types.cpp` | A board coordinate (row, column). |
| `Piece` | `src/core/Types.cpp` | What stands on a square: type and side. |
| `Move` | `src/core/Types.cpp` | A move from one square to another. |
| `State` | `src/core/Types.cpp` | Everything needed to continue a game: the board and whose turn it is. |
| `Game` | `src/core/Game.cpp` | The live game: plays moves and stores the error message for rejected moves. |
| `App` | `src/ui/App.cpp` | Window, drawing and mouse/keyboard input. It asks `Game` to play moves and never changes the board itself. |

The movement rules are free functions in `src/core/Rules.cpp`. The full description of every class, field and function is planned for Sprint 4 ("Document the actual classes and architecture").

### Planned classes vs. actual classes

The Week 1 plan named `Board`, `Piece`, `Move`, `GameState` and `Timeline`. The code maps them like this (from `updatesweek1.md`):

| Planned | In the code |
|---|---|
| `Board` | `State::board` |
| `GameState` | `State` |
| `Timeline` | a `vector<State>` inside `Game` (Sprint 4); all timelines = `vector<vector<State>>` |

## 5. Code conventions (as used in the code)

- `PascalCase` for classes (`Game`), `camelCase` for functions and variables (`isLegalMove`, `selected_`).
- Private member variables end with `_` (`state_`, `error_`).
- Engine constants are `UPPER_SNAKE_CASE`; UI layout constants in `App.cpp` are `PascalCase` (`BoardX`, `Cell`). New UI constants should follow `App.cpp`; new engine constants should follow `Types.cpp`.
- `using namespace std;` is used in every file.
- Functions that only read a `State` take it as `const State &`.
- Comments explain *why* (for example the prototype limits in `isLegalMove`), not what each line does.
- Any action that is not allowed must leave the state unchanged and set a short message (`Game::reject`).

## 6. Repository conventions

| Item | Convention |
|---|---|
| Folders | `src/core` engine, `src/ui` interface, `assets/` images and fonts with licences, `website/`, `docs/`, `qa/`, `weeklyInformation/` |
| Weekly updates | One file per sprint in `weeklyInformation/`. App team: `updatesweekN.md`. Support team: one report per person, `sprintN-<name>.md`. |
| Branches | One branch per member and task, e.g. `ivan/sprint3-responsive`, `mladen/sprint3-check-tests`. |
| Commits | Short imperative subject with the area and sprint, e.g. `website: add how-to-play structure (S2)`. |
| Pull requests | Every change to `main` goes through a pull request reviewed by one other member (see `qa/qa-process.md`). |
| Build output | Outside the repository (`..\..\RewindChess-weekly-build`). |
| Docs | Markdown, English, dates as "12 Nov 2026". |

---

## Sprint 4 Update: Implemented Classes & State Restoration

### Core Data Structures (`src/core/Types.cpp`)
- **`Square`:** Stores `int row` (`0` = Rank 8, `7` = Rank 1) and `int col` (`0` = File `a`, `7` = File `h`), with `valid()` and `sameAs()` helpers.
- **`Piece`:** Stores `int type` (`NO_PIECE=0`, `PAWN=1`, `KNIGHT=2`, `BISHOP=3`, `ROOK=4`, `QUEEN=5`, `KING=6`) and `int side` (`WHITE_PLAYER=0`, `BLACK_PLAYER=1`).
- **`Move`:** Stores `Square from`, `Square to`, and `int promotion`.
- **`CastlingRights`:** Stores `bool kingSide[2]` and `bool queenSide[2]` indexed by player side.
- **`Player`:** Stores `int rewindsUsed = 0`. Kept outside `State` so session resource usage persists across all timeline branches.

### Fields Stored in `State` (`src/core/Types.cpp`)
Every valid move produces a self-contained `State` snapshot containing:
1. `Piece board[8][8]` — Full 64-square piece placement array.
2. `int turn` — Side to move (`WHITE_PLAYER` or `BLACK_PLAYER`).
3. `CastlingRights castling` — Remaining kingside and queenside castling flags for both players.
4. `Square enPassant` — Target capture square for en passant (invalid `Square(-1, -1)` when unavailable).
5. `int halfmoveClock` — Plies elapsed since the last pawn move or capture (used for 50-move claim and 75-move automatic draw).
6. `int fullmoveNumber` — Full turn counter starting at `1` and incrementing after Black's move.
7. `Move lastMove` — The move that produced this state.
8. `string moveText` — Standard algebraic notation string (e.g., `"Start"`, `"e4"`, `"Nf3+"`, `"Qh7#"`).
9. `string repetitionKey` — Serialized position key (`getPositionKey(state)`) used to detect threefold and fivefold repetition.

### Snapshots & Restoration (`src/core/Game.cpp`)
- **History Storage:** `Game` stores all timelines in `vector<vector<State>> timelines_`, paired with `parentTimelineIds_` and `forkStateIndices_` to track where each branch forked.
- **Snapshot Creation:** On every valid `play(move)`, `applyMove(live(), move)` computes the next `State`, assigns `moveText` and `repetitionKey`, and appends it to `timelines_[activeTimeline_]`.
- **State Restoration:** Because `State` contains no external pointers, copying `timelines_[viewedTimeline_][0..viewedState_]` into a new `vector<State>` restores a completely independent game state (board, turn, castling rights, en passant target, clocks, and repetition history).

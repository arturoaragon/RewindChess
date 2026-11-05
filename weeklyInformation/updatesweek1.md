# Week 1 - Development Progress

Reconstructed milestone (20 Oct – 25 Oct 2026), created on 4 November 2026 from the definitive code and the proposed roadmap. This describes differences between reconstructed snapshots, not verified historical activity.

## 1. Objectives for the week

App team, spreadsheet `Weekly Plan!C6`: Agree C++17 architecture; define Board, Piece, Move, GameState, Timeline classes; set up compiler/repo and GUI library.

Milestone, `E6`: Architecture and deliverables agreed.

Support-team plan, `D6`: Split documentation and website ownership; refine requirements, acceptance criteria and task backlog; confirm website sections from mockup.

Support tasks are recorded for traceability; website/hosting/team activity is not implemented or claimed here.

## 2. Implemented features

- C++17 build and raylib architecture window.
- Square, Piece, Move, State and Game definitions; game and UI separated.

`Square` (`valid`, `sameAs`), `Piece` (`empty`), `Move`, `State` (`at`), `Game` (`live`, `statusText`) and the architecture window in `App.run` are defined. Board placement and timeline storage remain design responsibilities only.

## 3. Modified files

Compared with an empty project:

- `src/main.cpp`
- `src/core/Game.cpp`
- `src/core/Types.cpp`
- `src/ui/App.cpp`
- `README.md` and `updatesweek1.md`: this stage's documentation.
- `CMakeLists.txt`: compiler/raylib setup.

## 4. Current project status

The application opens a working raylib architecture window. Basic classes exist, but no pieces are placed and no moves can be played.

## 5. Pending work

No initial piece placement, playable chessboard, moves, special rules, snapshots, rewinds or abilities yet.

## Interpretation and validation

The original spreadsheet has proposed dates and Not started statuses; reconstruction does not change those statuses. Planned Board/GameState/Timeline responsibilities map to the definitive `State::board`, `State`, and `Game`/`vector<State>` architecture.

Validation actually performed on 4 November 2026 on this Windows computer:

- CMake Release/Ninja configuration: passed.
- Compilation and executable link: passed using MinGW-w64 and raylib 5.5.
- Engine/class behavior: **6 checks passed**.
- Architecture milestone: no playable-board interaction test applies; the architecture window was launched instead.
- The actual `RewindChess.exe` opened a native window, stayed running, and closed normally with exit code 0.
- Local source includes stay inside this snapshot; no other version folder is required.
- No generated binaries or build folders are included in the source snapshot.

Logs and temporary check programs are outside the project, in `../../RewindChess-weekly-build/semana1`. The build used the pinned raylib source already cached on this machine, with each week compiling its own library. An installed-package attempt encountered raylib linker flags containing unquoted spaces; using the source-build path resolved validation. Standalone CMake can download the same pinned raylib release.

These are reconstruction-time checks, not historical weekly results. No second-PC test, website deployment, GitHub release, team playtest, presentation or submission was performed or claimed.

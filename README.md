# RewindChess - Week 1

**Reconstructed end-of-week snapshot**, based on the proposed Excel roadmap, 20 Oct – 25 Oct 2026. Created on 4 November 2026, not an archived historical checkout or a record of work actually completed on those dates.

RewindChess is a local two-player C++17 desktop chess game. This independent snapshot represents the stage "Architecture and deliverables agreed" for the application team.

## Available at this stage

- Week 1: C++17 build and raylib architecture window; Square, Piece, Move, State and Game definitions; game and UI separated.

## Structure and dependencies

- `src/core/Types.cpp`: the classes and constants available at this stage.
- `src/core/Game.cpp`: game coordination and the week's state/history/resource model.
- `src/ui/App.cpp`: raylib graphics and input, kept separate from game rules.
- `src/main.cpp`: entry point; only this file is compiled directly.
- `updatesweek1.md`: objectives, actual changes, pending work and validation evidence.

The final architecture represents the planned Board inside `State::board`, GameState as `State`, and Timeline as `vector<State>` managed by `Game`. Week 1 defines the basic architecture; stored timelines are implemented in week 4. This follows the existing class names rather than introducing duplicate wrapper classes. All owned source remains simple `.cpp` files with methods inside classes.

Requirements: C++17 compiler, CMake 3.20+, Ninja, and raylib 5.5. CMake locates raylib or downloads the pinned release on first configuration. No other week's folder is needed. Source and resources are copied locally; build directories are kept outside this project.

## Configure, compile and run

Open PowerShell in this project's folder, beside `CMakeLists.txt`, then run:

```powershell
$buildFolder = Join-Path "..\..\RewindChess-weekly-build" (Split-Path -Leaf $PWD)
cmake -S . -B "$buildFolder" -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build "$buildFolder" --parallel
& "$buildFolder\RewindChess.exe"
```

The first line uses your current folder's name automatically. These relative paths work even if you rename the project folder; each version gets its own build directory outside the source project.

For Visual Studio generators use `--config Release` on the build command and the `Release` executable subfolder. The shown commands use Ninja, as on this computer.

## Controls

The program opens the architecture window. Close it or press Esc. No playable board is provided yet.

## Limits and next steps

No initial piece placement, playable chessboard, moves, special rules, snapshots, rewinds or abilities yet.

The support-team column is context only: no website source was supplied, and no publishing, second-PC testing, team contributions, release tags or historical completion claims are fabricated. The original spreadsheet marks all statuses Not started.

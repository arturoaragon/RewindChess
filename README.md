# RewindChess - version 4

**Sprint 4: History and restoration** · 16 - 22 Nov 2026.

RewindChess is a local two-player chess game in C++17. This folder reconstructs a planned milestone; it is not a historical record of work completed on those dates.

## Current version status

- Sprint 1: Class responsibilities and dependencies are designed. Folders, working practices and scope are planned.
- Sprint 2: Initial board, turns, basic movement, captures and blocking. Graphical prototype with mouse selection.
- Sprint 3: Check, checkmate, stalemate and king safety. Castling, en passant, all four promotions and notation.
- Sprint 4: Complete snapshots after valid moves and vector-based history. Independent copy restoration, position keys and history-dependent draws.

## Structure

- `src/core/Types.cpp`: available classes and constants.
- `src/core/Rules.cpp`: implemented movement and chess rules.
- `src/core/Game.cpp`: game coordination and, when available, history/resources.
- `src/ui/App.cpp`: graphics and input, separated from the engine.
- `src/main.cpp`: entry point; the only directly compiled source file.
- `assets/`: pieces, fonts and licenses.
- `CMakeLists.txt`: C++17 and raylib configuration.

## Run the included game

Double-click `RewindChess.exe`, or run this command in PowerShell from this folder:

```powershell
.\RewindChess.exe
```

The included executable is for 64-bit Windows and needs no compiler. Keep the `assets` folder beside it.

## Build and run

Requirements: a C++17 compiler, CMake, Ninja and raylib 5.5. CMake downloads the library if needed. Open PowerShell in this folder, beside `CMakeLists.txt`:

```powershell
$buildFolder = Join-Path "..\..\RewindChess-weekly-build" (Split-Path -Leaf $PWD)
cmake -S . -B "$buildFolder" -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build "$buildFolder" --parallel
& "$buildFolder\RewindChess.exe"
```

The path is relative and uses the current folder name automatically. Generated files stay outside the source project, under `RewindChess-weekly-build`.

## Controls

Click a piece, then its destination. New game resets the match. Esc cancels the selection.
When a pawn promotes, choose Queen, Rook, Bishop or Knight.
A draw can be claimed when repetition or the 50-move rule permits it.

## Limitations and next steps

No history navigation, rewind action, branches, budgets or powers. Restoration is tested by constructing a separate game from a copied State.

## Planning and version mapping

Retains the former version4. Restoration does not introduce browsing or rewinding before sprint 5.

The backlogs also include the group's planned website, documentation and QA work. This game snapshot does not certify website completion or historical activity by its owners. See [the eight sprint backlogs](../planning/Sprint_Backlogs_8_Weeks.md).

# RewindChess - version 5

**Sprint 5: Branching rewind** · 23 - 29 Nov 2026.

RewindChess is a local two-player chess game in C++17. This folder reconstructs a planned milestone; it is not a historical record of work completed on those dates.

## Current version status

- Sprint 1: Class responsibilities and dependencies are designed. Folders, working practices and scope are planned.
- Sprint 2: Initial board, turns, basic movement, captures and blocking. Graphical prototype with mouse selection.
- Sprint 3: Check, checkmate, stalemate and king safety. Castling, en passant, all four promotions and notation.
- Sprint 4: Complete snapshots after valid moves and vector-based history. Independent copy restoration, position keys and history-dependent draws.
- Sprint 5: Read-only browsing and confirmation before branching. Original timelines are retained; each player has five rewinds.

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
Previous / Next browse saved states; Timeline changes branches; Back to live or End returns to the present. Continue from here requires confirmation before spending a rewind.

## Limitations and next steps

Only the five-rewind configuration is available. The three modes and powers arrive in version6; the complete interface is integrated in version7.

## Planning and version mapping

Retains the former version5. The provisional allowance is the Practice limit; all three modes arrive in sprint 6.

The backlogs also include the group's planned website, documentation and QA work. This game snapshot does not certify website completion or historical activity by its owners. See [the eight sprint backlogs](../planning/Sprint_Backlogs_8_Weeks.md).

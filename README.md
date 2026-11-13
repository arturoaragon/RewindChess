# RewindChess - version 2

**Sprint 2: Playable prototype** · 2 - 8 Nov 2026.

RewindChess is a local two-player chess game in C++17. This folder reconstructs a planned milestone; it is not a historical record of work completed on those dates.

## Current version status

- Sprint 1: Class responsibilities and dependencies are designed. Folders, working practices and scope are planned.
- Sprint 2: Initial board, turns, basic movement, captures and blocking. Graphical prototype with mouse selection.

## Structure

- `src/core/Types.cpp`: available classes and constants.
- `src/core/Rules.cpp`: implemented movement and chess rules.
- `src/core/Game.cpp`: game coordination and, when available, history/resources.
- `src/ui/App.cpp`: graphics and input, separated from the engine.
- `src/main.cpp`: entry point; the only directly compiled source file.
- `assets/`: pieces, fonts and licenses.
- `CMakeLists.txt`: C++17 and raylib configuration.

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

## Limitations and next steps

No king-safety checks, special rules, endings, history, rewinds, modes or powers. Pawns do not promote yet.

## Website, documentation and QA

The support team's work lives next to the game code:

- `website/`: the project website (Home, How to play, About, Download). Open `website/index.html` in a browser to preview it. See [`website/README.md`](website/README.md).
- `docs/`: scope and requirements, classes and conventions, the prototype guide, report outlines and the sprint backlogs. Start with [`docs/requirements.md`](docs/requirements.md).
- `qa/`: test plans, the issue log, evidence and the automated engine checks. See [`qa/README.md`](qa/README.md).
- `weeklyInformation/sprintN-<name>.md`: each support-team member's sprint report.

Run the engine checks from this folder (no raylib needed):

```powershell
g++ -std=c++17 -Wall -Wextra qa/tests/engine_checks.cpp -o engine_checks.exe
.\engine_checks.exe
```

## Planning and version mapping

Retains the former version2 implementation, including the basic classes from the former version1.

The backlogs also include the group's planned website, documentation and QA work. See [the eight sprint backlogs](docs/sprint-backlogs.md).

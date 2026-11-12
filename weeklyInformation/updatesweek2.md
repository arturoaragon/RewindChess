# Sprint 2 - Version update

**Planned period:** 2 - 8 Nov 2026. Adapted to eight sprints and translated into English on 6 November 2026.

## Objective

Provide a local graphical board with the initial position, turns and basic movement, alongside the website skeleton.

## Added functionality or documentation

- Initial board, turns, basic movement, captures and blocking.
- Graphical prototype with mouse selection.

## Changes from the previous milestone

Retains the former version2 implementation, including the basic classes from the former version1.
All source, configuration and resources are introduced. The basic classes from the former first version are already included here.


## Proposed acceptance criteria

- The board displays 32 pieces, and only the player to move can act.
- Valid basic moves update the board; invalid moves leave the state unchanged.
- The website skeleton and startup instructions are ready for review.

## Pending work

No king-safety checks, special rules, endings, history, rewinds, modes or powers. Pawns do not promote yet.

## Validation

Verified on this Windows computer on 6 November 2026: CMake Release/Ninja configuration, MinGW-w64 compilation, 16 engine checks, 3 interface checks, all resource copies, and executable startup/clean close with exit code 0. The cached raylib 5.5 source was used. Logs are outside the project, in `../../RewindChess-weekly-build/eight-sprints/version2`. This checks the reconstructed snapshot, not historical team activity or execution of the website backlog.

The English translation preserves the source, configuration and resource bytes; these software results still apply. Document contents, links and generated planning files are checked separately.

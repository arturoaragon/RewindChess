# Sprint 4 - Version update

**Planned period:** 16 - 22 Nov 2026. Adapted to eight sprints and translated into English on 6 November 2026.

## Objective

Save a complete state after every valid move and demonstrate that a copied state restores a game correctly.

## Added functionality or documentation

- Complete snapshots after valid moves and vector-based history.
- Independent copy restoration, position keys and history-dependent draws.

## Changes from the previous milestone

Retains the former version4. Restoration does not introduce browsing or rewinding before sprint 5.
The existing milestone implementation is retained. Its documentation is adapted to the ODS calendar and the eight-sprint structure.


## Proposed acceptance criteria

- History contains the initial state plus the valid moves.
- Restoring a copy preserves the board, turn, castling, en passant and clocks.
- The restored copy is independent; technical documentation and the checklist are drafted.

## Pending work

No history navigation, rewind action, branches, budgets or powers. Restoration is tested by constructing a separate game from a copied State.

## Validation

Verified on this Windows computer on 6 November 2026: CMake Release/Ninja configuration, MinGW-w64 compilation, 69 engine checks, 12 interface checks, all resource copies, and executable startup/clean close with exit code 0. The cached raylib 5.5 source was used. Logs are outside the project, in `../../RewindChess-weekly-build/eight-sprints/version4`. This checks the reconstructed snapshot, not historical team activity or execution of the website backlog.

The English translation preserves the source, configuration and resource bytes; these software results still apply. Document contents, links and generated planning files are checked separately.

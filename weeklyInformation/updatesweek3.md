# Sprint 3 - Version update

**Planned period:** 9 - 15 Nov 2026. Adapted to eight sprints and translated into English on 6 November 2026.

## Objective

Complete normal chess rules and connect them to the interface, with information pages and an initial user guide.

## Added functionality or documentation

- Check, checkmate, stalemate and king safety.
- Castling, en passant, all four promotions and notation.

## Changes from the previous milestone

Retains the former version3.
The existing milestone implementation is retained. Its documentation is adapted to the ODS calendar and the eight-sprint structure.


## Proposed acceptance criteria

- No accepted move leaves the moving side's king in check.
- Castling, en passant and all four promotions follow their restrictions.
- Checkmate and stalemate stop play; the rules and initial guide are ready for review.

## Pending work

No stored history, repetition detection, browsing, branches, rewinds, modes or abilities.

## Validation

Verified on this Windows computer on 6 November 2026: CMake Release/Ninja configuration, MinGW-w64 compilation, 40 engine checks, 11 interface checks, all resource copies, and executable startup/clean close with exit code 0. The cached raylib 5.5 source was used. Logs are outside the project, in `../../RewindChess-weekly-build/eight-sprints/version3`. This checks the reconstructed snapshot, not historical team activity or execution of the website backlog.

The English translation preserves the source, configuration and resource bytes; these software results still apply. Document contents, links and generated planning files are checked separately.

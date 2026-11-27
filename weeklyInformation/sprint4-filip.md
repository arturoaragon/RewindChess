# Sprint 4 report – Filip Sekulovski (documentation)

**Role:** documentation and user guide · **Sprint:** 4 (16 – 22 Nov) – History and restoration

## Backlog tasks

| Backlog task | What I did | Where |
|---|---|---|
| Document the actual classes and architecture | Documented the implemented `Square`, `Piece`, `Move`, `CastlingRights`, `Player`, `State`, and `Game` classes from `src/core/Types.cpp` and `src/core/Game.cpp`. | `docs/architecture-and-conventions.md` |
| Explain every field stored in State | Listed and explained all nine fields stored inside `State` (`board[8][8]`, `turn`, `castling`, `enPassant`, `halfmoveClock`, `fullmoveNumber`, `lastMove`, `moveText`, and `repetitionKey`). | `docs/architecture-and-conventions.md` |
| Describe snapshots and state restoration | Explained how `vector<vector<State>> timelines_` appends snapshots on valid moves and restores an independent game state by value-copying a timeline prefix without external pointers. | `docs/architecture-and-conventions.md` |

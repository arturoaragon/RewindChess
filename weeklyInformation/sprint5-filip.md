# Sprint 5 report – Filip Sekulovski (documentation)

**Role:** documentation and user guide · **Sprint:** 5 (23 – 29 Nov) – Branching rewind

## Backlog tasks

| Backlog task | What I did | Where |
|---|---|---|
| Explain free previews versus paid continuation | Documented read-only preview mode (`preview(timeline, state)`, `Back to live game`) where moves and draw claims are blocked at zero cost, versus paid branch continuation (`Continue from here` → `Use 1 rewind?`). | `docs/user-guide.md` §2 |
| Document preservation of the original timeline | Documented how `Game::rewind` copies states `0..viewedState_` into a new branch in `timelines_` while recording `parentTimelineIds_` and `forkStateIndices_`, leaving the original timeline intact. | `docs/user-guide.md` §2 |
| Describe limits, confirmation and the paying player | Documented the 5-rewind-per-player allowance (`rewindLimit() == 5`), mandatory confirmation before branching (`Use 1 rewind?` vs. `Cancel`), live-turn payer validation (`requester == live().turn`), and non-refundability of `Player` counters stored outside `State`. | `docs/user-guide.md` §2 |

## Next sprint (Sprint 6, 30 Nov – 6 Dec)

1. Explain each mode and special power (`Knight Step`, `Bishop Step`, `Pawn Strike`).
2. Document building, installation, and controls.
3. Clarify `Knight Step` and resource rules.

# Sprint 1 & 2 report – Mladen Stamatoski (QA and coordination)

**Role:** QA, coordination and demo · **Sprints:** 1 (29 Oct – 1 Nov) and 2 (2 – 8 Nov) · **Build tested:** `8e8fc0a`

## Sprint 1 – Organisation and design

| Backlog task | What I did | Where |
|---|---|---|
| Agree on ownership and weekly coordination | Ownership table (who owns which files and who reviews whom) and a weekly rhythm: issues on Monday, check-in mid-week, merge on Friday, tests and weekly reports at the weekend. | `qa/coordination.md` §1–2 |
| Prepare the task board and tracking process | GitHub Projects board (columns and fields), labels, one issue per backlog item, Definition of Done, and issue templates for bugs and sprint tasks. | `qa/coordination.md` §3–4, `.github/ISSUE_TEMPLATE/` |
| Define the review and QA process | Pull requests with one reviewer, reviewer checklist and pull request template, the QA cycle for every sprint, severity levels and rules for evidence. | `qa/qa-process.md`, `.github/pull_request_template.md` |

## Sprint 2 – Playable prototype

| Backlog task | What I did | Where |
|---|---|---|
| Test the initial position and turn switching | Engine tests TC-01 to TC-15 (32 pieces, correct squares, White first, 20 first moves, turns alternate, rejected moves change nothing, New game resets) and UI steps UI-01 to UI-05. | `qa/tests/engine_checks.cpp`, `qa/test-plan-sprint2.md` |
| Check basic movement, blocking and captures | Engine tests TC-16 to TC-40, including counting all move sequences to depth 3 (must be 20 / 400 / 8902 like in normal chess), and UI steps UI-06 to UI-15 (blocked rook, knight jump, captures, Esc, New game). | same |
| Record reproducible prototype issues | Issue log with steps to reproduce: 1 UI bug and 1 code clean-up. | `qa/issues.md` |

To make sure the tests really catch mistakes, they were also run against a temporary copy of `Rules.cpp` with two bugs added on purpose (bishops ignore blocking pieces, the turn doesn't switch). The tests then showed 13 failures. The real code was not changed.

## Results

| Check | Linux run (12 Nov, Ubuntu 24.04, g++ 13.3) | Windows run (date: ______) |
|---|---|---|
| Engine tests | 40 passed, 0 failed | ___ passed, ___ failed |
| UI checklist (15 steps) | 14 passed, 1 failed (UI-13 → BUG-01) | ___ passed, ___ failed |

## Issues found

| ID | Short description | For |
|---|---|---|
| BUG-01 | The red hint stays on screen after you select a valid piece | Samuel |
| CODE-01 | Leftover `|| false` in `App::drawBoard` | Samuel |

## Not finished

- The GitHub Projects board and labels still have to be created on GitHub (Arturo has to do the admin step).
- The ownership table needs a ✔ from every member.

## Next sprint (Sprint 3, 9 – 15 Nov)

1. Test check, checkmate and stalemate.
2. Test illegal castling and pinned en passant.
3. Verify every promotion and record failures.

# Sprint 1 & 2 report – Filip Sekulovski (documentation)

**Role:** documentation and user guide · **Sprints:** 1 (29 Oct – 1 Nov) and 2 (2 – 8 Nov)

## Sprint 1 – Organisation and design

| Backlog task | What I did | Where |
|---|---|---|
| Write the scope and acceptance criteria | What is in and out of scope (local two-player Windows game, no online play, no AI, no playing in the browser), and acceptance criteria for every sprint. | `docs/requirements.md` §1, §4 |
| Prepare the README and report outlines | Outline of the final README and of the final report, with who gives the content for each part and in which sprint. | `docs/report-outline.md` |
| Document the agreed classes and conventions | The agreed classes and what each one is responsible for, how the planned classes map to the real ones, the include chain and engine/UI separation, board coordinates (row 0 = rank 8), constants, naming rules and repository rules. | `docs/architecture-and-conventions.md` |

## Sprint 2 – Playable prototype

| Backlog task | What I did | Where |
|---|---|---|
| Finalise requirements and update the scope | Requirements version 2: game (FR-01 to FR-20), website (WR), docs and QA (DR, QR) and non-functional (NFR), each with its sprint and status. FR-01 to FR-07 are done and linked to Mladen's test IDs. Added the open questions. | `docs/requirements.md` |
| Write requirements and initial README setup steps | Added a "Website, documentation and QA" section to the README with the folders and how to run the engine tests. The README link to the backlog was broken (it pointed outside the repo), so I made a Markdown copy of the backlog and fixed the link. | `README.md`, `docs/sprint-backlogs.md` |
| Document the prototype structure and usage | What the prototype can do, window layout, controls, what happens in the code after a click, known limitations and how to check it. | `docs/prototype-guide.md` |

## Open questions for the team

- **Q1 – knight ability:** "Knight Step" (mockup) or "Knight Swap" (backlog and Week 1 report)? Needed for the user guide.
- **Q2 – plan version:** the old `.xlsx` plan (from 20 Oct) is still being shared; the current plan is the `.ods` in the repo and the backlog.
- **Q3:** are saving games and a chess clock out of scope?

## Notes

- I only described what the code really does in commit `8e8fc0a`. Things like check, castling and promotion are marked as planned.
- In the README I also removed the sentence saying the website was not done, because it is now in `website/`.

## Next sprint (Sprint 3, 9 – 15 Nov)

1. Explain castling, en passant and promotion.
2. Rule diagrams and a glossary.
3. Start the user guide.

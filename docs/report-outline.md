# README and report outlines

**Author:** Filip Sekulovski · **Sprint 1 deliverable** ("Prepare the README and report outlines")

These outlines say what the final README and the final project report will contain, who supplies each part and in which sprint. Filip writes and edits; the named owners supply facts, screenshots and evidence.

## 1. Final README outline (finished in Sprint 8)

✔ = this part already exists in the repository.

| # | Section | Content | Supplied by | Sprint |
|---|---|---|---|---|
| 1 | Title and summary | One paragraph: what RewindChess is | Filip | 2 ✔ (app team) |
| 2 | Screenshot | Final game window | Samuel / Ivan | 7 |
| 3 | Features | Standard chess, rewinds and timelines, three modes, three abilities | Filip | 6 |
| 4 | Download | Link to the GitHub Release and the website | Ivan | 8 |
| 5 | Build from source | Requirements and PowerShell steps | Samuel / Filip | 2 ✔ |
| 6 | Controls | Final controls table | Samuel / Filip | 7 |
| 7 | Repository structure | Folders and main files | Filip | 2 ✔ |
| 8 | Testing | How to run the engine checks; link to the QA folder | Mladen | 2 ✔ |
| 9 | Team and roles | Six members and responsibilities | Filip | 7 |
| 10 | Licences and credits | Pieces, font, raylib | Filip | 7 |

## 2. Final report outline (Sprint 8)

| # | Chapter | Content | Supplied by | Draft in sprint |
|---|---|---|---|---|
| 1 | Introduction | Goal, what makes RewindChess different, team | Filip | 3 |
| 2 | Requirements | Scope, functional and non-functional requirements, acceptance criteria (from `docs/requirements.md`) | Filip | 2 ✔ |
| 3 | Planning and organisation | Eight sprints, roles, weekly coordination, task board, review process | Mladen, Filip | 2 ✔ |
| 4 | Game design | Rules, modes, rewind rules, abilities, mockup | Filip, Pedro | 6 |
| 5 | Architecture | Engine/UI separation, classes, include chain, diagrams | Filip, Arturo | 4 |
| 6 | Game state and history | Fields of `State`, snapshots, `vector<vector<State>>`, restoring and branching | Filip, Pedro | 4–5 |
| 7 | User interface | Screens, controls, timeline browser, design decisions | Samuel | 7 |
| 8 | Website and publishing | Pages, GitHub Pages, DuckDNS, download area | Ivan | 4–8 |
| 9 | Testing and quality | Test plan, automated checks, manual checks, playtesting, issues found and fixed, **real** evidence only | Mladen | 2 ✔ → 8 |
| 10 | Results | What was delivered vs. the plan; known limitations | All | 8 |
| 11 | Retrospective | What went well, what we would change | All | 8 |
| A | Appendices | User guide, build guide, test results, licences | Filip, Mladen | 8 |

## 3. Writing rules

- Only describe what exists in the delivered version, and only include test results that were actually produced (each with date and environment).
- Each chapter cites the file it is based on (`docs/…`, `qa/…`, `weeklyInformation/…`).
- Screenshots come from real builds; their file name includes the sprint (`prototype-sprint2.webp`).

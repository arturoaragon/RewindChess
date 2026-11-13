# Ownership, weekly coordination and task tracking

**Author:** Mladen Stamatoski · **Sprint 1 deliverable** (tasks 1–2: "Agree on ownership and weekly coordination", "Prepare the task board and tracking process") · Status: **proposal – each member confirms by adding ✔ next to their name**

## 1. Ownership

Team leader: **Pedro Navarro Fernández**. I (Mladen) organise the task board, the weekly check-ins and QA, and report to Pedro.

Based on the team-responsibility sheet in `weeklyInformation/RewindChess_Weekly_Project_Plan.ods` and the sprint backlog.

| Member | Sub-team | Owns (files / areas) | Reviews | Confirmed |
|---|---|---|---|---|
| Arturo Aragón Bermúdez | App | `src/core/Types.cpp`, `src/core/Rules.cpp`: pieces, movement, chess rules, abilities | Pedro's engine PRs | |
| Pedro Navarro Fernández (team leader) | App | `src/core/Game.cpp`: game state, history, timelines, rewinds, modes, counters | Arturo's engine PRs | |
| Samuel Vidal Mariño | App | `src/ui/`, `src/main.cpp`, `CMakeLists.txt`, `assets/`, Windows executable | Ivan's website PRs (screenshots, controls) | |
| Ivan Yasenovskyi | Support | `website/`, hosting, download area | Samuel's UI PRs (from a user's view) | |
| Filip Sekulovski | Support | `docs/`, `README.md`, user guide, report | Mladen's QA documents | |
| Mladen Stamatoski | Support | `qa/`, `.github/`, task board, presentation and demo | Filip's documents; every sprint's integration | |

Each sprint, each member owns their three backlog items. If someone cannot finish an item, they say so at the mid-week check-in, so the item can be moved or shared, not discovered on Sunday.

## 2. Weekly rhythm

Sprints run Monday to Sunday (Sprint 3: 9–15 Nov).

| When | What | Who |
|---|---|---|
| **Monday** | Turn your 3 backlog items into GitHub issues (template "Sprint task"), assign yourself, label `sprint-N`, move them to **To do**. | Everyone |
| **Monday** | Mladen checks that all 18 items exist on the board. | Mladen |
| **Wed / Thu** | 15-minute check-in (call or group chat): done / next / blocked. Blockers are written in the issue and the person who can unblock is tagged. | Everyone |
| **Friday** | App team pushes the sprint's code (pull requests reviewed and merged). | App team |
| **Sat / Sun** | QA runs the engine checks and the UI checklist on the merged code; issues are opened. Filip updates the docs; Ivan updates the website status. | Support team |
| **Sunday** | Weekly update files written: app team `weeklyInformation/updatesweekN.md`, support team one report each, `weeklyInformation/sprintN-<name>.md`. Board cleaned (Done items closed). | Arturo / Mladen |

### Hand-offs between the two sub-teams

```text
App team merges sprint code ──► QA tests it (Mladen) ──► issues back to the app team
          │                                  │
          └──► Filip documents what changed  └──► Ivan updates the website (status, screenshots)
```

## 3. Task board

Use **GitHub Projects** (free, linked to the issues).

### Set-up (once, about 10 minutes)

1. On GitHub: **Projects → New project → Board**, name it `RewindChess sprints`.
2. Columns: **Backlog · To do · In progress · In review · Done**.
3. Add a field **Sprint** (number 1–8) and a field **Area** (Engine, UI, Website, Docs, QA).
4. Link it to the repository: in the repository, **Projects → Link a project**. (A repository admin – Arturo – may need to do this step.)
5. Create the labels below (**Issues → Labels → New label**).
6. Invite all six members to the project with write access.

### Labels

| Label | Use |
|---|---|
| `sprint-1` … `sprint-8` | Which sprint the item belongs to |
| `area: engine`, `area: ui`, `area: website`, `area: docs`, `area: qa` | Which part of the project |
| `type: task`, `type: bug` | Planned work vs. a problem found |
| `severity: critical`, `severity: major`, `severity: minor`, `severity: trivial` | Bugs only (definitions in `qa-process.md`) |
| `blocked` | Waiting for someone else |

### Tracking rules

- One issue per backlog item (6 members × 3 items = 18 per sprint), titled `S3 · Ivan · Apply responsive styling based on the mockup`.
- Bugs use the "Bug report" template and get an ID from `qa/issues.md` (`BUG-02`, …).
- A pull request that completes an item writes `Closes #<issue number>` in its description, so the issue closes when it is merged.
- An item is **Done** only when it meets the Definition of Done below.

## 4. Definition of Done

An item is done when:

1. The work is merged into `main` through a reviewed pull request.
2. For code: it builds, the engine checks pass, and new rules have new checks.
3. For website/docs: links work and the text matches the current build (no planned feature described as finished).
4. It is mentioned in that sprint's weekly update file.

## 5. Sprint 1 status

The rules above are written; the GitHub Projects board, labels and invitations need repository access and are set up by Mladen (with Arturo for admin steps) at the start of Sprint 3. Issue and pull-request templates are already in `.github/`.

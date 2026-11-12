# Review and QA process

**Author:** Mladen Stamatoski · **Sprint 1 deliverable** (task 3: "Define the review and QA process")

## 1. Code and document review

1. Work on a branch: `<name>/<sprint>-<topic>`, e.g. `pedro/s3-en-passant`.
2. Open a pull request into `main`. The template in `.github/pull_request_template.md` loads automatically.
3. **One other member reviews** (pairs in `coordination.md`). Engine changes are reviewed by the other engine developer; website and docs changes are also checked by the owner of the feature they describe, for accuracy.
4. The reviewer answers within 2 days: **Approve**, or **Request changes** with a concrete reason.
5. The **author merges** after approval. Nobody pushes directly to `main`, except the weekly update files on Sunday.

### Reviewer checklist

- [ ] The change does what its issue says, and nothing unrelated.
- [ ] Code: builds without new warnings; `qa/tests/engine_checks` passes; the engine (`src/core`) still has no raylib include.
- [ ] New rule or behaviour → new check in `engine_checks.cpp` or a new line in the UI checklist.
- [ ] Website/docs: links work; planned features are marked as planned; screenshots come from a real build.
- [ ] No build output, `.exe` files or personal files committed.

## 2. QA cycle in every sprint

| Step | When | What |
|---|---|---|
| 1. Plan | Mon – Tue | Turn the sprint's QA backlog items into test cases (`qa/test-plan-sprintN.md`), with an ID, steps and expected result for each. |
| 2. Automate | During the sprint | Add engine checks for the new rules to `qa/tests/engine_checks.cpp`. Developers may add checks too. |
| 3. Check each PR | Every PR touching `src/` | The author runs the engine checks and writes the result line in the PR (`Result: N passed, 0 failed`). |
| 4. Sprint test run | Sat – Sun | Full engine checks + UI checklist on **Windows** with the merged build. Results and screenshots go to `qa/evidence/sprintN/`. |
| 5. Report | Same day | Every failure becomes an issue with steps to reproduce (`qa/issues.md` + GitHub issue). |
| 6. Retest | After the fix is merged | Repeat the steps; close the issue with a short note and the build commit. |
| 7. Regression | Every sprint | All earlier checks are run again. Checks are never deleted, only updated when a rule deliberately changes. |

## 3. Severity

| Severity | Meaning | Kind of problem | Rule |
|---|---|---|---|
| Critical | Crash, freeze, cannot start or cannot continue the game | The program closes during a move | Fix before the sprint ends |
| Major | A chess rule or rewind/resource rule gives a wrong result | A rewind is not charged | Fix in the same or next sprint |
| Minor | Confusing or cosmetic; the game result is still correct | An old hint stays on screen (BUG-01) | Plan a fix |
| Trivial | Wording, formatting, code tidiness | Typo in a label | Fix when convenient |

## 4. Evidence rules

- Every result records the **date, build commit and environment** (OS, compiler).
- Only real results: no screenshot, log or "Pass" is written for a test that was not run.
- Screenshots and logs are stored in `qa/evidence/sprintN/` with the test ID in the file name (`UI-13-select-after-notice.webp`).
- The final report (Sprint 8) uses only this evidence.

# QA

Author: **Mladen Stamatoski**

| File | Contents |
|---|---|
| [`coordination.md`](coordination.md) | Ownership, weekly rhythm, task board, labels, Definition of Done (Sprint 1) |
| [`qa-process.md`](qa-process.md) | Review process, QA cycle, severity levels, evidence rules (Sprint 1) |
| [`test-plan-sprint2.md`](test-plan-sprint2.md) | Sprint 2 test cases and results |
| [`issues.md`](issues.md) | Prototype issues found, with steps to reproduce |
| [`tests/engine_checks.cpp`](tests/engine_checks.cpp) | Automated engine checks (no raylib needed) |
| [`evidence/sprint2/`](evidence/sprint2/) | Check output and screenshots from the Sprint 2 run |

## Run the engine checks

From the repository root, with the same MinGW-w64 `g++` used for the game:

```powershell
g++ -std=c++17 -Wall -Wextra qa/tests/engine_checks.cpp -o engine_checks.exe
.\engine_checks.exe
```

The last line must be `Result: N passed, 0 failed`. The program exits with code 1 if any check fails. Do not commit `engine_checks.exe`.

# Sprint 5 - Version update

**Planned period:** 23 - 29 Nov 2026. Adapted to eight sprints and translated into English on 6 November 2026.

## Objective

Browse positions without editing them and continue a confirmed branch, with per-player rewind limits.

## Added functionality or documentation

- Read-only browsing and confirmation before branching.
- Original timelines are retained; each player has five rewinds.

## Changes from the previous milestone

Retains the former version5. The provisional allowance is the Practice limit; all three modes arrive in sprint 6.
The existing milestone implementation is retained. Its documentation is adapted to the ODS calendar and the eight-sprint structure.


## Proposed acceptance criteria

- Browsing neither changes games nor consumes rewinds.
- Only confirmation creates a branch and charges the player whose live turn it is.
- The original timeline remains intact; time travel does not refund spent resources.

## Pending work

Only the five-rewind configuration is available. The three modes and powers arrive in version6; the complete interface is integrated in version7.

## Validation

Verified on this Windows computer on 6 November 2026: CMake Release/Ninja configuration, MinGW-w64 compilation, 99 engine checks, 19 interface checks, all resource copies, and executable startup/clean close with exit code 0. The cached raylib 5.5 source was used. Logs are outside the project, in `../../RewindChess-weekly-build/eight-sprints/version5`. This checks the reconstructed snapshot, not historical team activity or execution of the website backlog.

The English translation preserves the source, configuration and resource bytes; these software results still apply. Document contents, links and generated planning files are checked separately.

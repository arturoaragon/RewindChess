# Sprint backlogs – RewindChess (Group F)

Markdown copy of `Sprint_Backlogs_8_Weeks.pdf` (8 sprints, 29 Oct – 20 Dec 2026), added by the support team on 12 Nov 2026 so the plan can be linked and edited in the repository. If the app team has the original editable Markdown version, replace this file with it.

Sprint 1 is organisational only; implementation starts on 2 November. App team: Arturo, Pedro, Samuel. Support team: Ivan (website), Filip (documentation), Mladen (QA and coordination).

## Sprint 1 · 29 Oct – 1 Nov · Organisation and design (version1)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Design Piece, Square and the board in State.<br>2. Define movement and validation contracts.<br>3. Agree on engine dependencies with the team. |
| Pedro Navarro Fernández | 1. Design State, Move and the future history model.<br>2. Specify state copying and branches.<br>3. Agree on turn and resource rules. |
| Samuel Vidal Mariño | 1. Choose raylib and define its C++17 integration.<br>2. Design screens and the interaction flow.<br>3. Agree on folders and the engine/UI separation. |
| Ivan Yasenovskyi | 1. Define navigation: Home, How to play, About and Download.<br>2. Assign website responsibilities.<br>3. Agree on repository organization and future publishing. |
| Filip Sekulovski | 1. Write the scope and acceptance criteria.<br>2. Prepare the README and report outlines.<br>3. Document the agreed classes and conventions. |
| Mladen Stamatoski | 1. Agree on ownership and weekly coordination.<br>2. Prepare the task board and tracking process.<br>3. Define the review and QA process. |

## Sprint 2 · 2 – 8 Nov · Playable prototype (version2)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Implement pieces and the initial position.<br>2. Validate movement geometry and blocked paths.<br>3. Reject off-board destinations and friendly captures. |
| Pedro Navarro Fernández | 1. Implement Move and the current state in Game.<br>2. Alternate turns after each valid move.<br>3. Connect move application and basic captures. |
| Samuel Vidal Mariño | 1. Configure the compiler, CMake and raylib.<br>2. Draw the board and load the piece images.<br>3. Connect mouse selection to the engine. |
| Ivan Yasenovskyi | 1. Create the static structure of all four pages.<br>2. Implement navigation and shared headers.<br>3. Add the project introduction and overview. |
| Filip Sekulovski | 1. Finalize requirements and update the scope.<br>2. Write requirements and initial README setup steps.<br>3. Document the prototype structure and usage. |
| Mladen Stamatoski | 1. Test the initial position and turn switching.<br>2. Check basic movement, blocking and captures.<br>3. Record reproducible prototype issues. |

## Sprint 3 · 9 – 15 Nov · Complete standard chess (version3)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Detect check and reject moves that expose the king.<br>2. Resolve checkmate and stalemate.<br>3. Implement castling and loss of castling rights. |
| Pedro Navarro Fernández | 1. Implement en passant and its expiry.<br>2. Implement all four promotions and state clocks.<br>3. Complete notation and insufficient-material endings. |
| Samuel Vidal Mariño | 1. Connect the complete rules to mouse input.<br>2. Add a promotion picker and check status.<br>3. Block further moves after the game ends. |
| Ivan Yasenovskyi | 1. Apply responsive styling based on the mockup.<br>2. Prepare the rules and game-mode pages.<br>3. Add visual explanations of rewinding. |
| Filip Sekulovski | 1. Explain castling, en passant and promotion.<br>2. Prepare rule diagrams and a glossary.<br>3. Start the user guide. |
| Mladen Stamatoski | 1. Test check, checkmate and stalemate.<br>2. Test illegal castling and pinned en passant.<br>3. Verify every promotion and record failures. |

## Sprint 4 · 16 – 22 Nov · History and restoration (version4)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Complete State with board, turn, rights and clocks.<br>2. Generate position keys and history-dependent draw rules.<br>3. Verify that a copy preserves all state information. |
| Pedro Navarro Fernández | 1. Save snapshots after valid moves.<br>2. Organize history with vector&lt;vector&lt;State&gt;&gt;.<br>3. Restore an independent game from a saved State. |
| Samuel Vidal Mariño | 1. Show the saved-state count and latest move.<br>2. Integrate the draw-claim action.<br>3. Connect history storage without adding navigation yet. |
| Ivan Yasenovskyi | 1. Prepare the hosting configuration.<br>2. Review the planned GitHub Pages and DuckDNS flow.<br>3. Prepare future guide and download integration. |
| Filip Sekulovski | 1. Document the actual classes and architecture.<br>2. Explain every field stored in State.<br>3. Describe snapshots and state restoration. |
| Mladen Stamatoski | 1. Draft the first QA checklist.<br>2. Verify one saved state per valid move.<br>3. Test restored turns, castling, en passant and clocks. |

## Sprint 5 · 23 – 29 Nov · Branching rewind (version5)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Validate legality after state restoration.<br>2. Check the preview turn against the live turn.<br>3. Keep resource counters outside snapshots. |
| Pedro Navarro Fernández | 1. Implement read-only history previews.<br>2. Create branches by copying a prefix and preserving the original.<br>3. Allow five rewinds per player and validate who pays. |
| Samuel Vidal Mariño | 1. Add history navigation and return-to-live controls.<br>2. Confirm before continuing a branch.<br>3. Display branches and rewind counters. |
| Ivan Yasenovskyi | 1. Prepare or publish a website staging preview.<br>2. Add the rewind flow to the website pages.<br>3. Review navigation and staging links. |
| Filip Sekulovski | 1. Explain free previews versus paid continuation.<br>2. Document preservation of the original timeline.<br>3. Describe limits, confirmation and the paying player. |
| Mladen Stamatoski | 1. Test that previews cannot move or spend resources.<br>2. Check branches, copied prefixes and player limits.<br>3. Test cancellation, incorrect requesters and special states. |

## Sprint 6 · 30 Nov – 6 Dec · Modes and abilities (version6)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Implement Knight Swap, Bishop Step and Pawn Strike.<br>2. Check king safety for all three powers.<br>3. Handle swapped king/rook castling rights and pawn promotion. |
| Pedro Navarro Fernández | 1. Implement modes with limits of 5 / 1 / 1.<br>2. Manage one shared ability use per player.<br>3. Integrate resources into draws and endings without refunds. |
| Samuel Vidal Mariño | 1. Add mode selection and ability buttons.<br>2. Disable spent powers and non-editable previews.<br>3. Connect power selection, cancellation and application. |
| Ivan Yasenovskyi | 1. Update the website with modes and abilities.<br>2. Add representative game screenshots.<br>3. Prepare installation and download instructions. |
| Filip Sekulovski | 1. Explain each mode and special power.<br>2. Document building, installation and controls.<br>3. Clarify Knight Swap and resource rules. |
| Mladen Stamatoski | 1. Organize playtesting for each mode.<br>2. Test legal/illegal powers and spending only on success.<br>3. Verify that rewinding refunds neither powers nor counters. |

## Sprint 7 · 7 – 13 Dec · Final UI and release candidate (version7)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Review integration of rules and game endings.<br>2. Fix confirmed engine issues.<br>3. Review code clarity for submission. |
| Pedro Navarro Fernández | 1. Review history, branches, counters and powers together.<br>2. Fix confirmed integration issues.<br>3. Check engine compatibility with the final interface. |
| Samuel Vidal Mariño | 1. Complete menus, help, move lists and timelines.<br>2. Polish highlights, alerts, shortcuts and sharp scaling.<br>3. Prepare the Windows candidate with fonts and images. |
| Ivan Yasenovskyi | 1. Finalize responsive styling, FAQs and website credits.<br>2. Prepare the download area and candidate links.<br>3. Review navigation and accessibility. |
| Filip Sekulovski | 1. Finalize the guide, FAQ, credits and licenses.<br>2. Update the README and installation steps.<br>3. Prepare presentation content and screenshots. |
| Mladen Stamatoski | 1. Run integration tests and retest corrected issues.<br>2. Verify windows, fullscreen and resources.<br>3. Prepare and rehearse the presentation and demo. |

## Sprint 8 · 14 – 20 Dec · Final delivery (version8)

| Member | Tasks |
|---|---|
| Arturo Aragón Bermúdez | 1. Run movement and special-rule regression checks.<br>2. Review endings, edge cases and outstanding issues.<br>3. Freeze and review the final source code. |
| Pedro Navarro Fernández | 1. Run branch, resource and ability regression checks.<br>2. Verify that the delivery retains every feature.<br>3. Review the integrity of submitted states and code. |
| Samuel Vidal Mariño | 1. Build the final executable with every resource.<br>2. Verify installation and startup in a clean environment.<br>3. Prepare the tagged version and source package. |
| Ivan Yasenovskyi | 1. Publish the final website and download area.<br>2. Verify delivery links and instructions.<br>3. Check website access and downloads from another computer. |
| Filip Sekulovski | 1. Finalize the report, README and screenshots.<br>2. Add genuine test evidence and the delivery link.<br>3. Review and prepare the presentation documents. |
| Mladen Stamatoski | 1. Run final regression tests and review the evidence.<br>2. Rehearse the demo using the frozen version.<br>3. Coordinate the group review, submission and presentation. |

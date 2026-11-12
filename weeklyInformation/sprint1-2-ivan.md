# Sprint 1 & 2 report – Ivan Yasenovskyi (website)

**Role:** website and publishing · **Sprints:** 1 (29 Oct – 1 Nov) and 2 (2 – 8 Nov)

## Sprint 1 – Organisation and design

| Backlog task | What I did | Where |
|---|---|---|
| Define navigation: Home, How to play, About and Download | Site map, menu order and the purpose of each page. I also wrote down in which sprint each part of the website is done. | `docs/website-plan.md` §1 |
| Assign website responsibilities | Table of who makes the pages, who writes the texts, who gives screenshots, who reviews and who does hosting. | `docs/website-plan.md` §2 |
| Agree on repository organisation and future publishing | Folders for the website, docs and QA, and the publishing plan (GitHub Pages + DuckDNS, download from GitHub Releases). | `docs/website-plan.md` §3–4 |

## Sprint 2 – Playable prototype

| Backlog task | What I did | Where |
|---|---|---|
| Create the static structure of all four pages | `index.html`, `how-to-play.html`, `about.html`, `download.html` with their sections. Pages whose content comes in later sprints have placeholders. | `website/` |
| Implement navigation and shared headers | `site.js` draws the same header with the menu and the same footer on every page from one list, and marks the current page. There is a plain `<noscript>` menu in case JavaScript is off. | `website/js/site.js` |
| Add the project introduction and overview | Home page: short introduction and an overview of the main features (chess for two players, rewinds and timelines, three modes, special abilities). | `website/index.html` |

The styling is only a basic layout (`website/css/style.css`). The styling from the mockup is the Sprint 3 task.

## Decisions

- The mockup has a "Play" button, but our game is a Windows program, so the menu item is "Download".

## How to check

Open `website/index.html` in a browser and click through the menu: all four pages open and the current page is shown in bold.

## Next sprint (Sprint 3, 9 – 15 Nov)

1. Apply responsive styling based on the mockup.
2. Prepare the rules and game-mode pages.
3. Add visual explanations of rewinding.

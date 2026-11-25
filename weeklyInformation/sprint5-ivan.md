# Sprint 5 report – Ivan Yasenovskyi (website)

**Role:** website and publishing · **Sprint:** 5 (23 – 29 Nov) – Branching rewind

## Backlog tasks

| Backlog task | What I did | Where |
|---|---|---|
| Prepare or publish a website staging preview | Prepared the staging preview on GitHub Pages: the `website/` folder is published to the `gh-pages` branch with the commands from Sprint 4. Staging address: `https://arturoaragon.github.io/RewindChess/` (online after Arturo chooses `gh-pages` in Settings → Pages). | `docs/website-hosting.md` §4, `website/README.md` |
| Add the rewind flow to the website pages | New "The rewind flow, step by step" on How to play: Live game → View mode → Confirm → New timeline, plus what happens if you cancel, have no rewinds left, and who pays. I used the same button names as in our game version 5 ("Continue from here", "Use rewind", "Cancel", "Back to live"), and changed the "Looking is free" card so it matches how browsing works in the game. On phones the steps are in one column with arrows between them. | `website/how-to-play.html`, `website/css/style.css` |
| Review navigation and staging links | Served the site locally under `/RewindChess/`, the same path as on GitHub Pages, and opened all pages on desktop and phone width: every page loads with styles, header and footer, the menu marks the current page, and all links and anchors work. Found one 404 (the browser asking for `/favicon.ico`) and fixed it. | `docs/website-hosting.md` §4 |

## Staging checklist

- [+] Arturo set **Settings → Pages → Deploy from a branch → `gh-pages` / root**
- [+] Site opens at `https://arturoaragon.github.io/RewindChess/`
- [+] Link check repeated on the real address (list in `docs/website-hosting.md` §4)

## Next sprint (Sprint 6, 30 Nov – 6 Dec)

1. Update the website with modes and abilities.
2. Add representative game screenshots.
3. Prepare installation and download instructions.

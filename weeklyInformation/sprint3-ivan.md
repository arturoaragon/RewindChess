# Sprint 3 report – Ivan Yasenovskyi (website)

**Role:** website and publishing · **Sprint:** 3 (9 – 15 Nov) – Complete standard chess

## Backlog tasks

| Backlog task | What I did | Where |
|---|---|---|
| Apply responsive styling based on the mockup | Colours, header with the yellow Download button, hero, cards, table and footer like in the mockup. Phone layout (under 720 px): menu goes under the logo, cards are in one column and the modes table turns into one card per mode. Tablet (under 960 px): hero in one column, cards in two columns. | `website/css/style.css`, `website/js/site.js` |
| Prepare the rules and game-mode pages | Home: the three game modes. How to play: modes table (rewinds and special moves per player, what each mode is for) and the three rewind rules (looking is free, playing on costs one rewind, no refunds). The intro says that the normal chess rules are used. | `website/index.html`, `website/how-to-play.html` |
| Add visual explanations of rewinding | 1) "Your game history" box on Home: rewind to move 3 opens Timeline 1. 2) "How a rewind works" in three steps on Home. 3) Branch picture on How to play: Timeline 0 with moves 1–5, "Continue from here = 1 rewind" at move 3, Timeline 1 with copied moves 1–3 and new moves 4–5. On phones the picture is vertical so the text is still readable. | `website/index.html`, `website/how-to-play.html` |

## Decisions

- Rules and game modes are on the How to play page (like in the mockup), so the menu stays Home · How to play · About · Download.
- I used system fonts instead of adding font files, so the site has no extra files and no font licence to include.
- The branch picture is drawn in SVG directly in the page, so it is sharp on every screen and needs no image files.

## Testing

- Opened all four pages in Chrome at desktop (1280 px) and phone (390 px) width: layout works and there are no errors in the console.
- All links between the pages work, including "Compare the modes" and "All rewind rules" on Home.

## Left for later sprints (from the backlog)

- Special abilities and screenshots – Sprint 6.
- Controls, download area, FAQ and credits – Sprints 6–7.
- Hosting on GitHub Pages and DuckDNS – Sprint 4.

## Next sprint (Sprint 4, 16 – 22 Nov)

1. Prepare the hosting configuration.
2. Review the planned GitHub Pages and DuckDNS flow.
3. Prepare future guide and download integration.

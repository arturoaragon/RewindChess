# Website plan

**Author:** Ivan Yasenovskyi · **Sprint 1** (29 Oct – 1 Nov 2026)

Sprint 1 website tasks:

1. Define navigation: Home, How to play, About and Download.
2. Assign website responsibilities.
3. Agree on repository organisation and future publishing.

## 1. Navigation

The website is informational and for downloads only. The game is a Windows program and is not played in the browser.

```text
Home ──┬── How to play
       ├── About
       └── Download
```

Menu order: **Home · How to play · About · Download**. The mockup has a "Play" button in this place; on our site it is "Download", because the game cannot be played in the browser.

| Page | File | Purpose |
|---|---|---|
| Home | `index.html` | What RewindChess is: introduction and overview |
| How to play | `how-to-play.html` | Game modes, rewind rules, special abilities, controls |
| About | `about.html` | The project and the team |
| Download | `download.html` | Download of the Windows game |

### When each part is done (from the sprint backlog)

| Sprint | Website work |
|---|---|
| 2 | Structure of the four pages, menu and shared header, introduction and overview |
| 3 | Styling from the mockup, rules and game-mode content, visual explanation of rewinding |
| 4 | Hosting configuration, GitHub Pages and DuckDNS flow |
| 5 | Staging preview, rewind flow on the pages |
| 6 | Modes and abilities, screenshots, installation and download instructions |
| 7 | Final styling, FAQ, credits, download area |
| 8 | Publish the final website and check it from another computer |

## 2. Responsibilities

| Task | Responsible | Helps | Reviews |
|---|---|---|---|
| Pages, menu, styling | Ivan | – | Mladen |
| Texts for the pages (rules, modes, guide) | Filip | Ivan | Mladen |
| Screenshots of the game | Ivan | Samuel (builds) | Filip |
| Correct rules and ability descriptions | Arturo, Pedro | Filip | Mladen |
| Checking links and pages | Mladen | Ivan | – |
| Hosting (GitHub Pages, DuckDNS) | Ivan | Arturo (repository settings) | Mladen |
| Download area | Ivan | Samuel (release files) | Mladen |

## 3. Repository organisation

```text
RewindChess/
├── src/, assets/, CMakeLists.txt    game (app team)
├── website/                         website (Ivan)
├── docs/                            documentation (Filip)
├── qa/                              tests and QA (Mladen)
└── weeklyInformation/               weekly reports
```

The website only uses files inside `website/`, so the folder can be published on its own.

## 4. Future publishing

- The website will be published with **GitHub Pages** and get an address with **DuckDNS**. The exact configuration is prepared in Sprint 4.
- The game download will link to a **GitHub Release** (Sprints 7–8).

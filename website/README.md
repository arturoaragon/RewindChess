# RewindChess website

Author: **Ivan Yasenovskyi**

Static website for RewindChess (plain HTML, CSS and JavaScript). The game itself is a Windows program; the website explains it and will have the download.

The plan for the website is in [`docs/website-plan.md`](../docs/website-plan.md).

## Pages

| File | Page |
|---|---|
| `index.html` | Home: introduction, history picture, game modes, how a rewind works |
| `how-to-play.html` | Game modes table, rewind rules with the branch picture; abilities and controls come later |
| `about.html` | About: project and team |
| `download.html` | Download (placeholder) |

## Structure

```text
website/
├── index.html, how-to-play.html, about.html, download.html
├── css/style.css     styles from the mockup + phone layout
└── js/site.js        shared header (menu) and footer
```

Every page has an empty `<header id="site-header">` and `<footer id="site-footer">`. `js/site.js` fills them from one list (`PAGES`), so the menu is changed in one place. To add a page: copy a page, change the title and `data-page`, add it to `PAGES` and to the `<noscript>` menu.

## Styles

- Colours are taken from the mockup and kept as variables at the top of `css/style.css`.
- For amber text on the light background use `--amber-text` (the button amber is too light for text).
- Phone layout is in the `@media (max-width: 720px)` block at the end: menu under the logo, cards in one column, the modes table becomes one card per mode, and the branch picture on How to play switches to the vertical version.

## Publishing

Staging preview: **https://arturoaragon.github.io/RewindChess/**

The site is published with GitHub Pages from the `gh-pages` branch. How it works and the commands are in [`docs/website-hosting.md`](../docs/website-hosting.md).

## Open it

Double-click `website/index.html`. It works without a server.

# RewindChess website

Author: **Ivan Yasenovskyi**

Static website for RewindChess (plain HTML, CSS and JavaScript). The game itself is a Windows program; the website explains it and will have the download.

The plan for the website is in [`docs/website-plan.md`](../docs/website-plan.md).

## Pages

| File | Page |
|---|---|
| `index.html` | Home: introduction and overview |
| `how-to-play.html` | How to play (sections only, content comes later) |
| `about.html` | About: project and team |
| `download.html` | Download (placeholder) |

## Structure

```text
website/
├── index.html, how-to-play.html, about.html, download.html
├── css/style.css     basic layout
└── js/site.js        shared header (menu) and footer
```

Every page has an empty `<header id="site-header">` and `<footer id="site-footer">`. `js/site.js` fills them from one list (`PAGES`), so the menu is changed in one place. To add a page: copy a page, change the title and `data-page`, add it to `PAGES` and to the `<noscript>` menu.

## Open it

Double-click `website/index.html`. It works without a server.

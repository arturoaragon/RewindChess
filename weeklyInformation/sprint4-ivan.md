# Sprint 4 report – Ivan Yasenovskyi (website)

**Role:** website and publishing · **Sprint:** 4 (16 – 22 Nov) – History and restoration

## Backlog tasks

| Backlog task | What I did | Where |
|---|---|---|
| Prepare the hosting configuration | Chose GitHub Pages with **Deploy from a branch**: the `gh-pages` branch gets only the files of `website/`. Wrote the commands to publish and update it, the one-time Pages settings for Arturo, and added `website/.nojekyll` so GitHub Pages serves the files as they are. Tested the publish commands on a copy of the repository: the `gh-pages` branch had the website files at its root. | `docs/website-hosting.md` §1, `website/.nojekyll` |
| Review the planned GitHub Pages and DuckDNS flow | Checked each step of the plan with the GitHub Pages and DuckDNS documentation. Found that Pages cannot publish the `website/` folder directly, that only admins can change the settings, that DuckDNS has no CNAME records (so the name must point to a GitHub Pages IP), and that a custom domain needs a `CNAME` file that our updates must keep. Decision: staging on the `github.io` address, DuckDNS name for the final website. | `docs/website-hosting.md` §2 |
| Prepare future guide and download integration | Planned where the `.exe` (GitHub Release, link to `releases/latest`), the installation steps and the controls (Filip's user guide) will go. Prepared the sections on the pages: "Windows download" and "Installation" on Download, and the controls section on How to play. | `docs/website-hosting.md` §3, `website/download.html`, `website/how-to-play.html` |

## Decisions

- Publishing from a `gh-pages` branch only needs Git and GitHub Pages, which are already in our tool list.
- The game `.exe` will not be stored in the website; the Download button will link to the latest GitHub Release.

## Needed from the team

- Arturo: set **Settings → Pages → Deploy from a branch → `gh-pages` / root** once (only admins can do it).

## Next sprint (Sprint 5, 23 – 29 Nov)

1. Prepare or publish a website staging preview.
2. Add the rewind flow to the website pages.
3. Review navigation and staging links.

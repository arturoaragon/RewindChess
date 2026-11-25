# Website hosting

**Author:** Ivan Yasenovskyi · **Sprint 4** (16 – 22 Nov 2026)

Sprint 4 website tasks:

1. Prepare the hosting configuration.
2. Review the planned GitHub Pages and DuckDNS flow.
3. Prepare future guide and download integration.

## 1. Hosting configuration

| Setting | Value |
|---|---|
| Hosting | GitHub Pages of `arturoaragon/RewindChess` |
| Source | **Deploy from a branch** → branch `gh-pages`, folder `/ (root)` |
| What is in `gh-pages` | Only the files of `website/` (made from `main`, see the commands below) |
| Address | `https://arturoaragon.github.io/RewindChess/` |
| `website/.nojekyll` | Empty file. GitHub Pages then serves our files as they are, without running Jekyll on them. |

Why a separate `gh-pages` branch: GitHub Pages can only publish the root of a branch or a `/docs` folder. Our website is in `website/` and `docs/` is used for documentation, so the website files are copied to the root of their own branch. This only needs Git and GitHub Pages, no extra tools.

All links and files in the website are relative (`css/style.css`, `how-to-play.html`), so the site also works under `/RewindChess/` and not only at the root of a domain.

### Who does what

| Step | Who | How often |
|---|---|---|
| Choose `gh-pages` as the Pages source | Arturo (only repository admins can change Pages settings) | Once |
| Publish or update the website | Ivan | After each website change that should go online |

### Publishing or updating (PowerShell, in the `RewindChess` folder)

```powershell
git checkout main
git pull
git subtree split --prefix website -b gh-pages-tmp
git push origin gh-pages-tmp:gh-pages --force
git branch -D gh-pages-tmp
```

- `git subtree split --prefix website` makes a temporary branch whose root is the `website/` folder.
- `git push ... gh-pages --force` replaces the `gh-pages` branch on GitHub with it. `--force` is only used for `gh-pages`, which nobody edits by hand. `main` is never force-pushed.
- GitHub Pages updates the site about a minute later.

### One-time settings (Arturo)

1. Repository → **Settings** → **Pages**.
2. **Build and deployment** → Source: **Deploy from a branch**.
3. Branch: **gh-pages**, folder: **/ (root)** → **Save**.

The `gh-pages` branch has to exist first, so Ivan publishes once before Arturo does this.

## 2. Review of the GitHub Pages + DuckDNS flow

| Planned step | What I found | Decision |
|---|---|---|
| Publish the `website/` folder with GitHub Pages | Pages can publish any branch, but only its root or its `/docs` folder. | Publish from the `gh-pages` branch (section 1). |
| Turn Pages on | Only people with admin permissions can configure Pages and a custom domain. | Arturo does the settings once. |
| Give the site a DuckDNS name | DuckDNS only stores an IPv4/IPv6 address (and one TXT record) for a name; it has no CNAME records, which GitHub suggests for subdomains. A single A record pointing to one of the GitHub Pages IP addresses can also work. | In DuckDNS set the IP of `<name>.duckdns.org` to `185.199.108.153` (GitHub Pages), then type `<name>.duckdns.org` as the custom domain in Settings → Pages. |
| Keep the custom domain after updates | With branch publishing, saving a custom domain adds a `CNAME` file to the root of the source branch. Our update replaces `gh-pages`, so that file would be lost. | When the name is chosen, also add `website/CNAME` (one line: the domain) in `main`, so it is always published. |
| HTTPS | GitHub can create the HTTPS certificate only after the domain points correctly to GitHub Pages. This has to be checked when it is set up. | If DuckDNS does not get HTTPS or does not work, we keep the `github.io` address, which always has HTTPS. |

**Result:** the staging preview (Sprint 5) uses the `github.io` address. The DuckDNS name is added when the final website is published (Sprint 8), with the `github.io` address as a fallback.

## 3. Guide and download integration

| Content | Comes from | Goes to | Sprint |
|---|---|---|---|
| Windows game (`.exe`) | Samuel: GitHub Release of the repository | Download page, "Windows download": a button that links to `https://github.com/arturoaragon/RewindChess/releases/latest` | 7 – 8 |
| Installation steps | Filip: user guide | Download page, "Installation" | 6 |
| Controls | Filip: user guide | How to play, "4. Controls": short list + link to the full guide | 6 – 7 |

- The `.exe` is **not** stored in the website or the repository. The button links to the latest release, so a new version does not need a website change.
- The full user guide stays in `docs/` (Filip). The website shows only the short version and links to the guide, so the text is written once.
- The sections are already prepared on the pages (`download.html#windows`, `download.html#install`, `how-to-play.html` section 4), so the content can be dropped in later.

## 4. Staging preview (Sprint 5)

Staging address: **https://arturoaragon.github.io/RewindChess/**

1. Ivan publishes `website/` to the `gh-pages` branch with the commands in section 1.
2. Arturo chooses `gh-pages` / root in Settings → Pages (once).
3. The team opens the address and checks the site before it is final. Every later website change is published with the same commands.

### Navigation and link check

Before publishing, the site was served locally under the same path as GitHub Pages (`/RewindChess/`) and every page was opened at desktop (1280 px) and phone (390 px) width.

| Check | Result |
|---|---|
| `/RewindChess/` opens the Home page | OK |
| All 4 pages load, with styles and the shared header and footer | OK |
| Current page is marked in the menu on every page | OK |
| All links between the pages and the anchors (`#modes`, `#rewind`) work | OK, 6 link targets checked |
| Errors in the browser console | One 404: the browser asked for `/favicon.ico`. Fixed with `<link rel="icon" href="data:,">` in every page; checked again, no errors. |

After the site is online, the same check is done once on the real address:

- [ ] `https://arturoaragon.github.io/RewindChess/` opens Home
- [ ] Menu works on all 4 pages
- [ ] "Compare the modes" and "All rewind rules" open the right part of How to play
- [ ] Phone view checked on a real phone

## Sources

- GitHub Docs – [Configuring a publishing source for your GitHub Pages site](https://docs.github.com/en/pages/getting-started-with-github-pages/configuring-a-publishing-source-for-your-github-pages-site)
- GitHub Docs – [Managing a custom domain for your GitHub Pages site](https://docs.github.com/en/pages/configuring-a-custom-domain-for-your-github-pages-site/managing-a-custom-domain-for-your-github-pages-site)
- Duck DNS – [spec](https://www.duckdns.org/spec.jsp)

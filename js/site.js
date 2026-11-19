// Header + footer for every page.
// Each page only has an empty <header id="site-header"> and <footer id="site-footer">,
// this script fills them, so the menu is changed in one place only.
// I didn't use fetch() for this because it doesn't work when you open the html file directly.
(function () {
  "use strict";

  // menu items (same order as in the mockup, "Play" is Download for us)
  // cta = drawn as the yellow button on the right
  var PAGES = [
    { id: "home", label: "Home", href: "index.html" },
    { id: "how-to-play", label: "How to play", href: "how-to-play.html" },
    { id: "about", label: "About", href: "about.html" },
    { id: "download", label: "Download", href: "download.html", cta: true }
  ];

  // footer team line like in the mockup
  var TEAM = [
    "Pedro Navarro Fernández",
    "Arturo Aragón Bermúdez",
    "Samuel Vidal Mariño",
    "Ivan Yasenovskyi",
    "Filip Sekulovski",
    "Mladen Stamatoski"
  ];

  function buildHeader(current) {
    var items = PAGES.map(function (page) {
      var cls = page.cta ? ' class="nav-cta"' : "";
      var currentAttr = page.id === current ? ' aria-current="page"' : "";
      return '<li><a href="' + page.href + '"' + cls + currentAttr + ">" + page.label + "</a></li>";
    }).join("");

    return (
      '<div class="container">' +
      '<a class="logo" href="index.html">Rewind<span>Chess</span></a>' +
      '<nav class="site-nav" aria-label="Main"><ul>' + items + "</ul></nav>" +
      "</div>"
    );
  }

  function buildFooter() {
    return (
      '<div class="container">' +
      '<p class="footer-name">RewindChess</p>' +
      "<p>Software Engineering team project · Group F · Oct – Dec 2026</p>" +
      "<p>Team: " + TEAM.join(", ") + "</p>" +
      "</div>"
    );
  }

  function render() {
    var current = document.body.getAttribute("data-page") || "";
    var header = document.getElementById("site-header");
    var footer = document.getElementById("site-footer");

    if (header) {
      header.className = "site-header";
      header.innerHTML = buildHeader(current);
    }
    if (footer) {
      footer.className = "site-footer";
      footer.innerHTML = buildFooter();
    }
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", render);
  } else {
    render();
  }
})();

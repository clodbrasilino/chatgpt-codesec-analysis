"""Build docs/architecture.html from docs/architecture.md with figures inlined."""
import re
from pathlib import Path

import markdown

DOCS = Path(__file__).resolve().parent
md_text = (DOCS / "architecture.md").read_text()

body = markdown.markdown(
    md_text,
    extensions=["tables", "fenced_code", "toc", "sane_lists"],
    extension_configs={"toc": {"title": "Contents"}},
)

# Inline the three SVG figures (replace <img src="figures/x.svg" ...> with raw SVG).
def _inline(m: re.Match) -> str:
    src = m.group("src")
    svg = (DOCS / src).read_text()
    alt = m.group("alt")
    return (
        f'<figure class="fig">{svg}'
        f'<figcaption>{alt}</figcaption></figure>'
    )

body = re.sub(
    r'<img[^>]*alt="(?P<alt>[^"]*)"[^>]*src="(?P<src>figures/[^"]+)"[^>]*/?>',
    _inline,
    body,
)
body = re.sub(
    r'<img[^>]*src="(?P<src>figures/[^"]+)"[^>]*alt="(?P<alt>[^"]*)"[^>]*/?>',
    _inline,
    body,
)
assert "<img" not in body, "unresolved image reference"

html = f"""<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="utf-8">
<title>Experiment Pipeline Architecture — FSE 2027 Extension</title>
<style>
  body {{ max-width: 980px; margin: 2rem auto; padding: 0 1.5rem;
         font: 16px/1.65 -apple-system, "Helvetica Neue", Arial, sans-serif;
         color: #1f2937; background: #ffffff; }}
  h1 {{ font-size: 1.9rem; border-bottom: 3px solid #4f46e5; padding-bottom: .4rem; }}
  h2 {{ font-size: 1.35rem; margin-top: 2.2rem; border-bottom: 1px solid #e5e7eb;
       padding-bottom: .25rem; }}
  h3 {{ font-size: 1.1rem; margin-top: 1.6rem; }}
  code {{ font: .88em/1.5 "SF Mono", Menlo, Consolas, monospace;
         background: #f1f5f9; padding: .1em .35em; border-radius: 4px; }}
  pre {{ background: #0f172a; color: #e2e8f0; padding: 1rem 1.2rem;
        border-radius: 8px; overflow-x: auto; }}
  pre code {{ background: none; padding: 0; }}
  table {{ border-collapse: collapse; margin: 1rem 0; width: 100%; font-size: .92rem; }}
  th, td {{ border: 1px solid #e2e8f0; padding: .45rem .65rem; text-align: left; }}
  th {{ background: #f8fafc; }}
  tr:nth-child(even) td {{ background: #fbfcfe; }}
  .fig {{ margin: 1.8rem 0; }}
  .fig svg {{ width: 100%; height: auto; border: 1px solid #e5e7eb;
             border-radius: 8px; }}
  figcaption {{ text-align: center; font-size: .85rem; color: #64748b;
               margin-top: .4rem; }}
  blockquote {{ border-left: 4px solid #c7d2fe; margin: 1rem 0;
               padding: .3rem 1rem; color: #475569; background: #f8fafc; }}
  a {{ color: #4f46e5; }}
  hr {{ border: none; border-top: 1px solid #e5e7eb; margin: 2rem 0; }}
</style>
</head>
<body>
{body}
</body>
</html>
"""
(DOCS / "architecture.html").write_text(html)
print("wrote", DOCS / "architecture.html", len(html), "bytes")

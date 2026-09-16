"""Full data-collection progress report (channel-level audit).

Walks collected_code_6 + results manifests and produces an HTML report:
  1. heal_0 per model: generated coverage, clean, static/dynamic/test-failure
     detection (channel classification replicates comment_inject.py exactly).
  2. Healing-round funnels per cell: entered / cleaned / remaining / heal_failed
     + channel mix of the files entering each round.
  3. Ablation status: thinking vs non-thinking, temperature / top_p cells.
  4. s/d/s+d 3-arm comparison per model: problem-level detection sets at
     heal_0, per-arm outcomes (clean at start, healed per round, remainders),
     full per-problem appendix.

Output: results/collection_report.html
"""
from __future__ import annotations

import csv
import html as html_mod
import json
import re
import time
from collections import Counter, defaultdict
from datetime import datetime
from pathlib import Path

import sys
sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from src.pipeline import comment_inject as ci  # noqa: E402

REPO = Path(__file__).resolve().parents[2]
CC = REPO / "collected_code_6"
RESULTS = REPO / "results"
OUT = RESULTS / "collection_report.html"

EXPECTED_FULL = 974 * 3          # 2,922
EXPECTED_SUBSET = 200 * 3        # 600

_BASE_RE = re.compile(r"^problem-(\d+)(?:-s([2-9]))?$")


def load_subset() -> list[int]:
    with open(RESULTS / "vulnerable_subset.csv") as f:
        rows = list(csv.DictReader(f))
    return [int(r["problem_id"]) for r in rows[:200]]


def load_manifest(model: str, slug: str) -> dict | None:
    p = RESULTS / model / f"{slug}.manifest.json"
    if not p.is_file():
        return None
    try:
        return json.loads(p.read_text())
    except Exception:
        return None


def outcome_counts(man: dict | None, pids: set[int] | None = None) -> dict:
    """Counter of outcomes, optionally restricted to subset pids."""
    c: Counter = Counter()
    if not man:
        return dict(c)
    for key, rec in man["outcomes"].items():
        if pids is not None:
            m = re.match(r"problem-(\d+)", key)
            if not m or int(m.group(1)) not in pids:
                continue
        c[rec["outcome"] if isinstance(rec, dict) else rec] += 1
    return dict(c)


def rtc_histogram(man: dict | None, pids: set[int] | None = None) -> dict[int, int]:
    """rounds_to_clean histogram over outcome == clean."""
    h: Counter = Counter()
    if not man:
        return dict(h)
    for key, rec in man["outcomes"].items():
        if pids is not None:
            m = re.match(r"problem-(\d+)", key)
            if not m or int(m.group(1)) not in pids:
                continue
        if isinstance(rec, dict) and rec.get("outcome") == "clean":
            h[rec.get("rounds_to_clean", 0)] += 1
    return dict(h)


# ---------------------------------------------------------------- findings --
_find_cache: dict[tuple[str, str], tuple[bool, bool, bool]] = {}


def channel_flags(dirpath: Path, base: str) -> tuple[bool, bool, bool]:
    """(has_static, has_asan, has_test) using the pipeline's own parsers."""
    key = (str(dirpath), base)
    if key in _find_cache:
        return _find_cache[key]
    has_s = False
    for suf in ci.STATIC_SUFFIXES:
        p = dirpath / (base + suf)
        if p.is_file():
            txt = p.read_text(errors="replace")
            if any(m["line"] > 0 for m in ci.extract_standard_messages(txt)):
                has_s = True
                break
    has_a = has_t = False
    for suf, flag in ((".asan.txt", "a"), (".fuzz.txt", "a"), (".test.txt", "t")):
        p = dirpath / (base + suf)
        if p.is_file():
            txt = p.read_text(errors="replace")
            if any(m["line"] > 0 for m in ci.extract_standard_messages(txt)):
                if flag == "a":
                    has_a = True
                else:
                    has_t = True
    res = (has_s, has_a, has_t)
    _find_cache[key] = res
    return res


def bases_in(d: Path) -> list[str]:
    if not d.is_dir():
        return []
    return sorted(p.name[:-2] for p in d.iterdir()
                  if p.name.endswith(".c") and _BASE_RE.match(p.name[:-2]))


# A compile error line in a gcc report (file:line:col: error: ...). Compile
# errors are the LLM's healing feedback for non-compilable code (static
# channel); non-compilability itself is an experiment outcome.
_NONCOMP_RE = re.compile(r":\d+:\d+:\s*error:")


def non_compilable(heal0: Path, base: str, model: str) -> bool:
    """Sample failed the compile gate (never executed by the dyn oracle).

    Primary: local gcc report contains a compile error. Fallbacks: the dyn
    'not compilable' marker (.test.txt), the old-format 'could not compile'
    message, or the static sibling cell's gcc report (dynamic-only cells
    share round-0 code with the RQ1 static sweep).
    """
    gcc = heal0 / (base + ".gcc.txt")
    if gcc.is_file():
        return bool(_NONCOMP_RE.search(gcc.read_text(errors="replace")))
    t = heal0 / (base + ".test.txt")
    if t.is_file():
        txt = t.read_text(errors="replace")
        if "not compilable" in txt or "could not compile under sanitizers" in txt:
            return True
    sib = CC / model / "feedback-static-r0-t1.0-p1.0" / "heal_0" / (base + ".gcc.txt")
    if sib.is_file():
        return bool(_NONCOMP_RE.search(sib.read_text(errors="replace")))
    return False


def pid_of(base: str) -> int:
    return int(_BASE_RE.match(base).group(1))


# ------------------------------------------------------------------- cells --
SLUG_RE = re.compile(
    r"^feedback-(static\+dynamic|static|dynamic)-r([01])-t([\d.]+)-p([\d.]+)$")


def discover_cells() -> list[dict]:
    cells = []
    for model_dir in sorted(CC.iterdir()):
        if not model_dir.is_dir():
            continue
        for cell_dir in sorted(model_dir.iterdir()):
            m = SLUG_RE.match(cell_dir.name)
            if m and (cell_dir / "heal_0").is_dir():
                cells.append({
                    "model": model_dir.name,
                    "dir": cell_dir,
                    "feedback": m.group(1),
                    "reasoning": m.group(2) == "1",
                    "temp": m.group(3),
                    "top_p": m.group(4),
                    "slug": cell_dir.name,
                })
    return cells


def analyze_cell(cell: dict) -> dict:
    """Full per-cell statistics: heal_0, funnel, channels."""
    root = cell["dir"]
    heal0 = root / "heal_0"
    cfiles = bases_in(heal0)
    problems: Counter = Counter(pid_of(b) for b in cfiles)

    fb = cell["feedback"]
    flags = {b: channel_flags(heal0, b) for b in cfiles}

    # Analysis-complete basis: files whose reports for the cell's gate exist.
    # In-flight cells (heal_0 analysis still running) only count files that
    # have actually been analyzed — missing reports never count as clean.
    if "dynamic" in fb:
        an_bases = {b for b in cfiles if (heal0 / (b + ".test.txt")).is_file()}
    else:
        an_bases = {b for b in cfiles if (heal0 / (b + ".gcc.txt")).is_file()}
    n_an = len(an_bases)

    def flagged_by_feedback(b: str) -> bool:
        s, a, t = flags[b]
        if fb == "static":
            return s
        if fb == "dynamic":
            return a or t
        return s or a or t

    flagged0 = {b for b in an_bases if flagged_by_feedback(b)}
    clean0 = an_bases - flagged0
    noncomp0 = {b for b in an_bases if non_compilable(heal0, b, cell["model"])}

    analyzed = n_an

    # channel mix on heal_0 (only meaningful where the channel was measured)
    mix0 = Counter()
    for b in an_bases:
        s, a, t = flags[b]
        key = (("S" if s else "-") + ("A" if a else "-") + ("T" if t else "-"))
        mix0[key] += 1

    # ---- funnel ----
    rounds = []
    max_round = 10
    for n in range(1, max_round + 2):
        tbe = root / f"heal_{n}" / "to_be_healed"
        if not tbe.is_dir():
            break
        flagged = set(bases_in(tbe))
        if not flagged:
            rounds.append({"round": n, "entered": 0, "state": "converged"})
            break
        src = heal0 if n == 1 else root / f"heal_{n-1}" / "healed"
        healed_dir = root / f"heal_{n}" / "healed"
        healed_c = set(bases_in(healed_dir)) if healed_dir.is_dir() else set()
        nxt = root / f"heal_{n+1}" / "to_be_healed"
        next_flagged = set(bases_in(nxt)) if nxt.is_dir() else None

        mix = Counter()
        for b in flagged:
            s, a, t = channel_flags(src, b)
            mix[(("S" if s else "-") + ("A" if a else "-") + ("T" if t else "-"))] += 1

        rec = {
            "round": n, "entered": len(flagged),
            "healed_present": len(healed_c),
            "mix": dict(mix), "state": "in-progress",
        }
        if next_flagged is not None:
            remaining = flagged & next_flagged
            gone = flagged - next_flagged
            cleaned = {b for b in gone if b in healed_c}
            failed = gone - cleaned
            rec.update({
                "state": "done",
                "cleaned": len(cleaned),
                "remaining": len(remaining),
                "heal_failed": len(failed),
            })
        elif healed_dir.is_dir() and len(healed_c) >= len(flagged):
            # all healed artifacts written but verification pass not yet run
            rec["state"] = "awaiting-verification"
        rounds.append(rec)
        if nxt.is_dir() and not next_flagged and (root / f"heal_{n+1}").is_dir():
            break

    manifest = load_manifest(cell["model"], cell["slug"])
    man_out = outcome_counts(manifest)
    valid_manifest = manifest is not None and len(manifest["outcomes"]) >= 100

    # Outcome of samples that were non-compilable at heal_0: did the LLM
    # heal the compile errors (via static-channel feedback)?
    nc_out: Counter = Counter()
    if manifest:
        for b in noncomp0:
            rec = manifest["outcomes"].get(b)
            if rec:
                nc_out[rec["outcome"]] += 1
            else:
                nc_out["pending"] += 1

    return {
        **cell, "n_c": len(cfiles), "n_an": n_an, "n_problems": len(problems),
        "samples_per_problem": Counter(problems.values()),
        "analyzed": analyzed, "flagged0": len(flagged0), "clean0": len(clean0),
        "noncomp0": len(noncomp0), "nc_out": dict(nc_out),
        "mix0": dict(mix0), "rounds": rounds, "an_bases": an_bases,
        "manifest": manifest, "man_out": man_out, "valid_manifest": valid_manifest,
        "rtc": rtc_histogram(manifest),
        "flags0": flags,
    }


# ------------------------------------------------------------------- HTML ---
CSS = """
:root { color-scheme: light; }
body { font-family: -apple-system, 'Helvetica Neue', Arial, sans-serif; margin: 0;
       background: #f5f6f8; color: #1c1e21; }
.wrap { max-width: 1180px; margin: 0 auto; padding: 24px 20px 60px; }
h1 { font-size: 26px; margin: 8px 0 2px; }
h2 { font-size: 20px; margin: 34px 0 10px; border-bottom: 2px solid #dfe3e8;
     padding-bottom: 6px; }
h3 { font-size: 16px; margin: 20px 0 8px; }
p.note { color: #555; font-size: 13.5px; line-height: 1.5; margin: 6px 0; }
.meta { color: #777; font-size: 13px; }
table { border-collapse: collapse; width: 100%; font-size: 13px;
        background: #fff; margin: 10px 0 18px; }
th, td { border: 1px solid #d9dde3; padding: 5px 8px; text-align: right; }
th { background: #eef1f5; font-weight: 600; }
td.l, th.l { text-align: left; }
tr:nth-child(even) td { background: #fafbfc; }
.ok { color: #0a7d32; font-weight: 600; }
.bad { color: #b3261e; font-weight: 600; }
.warn { color: #b25e09; font-weight: 600; }
.run { color: #1a56b0; font-weight: 600; }
.pill { display: inline-block; padding: 1px 8px; border-radius: 10px;
        font-size: 11.5px; font-weight: 600; }
.pill.ok { background: #e2f3e7; } .pill.bad { background: #fbe9e7; }
.pill.warn { background: #fdf0dd; } .pill.run { background: #e3edfb; }
details { margin: 8px 0 16px; }
summary { cursor: pointer; font-weight: 600; font-size: 13.5px;
          padding: 6px 10px; background: #eef1f5; border-radius: 6px; }
details[open] summary { border-radius: 6px 6px 0 0; }
.grid2 { display: grid; grid-template-columns: 1fr 1fr; gap: 0 24px; }
.small { font-size: 12px; color: #666; }
code { background: #eef1f5; padding: 0 4px; border-radius: 3px; font-size: 12px; }
"""


def esc(x) -> str:
    return html_mod.escape(str(x))


def table(headers: list[str], rows: list[list], cls: str = "") -> str:
    h = "".join(f'<th class="{"l" if i == 0 else ""}">{esc(c)}</th>'
                for i, c in enumerate(headers))
    body = ""
    for r in rows:
        body += "<tr>" + "".join(
            f'<td class="{"l" if i == 0 else ""}">{c}</td>' for i, c in enumerate(r)
        ) + "</tr>"
    return f'<table class="{cls}"><thead><tr>{h}</tr></thead><tbody>{body}</tbody></table>'


def pct(n: int, d: int) -> str:
    return f"{n / d * 100:.1f}%" if d else "—"


def status_pill(stats: dict) -> str:
    man_n = sum(stats["man_out"].values()) if stats["man_out"] else 0
    if stats["valid_manifest"] and man_n >= stats["n_c"]:
        return '<span class="pill ok">complete</span>'
    if man_n and stats["n_c"] > man_n:
        return (f'<span class="pill run">running</span>')
    if stats["model"] == "gemini-3-pro" and not stats["reasoning"]:
        return '<span class="pill run">running</span>'
    return '<span class="pill warn">in&nbsp;progress</span>'


def mix_cols(mix: dict, key: str) -> int:
    """count entries in a channel-mix dict that include channel key."""
    return sum(v for k, v in mix.items() if key in k)


def main() -> None:
    t0 = time.time()
    subset = load_subset()
    subset_set = set(subset)
    cells = [analyze_cell(c) for c in discover_cells()]
    by_model: dict[str, list[dict]] = defaultdict(list)
    for c in cells:
        by_model[c["model"]].append(c)

    now = datetime.now().strftime("%Y-%m-%d %H:%M CST")
    parts: list[str] = []
    parts.append(f"""<!DOCTYPE html><html><head><meta charset="utf-8">
<title>Data Collection Report — chatgpt-codesec-analysis</title>
<style>{CSS}</style></head><body><div class="wrap">
<h1>Data Collection Progress Report</h1>
<div class="meta">Snapshot: {now} · Source: <code>collected_code_6/</code> + <code>results/*.manifest.json</code> ·
Channel classification replicates <code>comment_inject.py</code> exactly (validated: qwen s+d heal_0 flagged set matches <code>heal_1/to_be_healed</code> 193/193)</div>
<p class="note"><b>Expected sizes:</b> full sweep = 974 tasks × 3 samples = <b>2,922</b> (dataset has 974 BCT tasks);
subset cells (top-200 vulnerable problems) = <b>600</b>. Asymmetries by design: qwen s+d baseline = 2 samples (400);
early deepseek/qwen static temp/top_p grid = 1 sample (200).
<b>Channels:</b> S = static (gcc -fanalyzer, clang+z3, cppcheck premium, flawfinder) ·
A = dynamic sanitizer (ASan/UBSan) · T = test-case failures. Fuzz channel (AFL++) is disabled in all cells (fuzz=false).</p>
""")

    # =============================================================== §1 heal_0
    parts.append("<h2>1. Round-0 (heal_0) generation &amp; detection status</h2>")

    # 1a full sweeps
    parts.append("<h3>1a. Non-thinking full sweeps — 974 × 3 = 2,922 (static gate)</h3>")
    parts.append('<p class="note">These cells measure the <b>static</b> gate only — dynamic (sanitizer) and test-failure '
                 'detection was not run on the full sweep (it is measured on the top-200 subset cells in §1b/§1c, '
                 'where round-0 code is shared with the full sweep via <code>--gen-source</code>).</p>')
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro", "claude-fable-5"]:
        c = next((x for x in by_model.get(model, [])
                  if x["feedback"] == "static" and not x["reasoning"]
                  and x["temp"] == "1.0" and x["top_p"] == "1.0"), None)
        if c is None:
            rows.append([model, "—", "—", "—", "—", "—", '<span class="bad">missing</span>'])
            continue
        analyzed_note = "" if c["analyzed"] == c["n_c"] else \
            f' <span class="warn">({c["analyzed"]} analyzed)</span>'
        status = status_pill(c)
        if model == "gemini-3-pro":
            status = '<span class="pill run">running (generation phase)</span>'
        if model == "claude-fable-5":
            status = '<span class="pill bad">aborted — no API key</span>'
        rows.append([
            model, f"{c['n_c']:,} / 2,922", pct(c["n_c"], EXPECTED_FULL),
            f"{c['clean0']} ({pct(c['clean0'], c['n_an'] or 1)})",
            f"{c['flagged0']} ({pct(c['flagged0'], c['n_an'] or 1)}){analyzed_note}",
            f"{c['noncomp0']} ({pct(c['noncomp0'], c['n_an'] or 1)})",
            status,
        ])
    parts.append(table(
        ["Model", "heal_0 files", "Coverage", "Clean at heal_0",
         "Static detections", "Not compilable", "Status"], rows))

    # 1b s+d subset cells heal_0 channel matrix
    parts.append("<h3>1b. static+dynamic cells — heal_0 channel matrix (main experiment: full 974 × 3 where n = 2,922)</h3>")
    parts.append('<p class="note">Round-0 code is shared with the model\'s full sweep (imported via <code>--gen-source</code>; '
                 'legacy 2-sample qwen cell archived 2026-09-10). Cells mid-run show the analysis-complete subset only. Channel mix legend: '
                 '<b>S</b>=static only, <b>A</b>=sanitizer only, <b>T</b>=test-failure only, combinations = overlaps. '
                 '“Flagged (S+A+T)” = union of all three channels (what the s+d gate sees).</p>')
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro"]:
        c = next((x for x in by_model.get(model, [])
                  if x["feedback"] == "static+dynamic" and x["temp"] == "1.0"
                  and x["top_p"] == "1.0"), None)
        if c is None:
            rows.append([model, "—"] + ["—"] * 10 + ['<span class="bad">not started</span>'])
            continue
        m = c["mix0"]
        order = ["---", "S--", "-A-", "--T", "SA-", "S-T", "-AT", "SAT"]
        mix_cells = [m.get(k, 0) for k in order]
        rows.append([
            model, f"{c['n_c']}",
            f"{c['clean0']} ({pct(c['clean0'], c['n_an'] or 1)})",
            *mix_cells,
            f"{c['flagged0']} ({pct(c['flagged0'], c['n_an'] or 1)})",
            f"{c['noncomp0']}",
            status_pill(c),
        ])
    parts.append(table(
        ["Model", "n", "Clean at start", "clean<br>(---)", "S only", "A only",
         "T only", "S+A", "S+T", "A+T", "S+A+T", "Flagged (union)",
         "Not compilable", "Status"], rows))

    # 1c dynamic-only cells
    parts.append("<h3>1c. Dynamic-only feedback cells — heal_0 (200 × 3 = 600)</h3>")
    parts.append('<p class="note">Same shared round-0 code; only the dynamic channel (sanitizer + tests) gates these cells.</p>')
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro"]:
        c = next((x for x in by_model.get(model, [])
                  if x["feedback"] == "dynamic"), None)
        if c is None:
            rows.append([model, "—", "—", "—", "—", "—", '<span class="bad">not started</span>'])
            continue
        m = c["mix0"]
        asan_n = mix_cols(m, "A")
        test_n = mix_cols(m, "T")
        rows.append([
            model, c["n_c"], f"{c['clean0']} ({pct(c['clean0'], c['n_an'] or 1)})",
            f"{c['flagged0']} ({pct(c['flagged0'], c['n_an'] or 1)})",
            f"{asan_n}", f"{test_n}", f"{c['noncomp0']}", status_pill(c),
        ])
    parts.append(table(
        ["Model", "n", "Clean (dyn gate)", "Dynamic-flagged", "of which sanitizer (A)",
         "of which test-fail (T)", "Not compilable*", "Status"], rows))

    # 1d thinking cells
    parts.append("<h3>1d. Thinking variants — static subset cells (200 × 3 = 600)</h3>")
    parts.append('<p class="note">Thinking cells generate their own round-0 (no <code>--gen-source</code>): '
                 'decoding differs from the non-thinking base, so round-0 cannot be shared. Static gate.</p>')
    rows = []
    for model in ["deepseek-v4-pro-thinking", "kimi-k3-thinking", "glm-5.1-thinking",
                  "openai-gpt56-sol-thinking", "gemini-3-pro-thinking"]:
        c = next((x for x in by_model.get(model, [])
                  if x["reasoning"] and x["feedback"] == "static"
                  and x["temp"] == "1.0" and x["top_p"] == "1.0"), None)
        if c is None:
            rows.append([model, "—", "—", "—", "—", '<span class="bad">missing</span>'])
            continue
        status = status_pill(c)
        if model == "glm-5.1-thinking" and not c["valid_manifest"]:
            status = '<span class="pill warn">healing in progress (manifest pending)</span>'
        if model == "openai-gpt56-sol-thinking":
            status = '<span class="pill bad">blocked — OpenAI credits exhausted</span>'
        if model == "gemini-3-pro-thinking":
            status = '<span class="pill bad">not started (1 stray probe file)</span>'
        rows.append([
            model, f"{c['n_c']:,} / 600", pct(c["n_c"], EXPECTED_SUBSET),
            f"{c['clean0']} ({pct(c['clean0'], c['n_an'] or 1)})",
            f"{c['flagged0']} ({pct(c['flagged0'], c['n_an'] or 1)})",
            f"{c['noncomp0']}", status,
        ])
    parts.append(table(
        ["Model", "heal_0 files", "Coverage", "Clean at start",
         "Static detections", "Not compilable", "Status"], rows))

    # 1e compile-fix outcomes: did the LLM heal non-compilable samples?
    parts.append("<h3>1e. Non-compilability outcomes — can the LLM heal compile errors?</h3>")
    parts.append('<p class="note">Non-compilable code is never executed (dynamic analysis is skipped; '
                 'compile errors are fed back to the LLM via the static channel). '
                 '*For dynamic-only cells, non-compilability is read from the static sibling cell '
                 '(shared round-0 code). This table shows what happened to each sample that was '
                 'non-compilable at heal_0: <b>healed</b> = the LLM fixed the compile errors within '
                 '10 rounds (outcome “clean”); never cleaned = compile errors (or other findings) persisted. '
                 '“Gate-blind” = the sample was never flagged by that cell\'s feedback gate — for '
                 'dynamic-only cells compile errors are invisible to the dynamic oracle (they are a '
                 'static-channel finding), so non-compilable samples there count as clean-at-start '
                 'w.r.t. the dynamic gate only.</p>')
    rows = []
    for c in sorted(cells, key=lambda x: (x["model"], x["slug"])):
        if not c["noncomp0"]:
            continue
        o = c["nc_out"]
        n = c["noncomp0"]
        healed = o.get("clean", 0)
        rows.append([
            c["model"], c["slug"].replace("feedback-", ""),
            n, healed, pct(healed, n),
            o.get("not_cleaned", 0), o.get("heal_failed", 0),
            o.get("clean_at_start", 0), o.get("pending", 0),
            status_pill(c) if (c["valid_manifest"] or sum(o.values()) == 0)
            else '<span class="pill warn">in&nbsp;progress</span>',
        ])
    if rows:
        parts.append(table(
            ["Model", "Cell", "Non-compilable at heal_0", "Healed by LLM",
             "Fix rate", "Never cleaned", "Heal failed",
             "Gate-blind (clean@start)", "Pending (running)",
             "Status"], rows))
    else:
        parts.append('<p class="note">No non-compilable samples recorded in any cell.</p>')

    # ====================================================== §2 healing rounds
    parts.append("<h2>2. Healing-rounds progress (per cell)</h2>")
    parts.append('<p class="note">Funnel per round: <b>entered</b> = files flagged at round start (heal_N/to_be_healed); '
                 '<b>cleaned</b> = reached zero findings after this round\'s heal; <b>remaining</b> = still flagged → next round; '
                 '<b>heal_failed</b> = heal API call failed permanently (artifact missing — never counted clean). '
                 'Channel mix (S/A/T) classifies each entering file by which channels flagged it in the previous round\'s code. '
                 '“awaiting-verification” = healed code written but next-round analysis not yet run; '
                 'cells with manifests also show the rounds-to-clean (RTC) histogram from the manifest.</p>')

    def funnel_html(c: dict) -> str:
        rows = []
        for r in c["rounds"]:
            n = r["round"]
            if r.get("state") == "converged" or r["entered"] == 0:
                rows.append([f"round {n}", 0, "—", "—", "—", "—", "—", "—", "converged"])
                continue
            mix = r.get("mix", {})
            s_n, a_n, t_n = (mix_cols(mix, "S"), mix_cols(mix, "A"), mix_cols(mix, "T"))
            state = r["state"]
            if state == "done":
                tail = (f'<span class="ok">{r["cleaned"]} cleaned</span>, '
                        f'{r["remaining"]} remain, {r["heal_failed"]} heal_failed')
            elif state == "awaiting-verification":
                tail = '<span class="warn">healed, awaiting verification</span>'
            else:
                tail = f'<span class="run">healing… ({r["healed_present"]}/{r["entered"]} written)</span>'
            rows.append([f"round {n}", r["entered"], s_n, a_n, t_n,
                         r.get("cleaned", "—"), r.get("remaining", "—"),
                         r.get("heal_failed", "—"), tail])
        out = table(["Round", "Entered", "S", "A", "T", "Cleaned", "Remaining",
                     "Heal failed", "State"], rows)
        if c["valid_manifest"] and c["rtc"]:
            h = c["rtc"]
            hist = ", ".join(f"r{k}: {v}" for k, v in sorted(h.items()))
            out += f'<p class="small">RTC histogram (round at which cleaned): {hist}</p>'
        mo = c["man_out"]
        if mo:
            out += (f'<p class="small">Manifest outcomes: clean_at_start {mo.get("clean_at_start", 0)}'
                    f' · clean {mo.get("clean", 0)} · not_cleaned {mo.get("not_cleaned", 0)}'
                    f' · heal_failed {mo.get("heal_failed", 0)} · n = {sum(mo.values())}</p>')
        return out

    # group: full sweeps, s+d cells, dynamic cells, thinking, temp/top_p
    groups = [
        ("Full sweeps — static feedback (974 × 3)",
         lambda c: c["feedback"] == "static" and not c["reasoning"]
         and c["temp"] == "1.0" and c["top_p"] == "1.0" and c["n_c"] > 1000),
        ("static+dynamic cells (subset)", lambda c: c["feedback"] == "static+dynamic"),
        ("Dynamic-only cells (subset)", lambda c: c["feedback"] == "dynamic"),
        ("Thinking cells (subset, static)",
         lambda c: c["reasoning"] and c["temp"] == "1.0" and c["top_p"] == "1.0"
         and c["feedback"] == "static" and c["n_c"] <= 1000),
        ("Early static-only temp/top_p grid (1 sample, 200)",
         lambda c: c["feedback"] == "static" and not c["reasoning"]
         and (c["temp"] != "1.0" or c["top_p"] != "1.0") and c["n_c"] <= 300),
    ]
    for title, pred in groups:
        grp = [c for c in cells if pred(c)]
        if not grp:
            continue
        parts.append(f"<h3>{esc(title)}</h3>")
        for c in sorted(grp, key=lambda x: (x["model"], x["slug"])):
            label = f"{c['model']} · {c['slug']}"
            pill = status_pill(c)
            parts.append(
                f"<details><summary>{esc(label)} &nbsp;{pill} &nbsp;"
                f'<span class="small">heal_0: {c["n_c"]} files · '
                f'{c["clean0"]} clean / {c["flagged0"]} flagged</span></summary>'
                f"{funnel_html(c)}</details>")

    # ========================================================== §3 ablations
    parts.append("<h2>3. Ablation status</h2>")

    # 3a thinking vs non-thinking
    parts.append("<h3>3a. Thinking vs non-thinking (static gate, top-200 subset, 3 samples)</h3>")
    parts.append('<p class="note">Non-thinking comparator = the model\'s full-sweep manifest restricted to the '
                 'same 200 problems (same shared round-0 code for deepseek/glm/kimi/gpt; independent draws otherwise). '
                 'Note: thinking round-0 is generated fresh, so initial-cleanliness comparisons are across '
                 'independent draws, but within-model.</p>')
    rows = []
    for model in ["deepseek-v4-pro", "kimi-k3", "glm-5.1", "openai-gpt56-sol",
                  "gemini-3-pro"]:
        base = next((x for x in by_model.get(model, [])
                     if x["feedback"] == "static" and not x["reasoning"]
                     and x["temp"] == "1.0" and x["top_p"] == "1.0"), None)
        think_model = model + "-thinking"
        think = next((x for x in by_model.get(think_model, [])
                      if x["reasoning"] and x["temp"] == "1.0"
                      and x["top_p"] == "1.0"), None)
        if base is None or think is None:
            rows.append([model, "—", "—", "—", "—", '<span class="bad">missing</span>'])
            continue
        bm = load_manifest(model, base["slug"])
        bo = outcome_counts(bm, subset_set)
        bn = sum(bo.values())
        to = think["man_out"]
        tn = sum(to.values())
        cs_b = bo.get("clean_at_start", 0)
        cs_t = to.get("clean_at_start", 0)
        fin_b = cs_b + bo.get("clean", 0)
        fin_t = cs_t + to.get("clean", 0)
        rows.append([
            model,
            f"{cs_b}/{bn} ({pct(cs_b, bn)}) · final {pct(fin_b, bn)}",
            f"{think['n_c']}/600",
            f"{cs_t}/{tn if tn else think['n_c']} ({pct(cs_t, tn if tn else think['n_c'])})",
            f"final {pct(fin_t, tn) if tn else '—'} · nc {to.get('not_cleaned', '—')} · hf {to.get('heal_failed', '—')}",
            status_pill(think),
        ])
    parts.append(table(
        ["Model", "Non-thinking (subset-restricted): clean@start · final",
         "Thinking heal_0", "Thinking clean@start", "Thinking final / not_cleaned / heal_failed",
         "Status"], rows))

    # 3b temp/top_p
    parts.append("<h3>3b. Temperature / top_p grid — s+d feedback (subset, 3 samples)</h3>")
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "gemini-3-pro"]:
        for temp, tp, label in [("0.2", "1.0", "t0.2-p1.0"), ("1.0", "0.5", "t1.0-p0.5")]:
            c = next((x for x in by_model.get(model, [])
                      if x["feedback"] == "static+dynamic" and x["temp"] == temp
                      and x["top_p"] == tp), None)
            if c is None:
                rows.append([model, label, "—", "—", "—", "—", '<span class="bad">not started</span>'])
                continue
            o = c["man_out"]
            n = sum(o.values()) or c["n_c"]
            rows.append([
                model, label, c["n_c"],
                f"{c['clean0']} ({pct(c['clean0'], c['n_an'] or 1)})",
                f"{o.get('clean_at_start', 0)} · {o.get('clean', 0)} · {o.get('not_cleaned', 0)}",
                pct((o.get("clean_at_start", 0) + o.get("clean", 0)), n),
                status_pill(c),
            ])
    parts.append(table(
        ["Model", "Cell", "n", "Clean at heal_0", "cs · clean · not_cleaned",
         "Final clean", "Status"], rows))
    parts.append('<p class="note small">Early static-only grid (deepseek + qwen, 1 sample, superseded by the s+d '
                 're-runs under the corrected design): deepseek t0.2 200 files (139/57/4) · p0.5 (127/69/4); '
                 'qwen t0.2 (126/72/2) · p0.5 (142/55/3). Also on disk: <code>qwen-max feedback-none-t0.5-p0.5</code> '
                 '— an empty directory, never collected. Claude/Kimi cannot run the grid: Replicate→native Claude has '
                 'no sampling params (and Kimi rejects temperature/top_p on all DashScope paths).</p>')

    # ===================================================== §4 s/d/s+d 3-arm
    parts.append("<h2>4. static / dynamic / static+dynamic — 3-arm feedback ablation</h2>")
    parts.append('<p class="note">Detection sets are computed on the <b>s+d cell\'s shared round-0</b> (static + dynamic '
                 'reports on identical code). Arms: <b>static</b> = full-sweep static-feedback manifest restricted to the '
                 '200 problems · <b>dynamic</b> = dynamic-only cell · <b>s+d</b> = s+d baseline cell. '
                 '“Healed on each round” = RTC histogram. Remainders = not_cleaned after 10 rounds.</p>')
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro"]:
        sd = next((x for x in by_model.get(model, [])
                   if x["feedback"] == "static+dynamic" and x["temp"] == "1.0"
                   and x["top_p"] == "1.0"), None)
        if sd is None or sd["n_c"] < 100:
            parts.append(f"<h3>{esc(model)}</h3>"
                         '<p class="note bad">s+d baseline cell not started — 3-arm analysis unavailable.</p>')
            continue
        base = next((x for x in by_model.get(model, [])
                     if x["feedback"] == "static" and not x["reasoning"]
                     and x["temp"] == "1.0" and x["top_p"] == "1.0"), None)
        dyn = next((x for x in by_model.get(model, [])
                    if x["feedback"] == "dynamic"), None)
        parts.append(f"<h3>{esc(model)}</h3>")

        # detection sets at heal_0 (problem level, any of 3 samples)
        det_s, det_a, det_t = set(), set(), set()
        for b, (s, a, t) in sd["flags0"].items():
            if b not in sd["an_bases"]:
                continue  # analysis incomplete for this sample
            p = pid_of(b)
            if s: det_s.add(p)
            if a: det_a.add(p)
            if t: det_t.add(p)
        n_probs = len({pid_of(b) for b in sd["flags0"] if b in sd["an_bases"]})
        det_dyn = det_a | det_t
        rows = [
            ["Detected by static (any sample)", len(det_s), pct(len(det_s), n_probs)],
            ["Detected by sanitizer (A)", len(det_a), pct(len(det_a), n_probs)],
            ["Detected by test failures (T)", len(det_t), pct(len(det_t), n_probs)],
            ["Detected by dynamic (A∪T)", len(det_dyn), pct(len(det_dyn), n_probs)],
            ["Static ∩ dynamic", len(det_s & det_dyn), pct(len(det_s & det_dyn), n_probs)],
            ["Union (s+d gate, any channel)", len(det_s | det_dyn), pct(len(det_s | det_dyn), n_probs)],
            ["Never detected (clean problems)", n_probs - len(det_s | det_dyn),
             pct(n_probs - len(det_s | det_dyn), n_probs)],
        ]
        parts.append(table(["Detection at heal_0 (problems, n=%d)" % n_probs, "Count", "%"], rows))

        # per-arm outcomes
        def arm_row(label, man, cell):
            if man is None and cell is None:
                return [label, "—", "—", "—", "—", "—"]
            o = outcome_counts(man, subset_set) if man else {}
            n = sum(o.values())
            if not n and cell:
                # derive from disk
                n = cell["n_c"]
                o = {"clean_at_start": cell["clean0"]}
            cs = o.get("clean_at_start", 0)
            cl = o.get("clean", 0)
            nc = o.get("not_cleaned", 0)
            hf = o.get("heal_failed", 0)
            rtc = rtc_histogram(man, subset_set) if man else {}
            hist = ", ".join(f"r{k}={v}" for k, v in sorted(rtc.items())) or "—"
            return [label, n, f"{cs} ({pct(cs, n)})", cl, f"{nc}", f"{hf}" if hf else "0",
                    hist]

        bm = load_manifest(model, base["slug"]) if base else None
        dm = load_manifest(model, dyn["slug"]) if dyn else None
        sm = load_manifest(model, sd["slug"])
        rows = [
            arm_row("static arm", bm, base),
            arm_row("dynamic arm", dm, dyn),
            arm_row("static+dynamic arm", sm, sd),
        ]
        parts.append(table(
            ["Arm (feedback channels)", "n", "Clean at start", "Healed (total)",
             "Not cleaned", "Heal failed", "Healed per round (RTC)"], rows))

        # per-problem appendix
        prob_rows = []
        for p in subset:
            s_flag = "●" if p in det_s else ""
            a_flag = "●" if p in det_a else ""
            t_flag = "●" if p in det_t else ""

            def arm_counts(man):
                if man is None:
                    return "—"
                cs = cl = nc = 0
                n = 0
                for key, rec in man["outcomes"].items():
                    m = re.match(r"problem-(\d+)", key)
                    if not m or int(m.group(1)) != p:
                        continue
                    n += 1
                    oc = rec["outcome"] if isinstance(rec, dict) else rec
                    if oc == "clean_at_start": cs += 1
                    elif oc == "clean": cl += 1
                    elif oc == "not_cleaned": nc += 1
                return f"{cs}/{cl}/{nc}" if n else "—"

            prob_rows.append([
                p, s_flag, a_flag, t_flag,
                arm_counts(bm), arm_counts(dm), arm_counts(sm),
            ])
        parts.append(
            "<details><summary>Per-problem appendix — detection flags and per-arm outcomes "
            "(cs/clean/nc per problem)</summary>"
            + table(["Problem", "S", "A", "T", "static arm", "dynamic arm", "s+d arm"],
                    prob_rows)
            + "</details>")

    # ================================================================ footer
    parts.append(f"""
<h2>Cell inventory</h2>
""")
    inv_rows = []
    for c in sorted(cells, key=lambda x: (x["model"], x["slug"])):
        o = c["man_out"]
        man_n = sum(o.values()) if o else 0
        inv_rows.append([
            c["model"], c["slug"].replace("feedback-", ""), c["n_c"],
            c["clean0"], c["flagged0"], man_n or "—",
            "valid" if c["valid_manifest"] else "pending",
        ])
    parts.append(table(["Model", "Cell", "heal_0 files", "Clean@0", "Flagged@0",
                        "Manifest n", "Manifest"], inv_rows))
    parts.append(f"""
<p class="meta small">Generated in {time.time() - t0:.1f}s · {len(cells)} cells discovered ·
snapshot timestamp {now} · gemini-3-pro full sweep is actively generating (numbers are a moving snapshot).</p>
</div></body></html>""")

    OUT.write_text("\n".join(parts))
    print(f"[collection_report] wrote {OUT} ({OUT.stat().st_size / 1024:.0f} KB) "
          f"in {time.time() - t0:.1f}s; {len(cells)} cells")


if __name__ == "__main__":
    main()

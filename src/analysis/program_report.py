"""Program-level progress report: the four experiment programs.

P1 Main experiment   — s+d healing on the FULL 974x3 set, non-thinking
P2 Thinking ablation — s+d, top-200 subset x3, thinking variants
P3 Temp/top_p        — s+d, top-200 subset x3, non-thinking, t0.2 / p0.5
P4 Methods ablation  — static-only vs dynamic-only vs s+d arms (subset x3)

Per cell: outcomes, rounds-to-clean distribution, exact token/latency usage
from the per-call ledger (subset-filtered where the arm is a restriction).

Output: results/program_report.html
"""
from __future__ import annotations

import html as html_mod
import json
import statistics
import time
from collections import Counter
from datetime import datetime
from pathlib import Path

import csv

REPO = Path(__file__).resolve().parents[2]
RESULTS = REPO / "results"
OUT = RESULTS / "program_report.html"

CSS = """
body { font-family: -apple-system, 'Helvetica Neue', Arial, sans-serif; margin: 0;
       background: #f5f6f8; color: #1c1e21; }
.wrap { max-width: 1180px; margin: 0 auto; padding: 24px 20px 60px; }
h1 { font-size: 25px; margin: 8px 0 2px; }
h2 { font-size: 19px; margin: 32px 0 10px; border-bottom: 2px solid #dfe3e8; padding-bottom: 6px; }
h3 { font-size: 15px; margin: 18px 0 6px; }
p.note { color: #555; font-size: 13px; line-height: 1.5; margin: 6px 0; }
.meta { color: #777; font-size: 12.5px; }
table { border-collapse: collapse; width: 100%; font-size: 12.5px; background: #fff;
        margin: 8px 0 16px; }
th, td { border: 1px solid #d9dde3; padding: 4px 7px; text-align: right; }
th { background: #eef1f5; font-weight: 600; }
td.l, th.l { text-align: left; }
tr:nth-child(even) td { background: #fafbfc; }
.ok { color: #0a7d32; font-weight: 600; }
.bad { color: #b3261e; font-weight: 600; }
.warn { color: #b25e09; font-weight: 600; }
.small { font-size: 11.5px; color: #666; }
.sub { color: #1a56b0; font-weight: 600; }
"""


def esc(x) -> str:
    return html_mod.escape(str(x))


def table(headers, rows):
    h = "".join(f'<th class="{"l" if i == 0 else ""}">{esc(c)}</th>'
                for i, c in enumerate(headers))
    body = "".join(
        "<tr>" + "".join(f'<td class="{"l" if i == 0 else ""}">{c}</td>'
                         for i, c in enumerate(r)) + "</tr>" for r in rows)
    return f"<table><thead><tr>{h}</tr></thead><tbody>{body}</tbody></table>"


def pct(n, d):
    return f"{n / d * 100:.1f}%" if d else "—"


def load_manifest(model, slug):
    p = RESULTS / model / f"{slug}.manifest.json"
    if not p.is_file():
        return None
    return json.loads(p.read_text())


def outcomes(man, pids=None):
    """(Counter of outcomes, rtc list) optionally restricted to problem ids."""
    c, rtc = Counter(), []
    if not man:
        return c, rtc
    for key, rec in man["outcomes"].items():
        if pids is not None:
            pid = int(key.replace("problem-", "").split("-")[0].split("s")[0])
            if pid not in pids:
                continue
        oc = rec["outcome"] if isinstance(rec, dict) else rec
        c[oc] += 1
        if oc == "clean":
            rtc.append(rec.get("rounds_to_clean", 0))
    return c, rtc


def usage(model, slug, pids=None):
    """Exact ledger usage, optionally restricted to subset problem ids."""
    p = RESULTS / model / f"{slug}.usage.jsonl"
    if not p.is_file():
        return None
    calls = [json.loads(l) for l in p.read_text().splitlines()]
    if pids is not None:
        calls = [x for x in calls if x.get("task_id") in pids]
    ok = [x for x in calls if x.get("ok")]
    g = lambda k: sum((x.get(k) or 0) for x in ok)
    lat = [x.get("latency_s") or 0 for x in ok]
    return {
        "calls": len(calls), "ok": len(ok), "fail": len(calls) - len(ok),
        "prompt": g("prompt_tokens"), "completion": g("completion_tokens"),
        "reasoning": g("reasoning_tokens"), "total": g("total_tokens"),
        "lat_total": sum(lat),
        "lat_mean": (sum(lat) / len(lat)) if lat else 0,
    }


def rtc_cell(rtc):
    if not rtc:
        return "—", "—"
    hist = Counter(rtc)
    return (f"{statistics.mean(rtc):.2f}",
            " ".join(f"r{k}:{hist[k]}" for k in sorted(hist)))


def fmt_tok(n):
    return f"{n / 1e6:.2f}M" if n >= 1e6 else (f"{n / 1e3:.0f}K" if n >= 1e3 else str(n))


def main() -> None:
    t0 = time.time()
    now = datetime.now().strftime("%Y-%m-%d %H:%M CST")
    with open(RESULTS / "vulnerable_subset.csv") as f:
        subset = {int(r["problem_id"]) for r in list(csv.DictReader(f))[:200]}

    # gemini static sweep progress
    gem_dir = REPO / "collected_code_6/gemini-3-pro/feedback-static-r0-t1.0-p1.0/heal_0"
    gem_n = len([f for f in gem_dir.iterdir() if f.name.endswith(".c")]) if gem_dir.is_dir() else 0

    parts = [f"""<!DOCTYPE html><html><head><meta charset="utf-8">
<title>Program Progress Report</title><style>{CSS}</style></head><body><div class="wrap">
<h1>Experiment Program Progress Report</h1>
<div class="meta">Snapshot {now} · Manifests + per-call usage ledgers ·
dataset = 974 BCT tasks (the “973” in requests is 974) · gates: static = 4 analyzers
(gcc -fanalyzer, clang+z3, cppcheck premium, flawfinder); dynamic = ASan/UBSan oracle;
tests = MBPP test cases (bonus signal inside the dynamic channel) · max_rounds = 10.</div>
"""]

    # ============================================================= P1 main
    parts.append("<h2>1 · Main experiment — s+d healing, full 974 × 3 (non-thinking)</h2>")
    parts.append('<p class="note">Round-0 code is shared with each model\'s static-only sweep '
                 '(free via gen-source). s+d = static + sanitizer + tests. “Rounds (mean)” = '
                 'average rounds-to-clean among healed samples; histogram shows the distribution.</p>')
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro", "claude-fable-5"]:
        man = load_manifest(model, "feedback-static+dynamic-r0-t1.0-p1.0")
        u = usage(model, "feedback-static+dynamic-r0-t1.0-p1.0")
        if man is None:
            if model == "gemini-3-pro":
                rows.append([model, f"static sweep {gem_n:,}/2,922 ({pct(gem_n, 2922)})",
                             "—", "—", "—", "—", "—", "—", "—", "—",
                             '<span class="warn">round-0 generating (free-tier throttled)</span>'])
            elif model == "claude-fable-5":
                rows.append([model, "26 files", "—", "—", "—", "—", "—", "—", "—", "—",
                             '<span class="bad">blocked — no API key</span>'])
            else:
                rows.append([model, "—"] + ["—"] * 8 +
                            ['<span class="bad">missing</span>'])
            continue
        c, rtc = outcomes(man)
        n = sum(c.values())
        cs, cl = c.get("clean_at_start", 0), c.get("clean", 0)
        nc, hf = c.get("not_cleaned", 0), c.get("heal_failed", 0)
        mean_r, hist = rtc_cell(rtc)
        note = ""
        if model == "openai-gpt56-sol":
            note = ' <span class="warn">(subset only — full set blocked on OpenAI credits)</span>'
            status = '<span class="warn">partial</span>'
        else:
            status = '<span class="ok">complete</span>'
        us = (f"{fmt_tok(u['prompt'])} / {fmt_tok(u['completion'])}"
              f"{f' (reas. {fmt_tok(u[chr(39)+'reasoning'+chr(39)])})' if u['reasoning'] else ''}<br>"
              f"total {fmt_tok(u['total'])}, {u['ok']:,} calls, "
              f"{u['lat_total'] / 3600:.1f}h") if u else "—"
        rows.append([
            model + note, f"{n:,}", f"{cs:,} ({pct(cs, n)})", f"{cl:,}",
            f"{nc:,}", f"{hf}" if hf else "0",
            f"<b>{pct(cs + cl, n)}</b>", mean_r, hist, us, status,
        ])
    parts.append(table(
        ["Model", "n", "Clean at start", "Healed", "Not cleaned",
         "Heal failed", "Final clean", "Rounds (mean)", "Rounds histogram",
         "Tokens (in / out)", "Status"], rows))

    # ======================================================== P2 thinking
    parts.append("<h2>2 · Thinking ablation — s+d, top-200 × 3 (thinking variants)</h2>")
    parts.append('<p class="note">Thinking round-0 is generated fresh (its own draws); the '
                 'non-thinking comparator is the main cell restricted to the same 200 problems '
                 '(shared round-0 across arms). deepseek-v4-pro-thinking\'s 12 heal_failed are '
                 'reasoning-chain length-limit failures (32k budget exhausted before code is '
                 'emitted), not refusals.</p>')
    rows = []
    for model in ["deepseek-v4-pro", "kimi-k3", "glm-5.1", "openai-gpt56-sol",
                  "gemini-3-pro"]:
        tm = model + "-thinking"
        man = load_manifest(tm, "feedback-static+dynamic-r1-t1.0-p1.0")
        u = usage(tm, "feedback-static+dynamic-r1-t1.0-p1.0")
        base = load_manifest(model, "feedback-static+dynamic-r0-t1.0-p1.0")
        bc, _ = outcomes(base, subset)
        bn = sum(bc.values())
        if man is None:
            if model == "openai-gpt56-sol":
                why = "thinking static cell 65/600 — OpenAI credits"
            elif model == "gemini-3-pro":
                why = "round-0 sweep incomplete (free tier)"
            else:
                why = "missing"
            rows.append([model, "—", "—", "—", "—", "—", "—", "—", "—", "—",
                         f'<span class="bad">{why}</span>'])
            continue
        c, rtc = outcomes(man)
        n = sum(c.values())
        cs, cl = c.get("clean_at_start", 0), c.get("clean", 0)
        nc, hf = c.get("not_cleaned", 0), c.get("heal_failed", 0)
        mean_r, hist = rtc_cell(rtc)
        bcs = bc.get("clean_at_start", 0)
        delta = (cs / n - bcs / bn) * 100 if bn else 0
        us = (f"{fmt_tok(u['prompt'])} / {fmt_tok(u['completion'])} "
              f"(reas. {fmt_tok(u['reasoning'])})<br>total {fmt_tok(u['total'])}, "
              f"{u['ok']:,} calls, {u['lat_total'] / 3600:.1f}h") if u else "—"
        rows.append([
            model, f"{n}", f"{cs} ({pct(cs, n)})",
            f"{f'{delta:+.1f}pp' if bn else '—'} vs base {pct(bcs, bn)}",
            f"{cl}", f"{nc}", f"{hf}" if hf else "0",
            f"<b>{pct(cs + cl, n)}</b>", mean_r, hist, us,
            '<span class="ok">complete</span>',
        ])
    parts.append(table(
        ["Model", "n", "Clean at start", "Δ vs non-thinking (subset)",
         "Healed", "Not cleaned", "Heal failed", "Final clean",
         "Rounds (mean)", "Histogram", "Tokens (in / out)", "Status"], rows))

    # ====================================================== P3 temp/top_p
    parts.append("<h2>3 · Temperature / top_p ablation — s+d, top-200 × 3 (non-thinking)</h2>")
    parts.append('<p class="note">Fresh round-0 at each decoding setting (decoding changes '
                 'generation). Baseline = main cell restricted to the subset. Kimi rejects '
                 'sampling parameters on all paths; GPT and Claude expose no sampling params '
                 'via their APIs — the grid is not runnable for those models.</p>')
    rows = []
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "gemini-3-pro"]:
        base = load_manifest(model, "feedback-static+dynamic-r0-t1.0-p1.0")
        bc, brtc = outcomes(base, subset)
        bn = sum(bc.values())
        if bn:
            bm, bh = rtc_cell(brtc)
            rows.append([f"{model} <span class=\"sub\">(baseline t1.0-p1.0)</span>",
                         f"{bn}", f"{bc.get('clean_at_start', 0)} ({pct(bc.get('clean_at_start', 0), bn)})",
                         "—", f"{bc.get('clean', 0)}", f"{bc.get('not_cleaned', 0)}",
                         f"{bc.get('heal_failed', 0)}",
                         f"<b>{pct(bc.get('clean_at_start', 0) + bc.get('clean', 0), bn)}</b>",
                         bm, bh, "", ""])
        for label, slug in [("t0.2-p1.0", "feedback-static+dynamic-r0-t0.2-p1.0"),
                            ("t1.0-p0.5", "feedback-static+dynamic-r0-t1.0-p0.5")]:
            man = load_manifest(model, slug)
            u = usage(model, slug)
            if man is None:
                rows.append([model, label, "—"] + ["—"] * 8 +
                            ['<span class="bad">not started</span>'])
                continue
            c, rtc = outcomes(man)
            n = sum(c.values())
            cs, cl = c.get("clean_at_start", 0), c.get("clean", 0)
            mean_r, hist = rtc_cell(rtc)
            us = (f"{fmt_tok(u['prompt'])} / {fmt_tok(u['completion'])}, "
                  f"{u['ok']:,} calls, {u['lat_total'] / 3600:.1f}h") if u else "—"
            rows.append([model, label, f"{n}",
                         f"{cs} ({pct(cs, n)})", f"{cl}", f"{c.get('not_cleaned', 0)}",
                         f"{c.get('heal_failed', 0)}",
                         f"<b>{pct(cs + cl, n)}</b>", mean_r, hist, us,
                         '<span class="ok">complete</span>'])
    parts.append(table(
        ["Model", "Cell", "n", "Clean at start", "Healed", "Not cleaned",
         "Heal failed", "Final clean", "Rounds (mean)", "Histogram",
         "Tokens (in / out)", "Status"], rows))

    # ======================================================== P4 methods
    parts.append("<h2>4 · Analysis-methods ablation — static-only vs dynamic-only vs s+d "
                 "(top-200 × 3, non-thinking)</h2>")
    parts.append('<p class="note">All three arms share the same round-0 code (imported from each '
                 'model\'s static sweep). Outcomes are relative to each arm\'s own gate: the '
                 'static arm counts only static findings; the dynamic arm only sanitizer + test '
                 'findings (compile errors are invisible to it — non-compilable code is never '
                 'executed and its compile errors heal via the static channel). Token usage is '
                 'filtered to the subset tasks. deepseek\'s static-arm usage is partial (its '
                 'RQ1 sweep partly predates the usage ledger — see usage_report.md for '
                 'char-based estimates).</p>')
    for model in ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
                  "openai-gpt56-sol", "gemini-3-pro"]:
        parts.append(f"<h3>{esc(model)}</h3>")
        rows = []
        arms = [
            ("static only", model, "feedback-static-r0-t1.0-p1.0"),
            ("dynamic only", model, "feedback-dynamic-r0-t1.0-p1.0"),
            ("static + dynamic", model, "feedback-static+dynamic-r0-t1.0-p1.0"),
        ]
        for label, m, slug in arms:
            man = load_manifest(m, slug)
            if man is None:
                rows.append([label, "—"] + ["—"] * 8 +
                            ['<span class="bad">not started</span>'])
                continue
            pids = subset if man and len(man["outcomes"]) > 1000 else None
            c, rtc = outcomes(man, pids)
            n = sum(c.values())
            u = usage(m, slug, pids)
            cs, cl = c.get("clean_at_start", 0), c.get("clean", 0)
            mean_r, hist = rtc_cell(rtc)
            us = (f"{fmt_tok(u['prompt'])} / {fmt_tok(u['completion'])}, "
                  f"{u['ok']:,} calls") if u else "—"
            rows.append([label, f"{n}", f"{cs} ({pct(cs, n)})", f"{cl}",
                         f"{c.get('not_cleaned', 0)}", f"{c.get('heal_failed', 0)}",
                         f"<b>{pct(cs + cl, n)}</b>", mean_r, hist, us,
                         '<span class="ok">complete</span>'])
        parts.append(table(
            ["Arm (feedback gate)", "n", "Clean at start", "Healed",
             "Not cleaned", "Heal failed", "Final clean", "Rounds (mean)",
             "Histogram", "Tokens (in / out, subset)", "Status"], rows))

    parts.append(f"""
<p class="meta small">Generated in {time.time() - t0:.1f}s · all token counts are exact
per-call ledger sums (no estimates except where flagged) · routing note: deepseek's main cell
ran on the first-party API (pre-2026-09-10); its thinking s+d cell ran via DashScope.</p>
</div></body></html>""")
    OUT.write_text("\n".join(parts))
    print(f"[program_report] wrote {OUT} in {time.time() - t0:.1f}s")


if __name__ == "__main__":
    main()

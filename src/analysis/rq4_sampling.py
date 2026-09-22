"""RQ4: sampling-parameter ablation (t, top_p) on the 200-problem subset.

Arms (non-thinking, full gate, r0):
  main : feedback-static+dynamic-r0-t1.0-p1.0   (the RQ1 cell)
  t0.2 : feedback-static+dynamic-r0-t0.2-p1.0
  p0.5 : feedback-static+dynamic-r0-t1.0-p0.5

Models with grid cells: DeepSeek V4 Pro, Gemini 3.1 Pro, GLM-5.1,
Qwen Max. Kimi K3's host rejects sampling parameters (no_sampling);
GPT-5.6 and Claude Fable 5 grid cells do not exist. DeepSeek's t0.2
cell fails the validity gate (heal_failed 158 > 50) and is reported
but excluded from the tests unless repaired.

Conventions identical to RQ3 (rq3_paired): unit = problem (200,
task ids from manifest outcomes), 3 samples per arm, primary =
common five-round censor on all arms, as-recorded = sensitivity;
McNemar exact on majority-of-3 pass labels, Wilcoxon signed-rank on
per-problem pass counts with rank-biserial r, cluster bootstrap
(10k resamples of problems) for rate differences.

Output: results/rq4_sampling.md
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

import numpy as np
from scipy import stats
from scipy.stats import rankdata

REPO = Path(__file__).resolve().parents[2]
R = REPO / "results"
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
GRID = {"t0.2": "feedback-static+dynamic-r0-t0.2-p1.0",
        "p0.5": "feedback-static+dynamic-r0-t1.0-p0.5"}
MODELS = ["deepseek-v4-pro", "gemini-3-pro", "glm-5.1", "qwen-max"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro", "gemini-3-pro": "Gemini 3.1 Pro",
        "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
CENSOR = 5
RNG = np.random.default_rng(20260922)


def load(model: str, slug: str) -> dict:
    return json.load(open(R / model / f"{slug}.manifest.json"))


def valid(man: dict) -> tuple[bool, str]:
    out = man["outcomes"]
    hf = sum(1 for v in out.values() if v.get("outcome") == "heal_failed")
    return (len(out) >= 100 and hf <= 50), f"n={len(out)}, heal_failed={hf}"


def tasks_of(man: dict) -> set[int]:
    return {int(m.group(1)) for k in man["outcomes"] if (m := KEY_RE.match(k))}


def per_problem(man: dict, pids: set[int], censor: int | None) -> dict:
    acc = {p: dict(df=0, flagged=0, repaired=0, n=0) for p in pids}
    for k, v in man["outcomes"].items():
        m = KEY_RE.match(k)
        if not m or int(m.group(1)) not in pids:
            continue
        p = int(m.group(1)); o = v.get("outcome")
        acc[p]["n"] += 1
        if o == "clean_at_start":
            acc[p]["df"] += 1
        else:
            acc[p]["flagged"] += 1
            if o == "clean" and (censor is None
                                 or (v.get("rounds_to_clean") or 0) <= censor):
                acc[p]["repaired"] += 1
    return acc


def rate_df(accs):
    return sum(a["df"] for a in accs) / sum(a["n"] for a in accs)


def rate_pass(accs):
    return (sum(a["df"] + a["repaired"] for a in accs)
            / sum(a["n"] for a in accs))


def rate_repair(accs):
    fl = sum(a["flagged"] for a in accs)
    return sum(a["repaired"] for a in accs) / fl if fl else float("nan")


def boot_diff(pb, pg, stat, plist, reps=10000):
    d = np.empty(reps)
    for i in range(reps):
        idx = RNG.integers(0, len(plist), len(plist))
        d[i] = stat([pg[plist[j]] for j in idx]) - stat([pb[plist[j]] for j in idx])
    return np.percentile(d, [2.5, 97.5])


def rank_biserial(x, y):
    dd = x - y; dd = dd[dd != 0]
    ranks = rankdata(np.abs(dd))
    return (ranks[dd > 0].sum() - ranks[dd < 0].sum()) / ranks.sum()


def compare(model: str, grid: str, slug: str, censor: int | None) -> dict:
    main, gridm = load(model, MAIN), load(model, slug)
    pids = tasks_of(main) & tasks_of(gridm)
    pm, pg = per_problem(main, pids, censor), per_problem(gridm, pids, censor)
    plist = sorted(pids)

    dfm, dfg = rate_df(list(pm.values())), rate_df(list(pg.values()))
    ci1 = boot_diff(pm, pg, rate_df, plist)
    passm, passg = rate_pass(list(pm.values())), rate_pass(list(pg.values()))
    ci2 = boot_diff(pm, pg, rate_pass, plist)
    # McNemar on majority-of-3 pass labels
    bm = np.array([1 if (pm[p]["df"] + pm[p]["repaired"]) * 2 >= pm[p]["n"] else 0
                   for p in plist])
    bg = np.array([1 if (pg[p]["df"] + pg[p]["repaired"]) * 2 >= pg[p]["n"] else 0
                   for p in plist])
    x = int(((bm == 1) & (bg == 0)).sum()); y = int(((bm == 0) & (bg == 1)).sum())
    mp = stats.binomtest(x, x + y, 0.5).pvalue if x + y else 1.0
    # Wilcoxon on pass counts (per problem, 0..3)
    cm = np.array([pm[p]["df"] + pm[p]["repaired"] for p in plist])
    cg = np.array([pg[p]["df"] + pg[p]["repaired"] for p in plist])
    nz = (cg - cm) != 0
    wp = float(stats.wilcoxon(cg[nz], cm[nz], zero_method="wilcox").pvalue) \
        if nz.sum() else 1.0
    wr = rank_biserial(cg, cm)

    return {"n": len(plist), "dfm": dfm, "dfg": dfg, "ci1": tuple(ci1),
            "passm": passm, "passg": passg, "ci2": tuple(ci2),
            "x": x, "y": y, "mp": mp, "wp": wp, "wr": wr}


def table(rows: list[tuple[str, dict]], label_pair) -> list[str]:
    pct = lambda v: f"{100*v:.1f}%"   # noqa: E731
    lines = [f"### {label_pair}", "",
             "| Model | n | det-free @gen main → grid | Δ (95% CI) | "
             "pass @horizon main → grid | Δ (95% CI) | McNemar x/y (p) | Wilcoxon (p, r) |",
             "|---|---:|---|---|---|---|---|---|"]
    for name, r in rows:
        if r is None:
            lines.append(f"| {name} | — | invalid (excluded) | | | | | |")
            continue
        lines.append(
            f"| {name} | {r['n']} | {pct(r['dfm'])} → {pct(r['dfg'])} | "
            f"{100*(r['dfg']-r['dfm']):+.1f}pp [{100*r['ci1'][0]:+.1f}, {100*r['ci1'][1]:+.1f}] | "
            f"{pct(r['passm'])} → {pct(r['passg'])} | "
            f"{100*(r['passg']-r['passm']):+.1f}pp [{100*r['ci2'][0]:+.1f}, {100*r['ci2'][1]:+.1f}] | "
            f"{r['x']}/{r['y']} ({r['mp']:.3g}) | p={r['wp']:.3g}, r={r['wr']:+.3f} |")
    lines.append("")
    return lines


def main() -> None:
    lines = ["# RQ4: sampling-parameter ablation (200-problem subset, full gate)",
             "",
             "Grid arms vs the main cell (t=1.0, p=1.0): temperature 0.2 and",
             "top_p 0.5, non-thinking, 3 samples per arm, problem-level pairing",
             "(200 problems; ids from manifest outcomes). Primary = common",
             "five-round censor on all arms; as-recorded = sensitivity.",
             "Models: DeepSeek V4 Pro, Gemini 3.1 Pro, GLM-5.1, Qwen Max",
             "(Kimi K3's host rejects sampling parameters; GPT-5.6 and Claude",
             "Fable 5 grid cells do not exist). DeepSeek's t0.2 cell fails the",
             "validity gate (heal_failed 158 > 50) and is excluded from tests.", ""]
    for tag, censor in (("Primary (common 5-round censor)", CENSOR),
                        ("Sensitivity (as-recorded outcomes)", None)):
        lines += [f"## {tag}", ""]
        for gname, slug in GRID.items():
            label = ("t=0.2 (vs t=1.0)" if gname == "t0.2"
                     else "top_p=0.5 (vs top_p=1.0)")
            rows = []
            for m in MODELS:
                try:
                    main = load(m, MAIN); grid = load(m, slug)
                except FileNotFoundError:
                    rows.append((NAME[m], None)); continue
                okm, _ = valid(main); okg, whyg = valid(grid)
                if not (okm and okg):
                    rows.append((NAME[m], None))
                    if not okg:
                        print(f"[skip] {m} {gname}: {whyg}", file=sys.stderr)
                    continue
                rows.append((NAME[m], compare(m, gname, slug, censor)))
            lines += table(rows, label)
    out = R / "rq4_sampling.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

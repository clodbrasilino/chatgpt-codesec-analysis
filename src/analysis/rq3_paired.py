"""RQ3 final paired analysis (two questions), with horizon symmetry.

Two corrections over the first pass:
  1. Pairing set: derived from the MANIFEST OUTCOMES, not from
     cell.tasks. The heal-repair reruns (--tasks <ids>) rewrote
     cell.tasks to the retried ids only (deepseek-thinking: 55/200)
     while keeping all 600 programs in outcomes.
  2. Common five-round censor: cells differ in recorded max_rounds
     (10 for the untouched cells, 5 for cells re-run after the budget
     cap). Programs recorded clean at round >5 exist in the 10-round
     cells (14-30 per arm in the subset). Primary statistic censors
     BOTH arms at 5 rounds (pass = clean_at_start, or clean with
     rounds_to_clean <= 5); the as-recorded variant is the sensitivity.

Unit = problem (200-task vulnerable-prone subset, 3 samples/arm):
  - cluster bootstrap over problems for rate differences
  - McNemar exact on majority-of-3 problem labels
  - Wilcoxon signed-rank on per-problem counts with rank-biserial r
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
B_SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
T_SLUG = "feedback-static+dynamic-r1-t1.0-p1.0"
CENSOR = 5
MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1"}
KEY_RE = re.compile(r"^problem-(\d+)(-s(\d+))?$")
RNG = np.random.default_rng(20260922)


def load(model: str, slug: str) -> dict:
    return json.load(open(R / model / f"{slug}.manifest.json"))


def tasks_of(man: dict) -> set[int]:
    """Task ids from OUTCOMES (cell.tasks can be narrowed by reruns)."""
    out = set()
    for k in man["outcomes"]:
        m = KEY_RE.match(k)
        if m:
            out.add(int(m.group(1)))
    return out


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
            if o == "clean":
                r = v.get("rounds_to_clean") or 0
                if censor is None or r <= censor:
                    acc[p]["repaired"] += 1
    return acc


def rate_df(accs):
    return sum(a["df"] for a in accs) / sum(a["n"] for a in accs)


def rate_repair(accs):
    fl = sum(a["flagged"] for a in accs)
    return sum(a["repaired"] for a in accs) / fl if fl else np.nan


def boot_diff(pb, pt, stat, plist, reps=10000):
    d = np.empty(reps)
    for i in range(reps):
        idx = RNG.integers(0, len(plist), len(plist))
        d[i] = stat([pt[plist[j]] for j in idx]) - stat([pb[plist[j]] for j in idx])
    return d


def rank_biserial(x, y):
    dd = x - y; dd = dd[dd != 0]
    ranks = rankdata(np.abs(dd))
    return (ranks[dd > 0].sum() - ranks[dd < 0].sum()) / ranks.sum()


def valid(man: dict) -> tuple[bool, str]:
    out = man["outcomes"]
    hf = sum(1 for v in out.values() if v.get("outcome") == "heal_failed")
    return (len(out) >= 100 and hf <= 50), f"n={len(out)}, heal_failed={hf}"


def analyze(model: str, censor: int | None) -> dict | None:
    try:
        base, think = load(model, B_SLUG), load(f"{model}-thinking", T_SLUG)
    except FileNotFoundError:
        return None
    ok_b, why_b = valid(base)
    ok_t, why_t = valid(think)
    if not (ok_b and ok_t):
        return {"model": model, "valid": False, "why": f"{why_b} / {why_t}"}
    pids = tasks_of(think) & tasks_of(base)
    plist = sorted(pids)
    pb, pt = per_problem(base, pids, censor), per_problem(think, pids, censor)

    dfb, dft = rate_df(list(pb.values())), rate_df(list(pt.values()))
    ci1 = np.percentile(boot_diff(pb, pt, rate_df, plist), [2.5, 97.5])
    b01 = np.array([1 if pb[p]["df"] >= 2 else 0 for p in plist])
    t01 = np.array([1 if pt[p]["df"] >= 2 else 0 for p in plist])
    mb = int(((b01 == 1) & (t01 == 0)).sum()); mc = int(((b01 == 0) & (t01 == 1)).sum())
    mp = stats.binomtest(mb, mb + mc, 0.5).pvalue if mb + mc else 1.0
    cb = np.array([pb[p]["df"] for p in plist]); ct = np.array([pt[p]["df"] for p in plist])
    nz = (ct - cb) != 0
    w1p = float(stats.wilcoxon(ct[nz], cb[nz], zero_method="wilcox").pvalue) if nz.sum() else 1.0
    r1 = rank_biserial(ct, cb)

    rb, rt = rate_repair(list(pb.values())), rate_repair(list(pt.values()))
    ci2 = np.percentile(boot_diff(pb, pt, rate_repair, plist), [2.5, 97.5])
    fb = sum(pb[p]["flagged"] for p in plist); ft = sum(pt[p]["flagged"] for p in plist)
    # overall pass (for reference)
    passb = (sum(pb[p]["df"] + pb[p]["repaired"] for p in plist)) / sum(pb[p]["n"] for p in plist)
    passt = (sum(pt[p]["df"] + pt[p]["repaired"] for p in plist)) / sum(pt[p]["n"] for p in plist)

    return {"model": model, "valid": True, "n": len(plist),
            "dfb": dfb, "dft": dft, "ci1": tuple(ci1), "mb": mb, "mc": mc,
            "mp": mp, "w1p": w1p, "r1": r1,
            "rb": rb, "rt": rt, "ci2": tuple(ci2), "fb": fb, "ft": ft,
            "passb": passb, "passt": passt}


def render(res: list[dict], censor: int | None, label: str) -> list[str]:
    pct = lambda x: f"{100*x:.1f}%"   # noqa: E731
    lines = [f"### {label}", "",
             "| Model | n problems | Q1 detection-free base→think | Δ | 95% CI | McNemar b/c (p) | Wilcoxon (p, r) |",
             "|---|---:|---|---:|---|---|---|---|"]
    for r in res:
        if not r["valid"]:
            lines.append(f"| {NAME[r['model']]} | — | invalid: {r['why']} | | | | |")
            continue
        lines.append(
            f"| {NAME[r['model']]} | {r['n']} | {pct(r['dfb'])} → {pct(r['dft'])} | "
            f"{100*(r['dft']-r['dfb']):+.1f}pp | [{100*r['ci1'][0]:+.1f}, {100*r['ci1'][1]:+.1f}] | "
            f"{r['mb']}/{r['mc']} (p={r['mp']:.3g}) | p={r['w1p']:.3g}, r={r['r1']:+.3f} |")
    lines += ["",
              "| Model | flagged base | flagged think | Q2 repair base→think | Δ | 95% CI | overall pass base→think |",
              "|---|---:|---:|---|---:|---|---|"]
    for r in res:
        if not r["valid"]:
            continue
        lines.append(
            f"| {NAME[r['model']]} | {r['fb']} | {r['ft']} | {pct(r['rb'])} → {pct(r['rt'])} | "
            f"{100*(r['rt']-r['rb']):+.1f}pp | [{100*r['ci2'][0]:+.1f}, {100*r['ci2'][1]:+.1f}] | "
            f"{pct(r['passb'])} → {pct(r['passt'])} |")
    return lines


def main() -> None:
    prim = [analyze(m, CENSOR) for m in MODELS]
    sens = [analyze(m, None) for m in MODELS]
    prim = [r for r in prim if r]
    sens = [r for r in sens if r]
    lines = ["# RQ3 final paired analysis (problem-level, full gate)", "",
             f"200-task vulnerable-prone subset (task ids from manifest "
             f"outcomes), 3 samples per arm, horizon = {CENSOR} rounds with a "
             "COMMON censor applied to both arms (primary). Sensitivity: "
             "as-recorded outcomes (cells differ in recorded budget).", ""]
    lines += render(prim, CENSOR, "Primary (common 5-round censor)")
    lines += [""] + render(sens, None, "Sensitivity (as-recorded outcomes)")
    out = R / "rq3_paired_final.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

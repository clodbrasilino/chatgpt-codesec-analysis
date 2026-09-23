"""Pre-registered significance tests for the cross-model consistency analysis.

Unit = problem (974), label = majority-of-3 samples flagged at
generation (round 0, outcome != clean_at_start), main cells.

Tests (as pre-registered in the paper TODO):
  1. Cochran's Q over the 7 models (binary labels, df = 6).
  2. Pairwise exact McNemar on discordant problem pairs, 21 pairs,
     Holm-corrected.
  3. Wilson 95% CIs for each model's majority-flagged share.
  4. Cohen's g effect size per pairwise contrast.

Output: results/consistency_tests.md + .json
"""
from __future__ import annotations

import itertools
import json
import re
import sys
from pathlib import Path

import numpy as np
from scipy import stats

sys.path.insert(0, str(REPO := Path(__file__).resolve().parents[2]))

R = REPO / "results"
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1", "qwen-max", "claude-fable-5"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max",
        "claude-fable-5": "Claude Fable 5"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")


def labels(model: str) -> dict[int, int]:
    """majority-of-3 flagged label per problem."""
    man = json.load(open(R / model / f"{MAIN}.manifest.json"))["outcomes"]
    per = {}
    for k, v in man.items():
        m = KEY_RE.match(k)
        if not m:
            continue
        p = int(m.group(1))
        flagged = v.get("outcome") != "clean_at_start"
        per.setdefault(p, []).append(1 if flagged else 0)
    return {p: 1 if sum(v) >= 2 else 0 for p, v in per.items()}


def wilson(k: int, n: int, z: float = 1.959963985) -> tuple[float, float]:
    ph = k / n
    d = 1 + z**2 / n
    c = (ph + z**2 / (2 * n)) / d
    h = z * np.sqrt(ph * (1 - ph) / n + z**2 / (4 * n**2)) / d
    return c - h, c + h


def cochrans_q(mat: np.ndarray) -> tuple[float, float, int]:
    """mat: N problems x k models of 0/1. Manual Cochran's Q."""
    n, k = mat.shape
    col = mat.sum(axis=0)
    row = mat.sum(axis=1)
    num = (k - 1) * (k * (col**2).sum() - col.sum() ** 2)
    den = k * col.sum() - (row**2).sum()
    q = num / den
    p = float(stats.chi2.sf(q, k - 1))
    return float(q), p, k - 1


def holm(pvals: list[float]) -> list[float]:
    order = np.argsort(pvals)
    m = len(pvals)
    adj = [0.0] * m
    run = 0.0
    for rank, i in enumerate(order):
        run = max(run, min(1.0, (m - rank) * pvals[i]))
        adj[i] = run
    return adj


def main() -> None:
    lab = {m: labels(m) for m in MODELS}
    pids = sorted(set.intersection(*[set(v) for v in lab.values()]))
    mat = np.array([[lab[m][p] for m in MODELS] for p in pids], dtype=int)
    n = len(pids)

    L = ["# Cross-model consistency: pre-registered significance tests", "",
         f"Unit = problem (n = {n}); label = majority-of-3 samples flagged",
         "at generation (round 0, main cells).", ""]

    # 1. Cochran's Q
    q, qp, df = cochrans_q(mat)
    flagged = mat.sum(axis=0)
    L += ["## Cochran's Q (7 models)", "",
          f"Q = {q:.2f}, df = {df}, p = {qp:.3g}.", ""]

    # 2. Wilson CIs per model
    L += ["## Per-model majority-flagged share with Wilson 95% CIs", "",
          "| Model | flagged (majority) | share | Wilson 95% CI |", "|---|---:|---:|---|"]
    wil = {}
    for i, m in enumerate(MODELS):
        k_ = int(flagged[i])
        lo, hi = wilson(k_, n)
        wil[m] = (k_, k_ / n, lo, hi)
        L.append(f"| {NAME[m]} | {k_} | {100*k_/n:.1f}% | "
                 f"[{100*lo:.1f}%, {100*hi:.1f}%] |")

    # 3. Pairwise exact McNemar + Holm + Cohen's g
    rows = []
    for a, b in itertools.combinations(MODELS, 2):
        ba = np.array([lab[a][p] for p in pids])
        bb = np.array([lab[b][p] for p in pids])
        x = int(((ba == 1) & (bb == 0)).sum())   # a flags, b does not
        y = int(((ba == 0) & (bb == 1)).sum())   # b flags, a does not
        pv = float(stats.binomtest(x, x + y, 0.5).pvalue) if x + y else 1.0
        g = (y - x) / (x + y) / 2 if x + y else 0.0   # + : b flags more
        rows.append((a, b, x, y, pv, g))
    adj = holm([r[4] for r in rows])
    L += ["", "## Pairwise exact McNemar (21 pairs, Holm-adjusted)", "",
          "| Pair | a-only | b-only | raw p | Holm p | Cohen's g | sig. |",
          "|---|---:|---:|---:|---:|---:|---|"]
    sig = []
    for (a, b, x, y, pv, g), pa in zip(rows, adj):
        mark = "yes" if pa < 0.05 else "no"
        if pa < 0.05:
            sig.append((NAME[a], NAME[b], pa, g))
        L.append(f"| {NAME[a]} vs {NAME[b]} | {x} | {y} | {pv:.3g} | "
                 f"{pa:.3g} | {g:+.3f} | {mark} |")

    L += ["", f"Holm-adjusted significant pairs: {len(sig)} of 21.", ""]
    for a, b, pa, g in sorted(sig, key=lambda t: -abs(t[3])):
        L.append(f"- {a} vs {b}: p = {pa:.3g}, Cohen's g = {g:+.3f}")

    json.dump({"n_problems": n, "cochrans_q": {"Q": q, "df": df, "p": qp},
               "wilson": {m: wil[m] for m in MODELS},
               "pairs": [{"a": a, "b": b, "a_only": x, "b_only": y,
                          "p_raw": pv, "p_holm": pa, "g": g}
                         for (a, b, x, y, pv, g), pa in zip(rows, adj)]},
              open(R / "consistency_tests.json", "w"), indent=1)
    (R / "consistency_tests.md").write_text("\n".join(L) + "\n")
    print(f"Cochran Q={q:.2f} p={qp:.3g}; sig pairs {len(sig)}/21")
    print(f"written -> {R / 'consistency_tests.md'}")


if __name__ == "__main__":
    main()

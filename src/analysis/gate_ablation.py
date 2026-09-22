"""Gate-usage ablation (P4): static-only vs dynamic-only vs full gate.

Arms (non-thinking, r0, t=1.0/p=1.0, 200-problem vulnerable-prone
subset, 3 samples/problem):
  static-only : feedback-static-r0-t1.0-p1.0        (974-task cell,
                restricted to the subset; generated independently)
  dynamic-only: feedback-dynamic-r0-t1.0-p1.0       (600 programs;
                round-0 code IMPORTED from the static-only cell via
                gen_source, so static vs dynamic compares IDENTICAL
                round-0 code under different feedback channels)
  full gate   : feedback-static+dynamic-r0-t1.0-p1.0 (independent
                generations; restricted to the subset)

Comparisons:
  A. static-only vs dynamic-only -- PROGRAM-level pairing (same
     round-0 code), the clean channel-isolation contrast.
  B. static-only vs full gate -- problem-level pairing (independent
     generations), as in RQ3.

Statistics: common five-round censor on both arms (primary; cells
record max_rounds=10 but the configured analysis horizon is 5),
as-recorded outcomes as sensitivity. McNemar exact on paired pass
labels, cluster bootstrap (10k resamples of problems) for rate
differences. Unit of resampling: the problem.

Output: results/gate_ablation.md
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

import numpy as np
from scipy import stats

REPO = Path(__file__).resolve().parents[2]
R = REPO / "results"
S_SLUG = "feedback-static-r0-t1.0-p1.0"
D_SLUG = "feedback-dynamic-r0-t1.0-p1.0"
F_SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
CENSOR = 5
MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1", "qwen-max", "claude-fable-5"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max",
        "claude-fable-5": "Claude Fable 5"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
RNG = np.random.default_rng(20260922)
CLEAN = {"clean_at_start", "clean"}


def load(model: str, slug: str) -> dict:
    return json.load(open(R / model / f"{slug}.manifest.json"))


def pass_of(v: dict, censor: int | None) -> bool:
    o = v.get("outcome")
    if o == "clean_at_start":
        return True
    if o == "clean":
        return censor is None or (v.get("rounds_to_clean") or 0) <= censor
    return False


def prog_map(man: dict, pids: set[int], censor: int | None) -> dict[str, bool]:
    """program base -> pass (subset only)."""
    out = {}
    for k, v in man["outcomes"].items():
        m = KEY_RE.match(k)
        if m and int(m.group(1)) in pids:
            out[k] = pass_of(v, censor)
    return out


def prob_map(man: dict, pids: set[int], censor: int | None) -> dict[int, bool]:
    """problem -> majority-of-3 pass."""
    acc: dict[int, list] = {p: [] for p in pids}
    for k, v in man["outcomes"].items():
        m = KEY_RE.match(k)
        if m and int(m.group(1)) in pids:
            acc[int(m.group(1))].append(pass_of(v, censor))
    return {p: (sum(v) >= 2) for p, v in acc.items() if v}


def cluster_boot(pb: dict, pa: dict, plist: list[int], reps=10000):
    """bootstrap CI of pass-rate diff (B - A), resampling problems."""
    d = np.empty(reps)
    for i in range(reps):
        idx = RNG.integers(0, len(plist), len(plist))
        d[i] = (np.mean([pb[plist[j]] for j in idx])
                - np.mean([pa[plist[j]] for j in idx]))
    return np.percentile(d, [2.5, 97.5])


def mcnemar(a: list, b: list) -> tuple[int, int, float]:
    av = np.array(a, int); bv = np.array(b, int)
    x = int(((av == 1) & (bv == 0)).sum())   # A passes, B not
    y = int(((av == 0) & (bv == 1)).sum())   # B passes, A not
    p = stats.binomtest(x, x + y, 0.5).pvalue if x + y else 1.0
    return x, y, float(p)


def comp_program_level(model: str, censor: int | None) -> dict | None:
    """A: static-only vs dynamic-only on IDENTICAL round-0 code."""
    s_man, d_man = load(model, S_SLUG), load(model, D_SLUG)
    pd_ = set()
    for k in d_man["outcomes"]:
        m = KEY_RE.match(k)
        if m:
            pd_.add(int(m.group(1)))
    s_map = prog_map(s_man, pd_, censor)
    d_map = prog_map(d_man, pd_, censor)
    common = sorted(set(s_map) & set(d_map))
    if not common:
        return None
    # cluster by problem
    plist = sorted({int(KEY_RE.match(k).group(1)) for k in common})
    by_prob = {p: ([], []) for p in plist}
    for k in common:
        p = int(KEY_RE.match(k).group(1))
        by_prob[p][0].append(s_map[k])
        by_prob[p][1].append(d_map[k])
    a = []; b = []
    for p in plist:
        a.append(all(by_prob[p][0]) if False else sum(by_prob[p][0]) / len(by_prob[p][0]))
        b.append(sum(by_prob[p][1]) / len(by_prob[p][1]))
    x, y, p = mcnemar([v >= 0.5 for v in a], [v >= 0.5 for v in b])
    # bootstrap on problem-level pass shares
    da = np.empty(10000)
    for i in range(10000):
        idx = RNG.integers(0, len(plist), len(plist))
        da[i] = np.mean([b[j] for j in idx]) - np.mean([a[j] for j in idx])
    ci = np.percentile(da, [2.5, 97.5])
    return {"n_prog": len(common), "n_prob": len(plist),
            "a": float(np.mean(a)), "b": float(np.mean(b)),
            "x": x, "y": y, "p": p, "ci": tuple(ci)}


def comp_problem_level(model: str, arm_b: str, arm_a: str,
                       censor: int | None) -> dict | None:
    """B: full gate vs static-only (independent generations)."""
    man_b = load(model, arm_b)
    man_a = load(model, arm_a)
    pids = set()
    for k in man_b["outcomes"]:
        m = KEY_RE.match(k)
        if m:
            pids.add(int(m.group(1)))
    pb = prob_map(man_b, pids, censor)
    pa = prob_map(man_a, pids, censor)
    plist = sorted(set(pb) & set(pa))
    if not plist:
        return None
    b = [pb[p] for p in plist]; a = [pa[p] for p in plist]
    x, y, p = mcnemar(a, b)
    ci = cluster_boot(pb, pa, plist)
    return {"n_prob": len(plist), "b": float(np.mean(b)), "a": float(np.mean(a)),
            "x": x, "y": y, "p": p, "ci": tuple(ci)}


def fmt(r, label_pair) -> list[str]:
    if r is None:
        return [f"| {label_pair} | — | | | | |"]
    pct = lambda v: f"{100*v:.1f}%"   # noqa: E731
    return [f"| {label_pair} | {pct(r['a'])} → {pct(r['b'])} | "
            f"{100*(r['b']-r['a']):+.1f}pp | [{100*r['ci'][0]:+.1f}, {100*r['ci'][1]:+.1f}] | "
            f"{r['x']}/{r['y']} | {r['p']:.3g} |"]


def main() -> None:
    lines = ["# Gate-usage ablation (P4): static-only vs dynamic-only vs full gate",
             "",
             "Non-thinking arms, 200-problem vulnerable-prone subset, 3 samples",
             "per problem, five-round horizon with a COMMON censor on both arms",
             "(primary; as-recorded sensitivity at the end). Dynamic-only cells",
             "import the round-0 code of the static-only cells (gen_source), so",
             "comparison A holds the code fixed and varies only the feedback",
             "channel; comparison B pairs problems across independently",
             "generated arms.", ""]
    for tag, censor in (("Primary (common 5-round censor)", CENSOR),
                        ("Sensitivity (as-recorded outcomes)", None)):
        lines += [f"## {tag}", ""]
        lines += ["### A. static-only vs dynamic-only (same round-0 code)",
                  "",
                  "| Model | pass static-only → dynamic-only | Δ | 95% CI | McNemar x/y | p |",
                  "|---|---|---:|---|---|---|"]
        for m in MODELS:
            r = comp_program_level(m, censor)
            lines += fmt(r, NAME[m])
        lines += ["",
                  "### B. static-only vs full gate (independent generations)",
                  "",
                  "| Model | pass static-only → full gate | Δ | 95% CI | McNemar x/y | p |",
                  "|---|---|---:|---|---|---|"]
        for m in MODELS:
            r = comp_problem_level(m, F_SLUG, S_SLUG, censor)
            lines += fmt(r, NAME[m])
        lines += ["",
                  "### C. dynamic-only vs full gate (independent generations)",
                  "",
                  "| Model | pass dynamic-only → full gate | Δ | 95% CI | McNemar x/y | p |",
                  "|---|---|---:|---|---|---|"]
        for m in MODELS:
            r = comp_problem_level(m, F_SLUG, D_SLUG, censor)
            lines += fmt(r, NAME[m])
        lines += ["", "x = first arm passes / second does not; y = reverse.", ""]
    out = R / "gate_ablation.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

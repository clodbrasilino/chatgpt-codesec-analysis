"""RQ2 paired contrast: static+dynamic vs static feedback on the vulnerable subset.

Compares, for the same model and the same 200-task vulnerable subset:
  - the RQ1 cell (feedback=static,  measure=static,  3 samples/task), and
  - the RQ2 key cell (feedback=static+dynamic, measure=static+dynamic, 2 samples/task)

Because the cells draw different numbers of samples per task, pairing is done at
the problem level (per-problem binary clean outcome and mean rounds-to-clean).

Pre-registered tests (config/experiment.yaml -> analysis.tests.rq2_rq3):
  mcnemar, wilcoxon_signed_rank, effect_size_r, bootstrap_ci  (alpha = 0.05)

Caveats recorded in the report:
  - GATE ASYMMETRY: RQ1 "clean" = clean under the static gate only; RQ2 "clean" =
    clean under the stricter static+dynamic gate. The contrast therefore measures
    whether adding dynamic findings to the feedback loop lets the model reach the
    stricter bar, NOT whether the produced code is equally secure.
  - Samples differ (3 vs 2 per task); per-problem aggregation absorbs this.
  - Single model (default qwen-max); repeat per model as key cells complete.

Usage:
    python -m src.analysis.rq2_paired [--model qwen-max]
"""

from __future__ import annotations

import argparse
import re
from collections import Counter
from pathlib import Path

import numpy as np
from scipy import stats as sps

from src.pipeline.comment_inject import (
    DYNAMIC_SUFFIXES,
    STATIC_SUFFIXES,
    extract_standard_messages,
    get_problems_weaknesses,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS = REPO_ROOT / "results"
CLEAN_OUTCOMES = {"clean_at_start", "clean"}

_KEY_RE = re.compile(r"^problem-(\d+)(-s\d+)?$")


def load_manifest(cell_slug: str, model: str) -> dict:
    path = RESULTS / model / f"{cell_slug}.manifest.json"
    return {
        "cell": path.name.removesuffix(".manifest.json"),
        "data": _load(path),
        "path": path,
    }


def _load(path: Path) -> dict:
    import json

    with open(path) as f:
        return json.load(f)


def _per_problem(outcomes: dict, pids: set[int], penalty: float) -> dict[int, dict]:
    """Aggregate per-sample outcomes to per-problem clean flag and mean rounds."""
    acc: dict[int, dict] = {pid: {"clean": [], "rounds": []} for pid in pids}
    for key, rec in outcomes.items():
        m = _KEY_RE.match(key)
        if not m:
            continue
        pid = int(m.group(1))
        if pid not in acc:
            continue
        outcome = rec["outcome"] if isinstance(rec, dict) else rec
        rounds = rec.get("rounds_to_clean", 0) if isinstance(rec, dict) else 0
        acc[pid]["clean"].append(outcome in CLEAN_OUTCOMES)
        acc[pid]["rounds"].append(rounds if outcome in CLEAN_OUTCOMES else penalty)
    return {
        pid: {
            "clean": all(v["clean"]) if v["clean"] else False,
            "rounds": float(np.mean(v["rounds"])) if v["rounds"] else penalty,
            "n": len(v["clean"]),
        }
        for pid, v in acc.items()
    }


def _count_flags(report_path: Path) -> int:
    """Findings with line > 0 in one report file (canonical pipeline parse)."""
    if not report_path.is_file():
        return 0
    text = report_path.read_text(errors="replace")
    return sum(1 for m in extract_standard_messages(text) if m["line"] > 0)


def _final_healed_dir(cell_root: Path) -> Path:
    """Highest-numbered heal_N/healed dir with a healed .c in it — the round
    whose reports are the last word on still-flagged samples."""
    best = cell_root / "heal_0"
    for d in sorted(
        cell_root.glob("heal_*"),
        key=lambda p: int(p.name.split("_")[1]) if p.name.split("_")[-1].isdigit() else -1,
    ):
        h = d / "healed"
        if h.is_dir() and any(h.glob("*.c")):
            best = h
    return best


def sticky_channel_breakdown(final_dir: Path, stems: list[str]) -> dict:
    """Which channels still flag each not_cleaned sample in the final round dir."""
    static_findings = get_problems_weaknesses(str(final_dir), STATIC_SUFFIXES)
    dyn_findings = get_problems_weaknesses(str(final_dir), DYNAMIC_SUFFIXES)
    rows: dict[str, dict] = {}
    for stem in stems:
        flags: dict[str, int] = {}
        for suffix in STATIC_SUFFIXES + DYNAMIC_SUFFIXES:
            n = _count_flags(final_dir / f"{stem}{suffix}")
            if n:
                flags[suffix] = n
        static_hit = stem in static_findings
        dyn_hit = stem in dyn_findings
        rows[stem] = {
            "flags": flags,
            "class": "both" if static_hit and dyn_hit
            else "static_only" if static_hit
            else "dynamic_only" if dyn_hit else "none",
        }
    return rows


def analyze(model: str = "qwen-max") -> Path:
    rq1 = load_manifest("feedback-static-r0-t1.0-p1.0", model)
    rq2 = load_manifest("feedback-static+dynamic-r0-t1.0-p1.0", model)
    pids = set(rq2["data"]["cell"]["tasks"])
    max_rounds = int(rq2["data"]["cell"]["max_rounds"])
    penalty = max_rounds + 1.0

    per1 = _per_problem(rq1["data"]["outcomes"], pids, penalty)
    per2 = _per_problem(rq2["data"]["outcomes"], pids, penalty)
    common = sorted(pid for pid in pids if pid in per1 and per1[pid]["n"] and per2[pid]["n"])

    clean1 = np.array([per1[p]["clean"] for p in common], dtype=int)
    clean2 = np.array([per2[p]["clean"] for p in common], dtype=int)
    rounds1 = np.array([per1[p]["rounds"] for p in common])
    rounds2 = np.array([per2[p]["rounds"] for p in common])

    # ---- McNemar (exact binomial on discordant pairs) ----
    b = int(np.sum((clean1 == 1) & (clean2 == 0)))  # static clean, s+d not
    c = int(np.sum((clean1 == 0) & (clean2 == 1)))  # static not, s+d clean
    if b + c > 0:
        mcnemar_p = float(sps.binomtest(b, b + c, 0.5).pvalue)
    else:
        mcnemar_p = 1.0

    # ---- Wilcoxon signed-rank on penalized rounds-to-clean ----
    diff = rounds2 - rounds1  # >0 means s+d cell needed more rounds
    nonzero = diff != 0
    wilcoxon_p, effect_r, n_eff = float("nan"), float("nan"), 0
    if nonzero.sum() > 0:
        n_eff = int(nonzero.sum())
        try:
            res = sps.wilcoxon(rounds2[nonzero], rounds1[nonzero], zero_method="wilcox")
            wilcoxon_p = float(res.pvalue)
            z = sps.norm.isf(wilcoxon_p / 2) if 0 < wilcoxon_p < 1 else 0.0
            effect_r = float(np.sign(np.mean(diff[nonzero])) * abs(z) / np.sqrt(n_eff))
        except ValueError:
            wilcoxon_p = 1.0

    # ---- Sensitivity: problems clean under BOTH gates ----
    both = (clean1 == 1) & (clean2 == 1)
    sens_p = float("nan")
    if both.sum() > 0 and np.any(rounds2[both] != rounds1[both]):
        sens = sps.wilcoxon(rounds2[both], rounds1[both], zero_method="wilcox")
        sens_p = float(sens.pvalue)

    # ---- Bootstrap CI for the paired per-problem clean-rate difference ----
    rng = np.random.default_rng(20260831)
    paired_diff = clean2 - clean1
    boots = np.array([
        paired_diff[rng.integers(0, len(paired_diff), len(paired_diff))].mean()
        for _ in range(10_000)
    ])
    ci_lo, ci_hi = np.percentile(boots, [2.5, 97.5])

    # ---- Descriptives (per-sample level, subset-restricted) ----
    def _desc(per: dict, outcomes: dict) -> dict:
        sub = {k: v for k, v in outcomes.items() if _KEY_RE.match(k) and int(_KEY_RE.match(k).group(1)) in pids}
        counts = Counter(
            (v["outcome"] if isinstance(v, dict) else v) for v in sub.values()
        )
        n = sum(counts.values())
        final_clean = counts.get("clean_at_start", 0) + counts.get("clean", 0)
        return {
            "n": n, "counts": dict(counts),
            "initial_clean": counts.get("clean_at_start", 0) / n if n else float("nan"),
            "final_clean": final_clean / n if n else float("nan"),
        }

    d1 = _desc(per1, rq1["data"]["outcomes"])
    d2 = _desc(per2, rq2["data"]["outcomes"])

    # ---- Sticky findings: channels still flagging the not_cleaned samples ----
    not_cleaned = sorted(
        k for k, v in rq2["data"]["outcomes"].items()
        if _KEY_RE.match(k)
        and int(_KEY_RE.match(k).group(1)) in pids
        and (v["outcome"] if isinstance(v, dict) else v) == "not_cleaned"
    )
    cell_root = REPO_ROOT / rq2["data"]["cell"]["root"] / model / rq2["cell"]
    final_dir = _final_healed_dir(cell_root)
    sticky = sticky_channel_breakdown(final_dir, not_cleaned)
    classes = Counter(v["class"] for v in sticky.values())
    suffix_counts = Counter(
        s for v in sticky.values() for s in v["flags"]
    )

    # ---------------- report ----------------
    lines = [
        "# RQ2 paired contrast: static+dynamic vs static feedback",
        "",
        f"Model: **{model}** — vulnerable subset, top-200 ranked problems "
        f"(n = {len(common)} paired problems).",
        f"Generated: 2026-09-01 (pre-registered tests: mcnemar, wilcoxon_signed_rank, "
        "effect_size_r, bootstrap_ci; alpha = 0.05).",
        "",
        "## Cells",
        "",
        "| Cell | Feedback | Measure | Samples/task | n (samples) |",
        "|---|---|---|---|---|",
        f"| RQ1 | static | static | 3 | {d1['n']} |",
        f"| RQ2 key | static+dynamic | static+dynamic | 2 | {d2['n']} |",
        "",
        "## Descriptives (per-sample, restricted to the 200 tasks)",
        "",
        "| Metric | RQ1 static | RQ2 static+dynamic |",
        "|---|---|---|",
        f"| Clean at start | {d1['initial_clean']:.1%} | {d2['initial_clean']:.1%} |",
        f"| Final clean | {d1['final_clean']:.1%} | {d2['final_clean']:.1%} |",
        f"| Outcome counts | {d1['counts']} | {d2['counts']} |",
        "",
        f"Not-cleaned penalty for rounds-to-clean: {penalty:.0f} (max_rounds + 1).",
        "",
        "## Pre-registered tests (per-problem pairing, n = %d)" % len(common),
        "",
        f"- **McNemar (exact)** on problem-level clean: b = {b} "
        f"(static clean, s+d not), c = {c} (static not, s+d clean), "
        f"p = {mcnemar_p:.4g}",
        f"- **Wilcoxon signed-rank** on penalized rounds-to-clean "
        f"(n_eff = {n_eff} non-zero pairs): p = {wilcoxon_p:.4g}",
        f"- **Effect size r** = {effect_r:+.3f} "
        "(>0 = s+d cell needs MORE rounds; includes the gate-asymmetry effect)",
        f"- **Bootstrap 95% CI** for paired clean-rate difference "
        f"(s+d − static): [{ci_lo:+.3f}, {ci_hi:+.3f}]",
    ]
    if not np.isnan(sens_p):
        lines.append(
            f"- Sensitivity — Wilcoxon on problems clean under both gates "
            f"(n = {int(both.sum())}): p = {sens_p:.4g}"
        )
    lines += [
        "",
        "## Sticky findings: what still flags the "
        f"{len(not_cleaned)} not_cleaned samples (final round reports)",
        "",
        f"- Channel class: {dict(classes)}",
        f"- Non-empty finding reports by tool: {dict(suffix_counts)}",
        "",
        "## Caveats",
        "",
        "1. **Gate asymmetry** — RQ1 'clean' means static-gate clean only; RQ2 'clean' "
        "means clean under the stricter static+dynamic gate. The contrast tests whether "
        "dynamic feedback helps the model reach the stricter bar; it does not claim the "
        "RQ1 outputs are equally defect-free.",
        "2. Samples per task differ (3 vs 2); pairing is per-problem.",
        "3. Single model; repeat per model as key cells complete.",
        "",
    ]

    out = RESULTS / "rq2_paired_report.md"
    out.write_text("\n".join(lines))

    print(f"[rq2_paired] problems paired: {len(common)}")
    print(f"[rq2_paired] McNemar b={b} c={c} p={mcnemar_p:.4g}")
    print(f"[rq2_paired] Wilcoxon p={wilcoxon_p:.4g} r={effect_r:+.3f}")
    print(f"[rq2_paired] bootstrap CI [{ci_lo:+.3f}, {ci_hi:+.3f}]")
    print(f"[rq2_paired] sticky classes: {dict(classes)}")
    print(f"[rq2_paired] report -> {out}")
    return out


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="RQ2 paired contrast")
    parser.add_argument("--model", default="qwen-max")
    args = parser.parse_args()
    analyze(args.model)

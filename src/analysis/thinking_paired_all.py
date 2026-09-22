"""RQ3: thinking vs non-thinking paired contrast, all 5 toggle-verified models.

Extends thinking_paired.py (deepseek-only, static-only) to the full
ablation design:

  models : deepseek-v4-pro, openai-gpt56-sol, gemini-3-pro, kimi-k3,
           glm-5.1  (the 5 with verified reasoning toggles; Qwen has no
           thinking variant, Claude cannot disable reasoning)
  arms   : static-only  base feedback-static-r0-t1.0-p1.0
                        think feedback-static-r1-t1.0-p1.0
           full gate    base feedback-static+dynamic-r0-t1.0-p1.0
                        think feedback-static+dynamic-r1-t1.0-p1.0
  subset : the 200-task vulnerable-prone subset (top-200 of
           results/vulnerable_subset.csv); 3 samples per task on BOTH
           sides (600 programs per thinking cell)

Protocol:
  - horizon: config-driven cap via src.config (max_rounds recorded in
    manifests is 10 but the analysis horizon is the configured 5; the
    not-cleaned penalty follows not_cleaned_penalty()).
  - primary pairing: sample-1 vs sample-1 (pre-registered).
  - sensitivity: all-3-samples-clean bar on BOTH sides (symmetric,
    available because the thinking cells also carry 3 samples).
  - tests: McNemar exact, Wilcoxon signed-rank on penalized
    rounds-to-clean, effect size r, bootstrap 95% CI of the clean-rate
    difference (pre-registered in config/experiment.yaml, alpha 0.05).
  - manifest validity gate: n >= 100 outcomes and heal_failed <= 50;
    invalid cells are reported but excluded from the tests.
  - usage: exact per-call ledgers, base side filtered to the subset
    task ids; per-problem token and latency multipliers.

Output: results/thinking_paired_all.md
"""
from __future__ import annotations

import json
import sys
from collections import Counter
from pathlib import Path

import numpy as np

from src.config import max_healing_rounds
from src.analysis.grid_paired import (
    _all_samples_per_problem,
    _load,
    _paired_tests,
    _sample1_per_problem,
)

REPO = Path(__file__).resolve().parents[2]
RESULTS = REPO / "results"

MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1"]
CONFIGS = [
    ("static-only", "feedback-static-r0-t1.0-p1.0",
     "feedback-static-r1-t1.0-p1.0"),
    ("full gate", "feedback-static+dynamic-r0-t1.0-p1.0",
     "feedback-static+dynamic-r1-t1.0-p1.0"),
]

DISPATCH_NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
                 "openai-gpt56-sol": "GPT-5.6",
                 "gemini-3-pro": "Gemini 3.1 Pro",
                 "kimi-k3": "Kimi K3",
                 "glm-5.1": "GLM-5.1"}


def manifest_valid(man: dict) -> tuple[bool, str]:
    out = man["outcomes"]
    n = len(out)
    hf = sum(1 for v in out.values() if v.get("outcome") == "heal_failed")
    if n < 100:
        return False, f"n={n} < 100 (dry-run)"
    if hf > 50:
        return False, f"heal_failed={hf} > 50 (transient transport failures)"
    return True, f"n={n}, heal_failed={hf}"


def usage_subset(model: str, slug: str, task_ids: set[int]) -> dict | None:
    """Ledger usage restricted to the subset tasks (both models get the
    same restriction, so per-problem multipliers are comparable)."""
    f = RESULTS / model / f"{slug}.usage.jsonl"
    if not f.is_file():
        return None
    ok = 0
    fail = 0
    in_tok = out_tok = reason_tok = 0
    lat = []
    for line in open(f):
        try:
            c = json.loads(line)
        except json.JSONDecodeError:
            continue
        if int(c.get("task_id", -1)) not in task_ids:
            continue
        if c.get("ok"):
            ok += 1
            in_tok += c.get("prompt_tokens") or 0
            out_tok += c.get("completion_tokens") or 0
            reason_tok += c.get("reasoning_tokens") or 0
            lat.append(c.get("latency_s") or 0)
        else:
            fail += 1
    return {"ok": ok, "fail": fail, "in": in_tok, "out": out_tok,
            "reason": reason_tok,
            "mean_lat": sum(lat) / max(len(lat), 1)}


def analyze_config(model: str, label: str, base_slug: str,
                   think_slug: str) -> list[str]:
    base = _load(RESULTS / model / f"{base_slug}.manifest.json")
    think = _load(RESULTS / f"{model}-thinking" / f"{think_slug}.manifest.json")
    lines: list[str] = [f"### {DISPATCH_NAME[model]} — {label}", ""]
    if base is None or think is None:
        lines += ["Missing manifest — skipped.", ""]
        return lines

    ok_b, why_b = manifest_valid(base)
    ok_t, why_t = manifest_valid(think)
    lines.append(f"Base `{base_slug}`: {why_b}. Thinking `{think_slug}`: {why_t}.")

    pids = set(int(t) for t in think["cell"]["tasks"])
    cap = max_healing_rounds(manifest_max_rounds=int(think["cell"]["max_rounds"]))
    penalty = float(cap + 1)

    counts_t = Counter(v.get("outcome") for v in think["outcomes"].values())
    counts_b_sub = Counter()
    for k, v in base["outcomes"].items():
        pid = int(k.split("-s")[0].replace("problem-", ""))
        if pid in pids:
            counts_b_sub[v.get("outcome")] += 1
    n_prog = sum(counts_b_sub.values())

    def rates(c: Counter, denom: int) -> tuple[float, float]:
        cs = c.get("clean_at_start", 0) + c.get("clean", 0)
        return c.get("clean_at_start", 0) / denom, cs / denom

    b_df, b_pass = rates(counts_b_sub, n_prog)
    t_df, t_pass = rates(counts_t, len(think["outcomes"]))
    lines += [
        "",
        "| arm | programs | detection-free @gen | pass @horizon | "
        "clean | not_cleaned | heal_failed |",
        "|---|---:|---:|---:|---:|---:|---:|",
        f"| base (subset) | {n_prog} | {b_df:.1%} | {b_pass:.1%} | "
        f"{counts_b_sub.get('clean', 0)} | {counts_b_sub.get('not_cleaned', 0)} | "
        f"{counts_b_sub.get('heal_failed', 0)} |",
        f"| thinking | {len(think['outcomes'])} | {t_df:.1%} | {t_pass:.1%} | "
        f"{counts_t.get('clean', 0)} | {counts_t.get('not_cleaned', 0)} | "
        f"{counts_t.get('heal_failed', 0)} |",
        "",
    ]

    if not (ok_b and ok_t):
        lines += ["**Excluded from paired tests** (validity gate).", ""]
        return lines

    base_s1 = _sample1_per_problem(base["outcomes"], pids, penalty)
    think_s1 = _sample1_per_problem(think["outcomes"], pids, penalty)
    base_all = _all_samples_per_problem(base["outcomes"], pids, penalty)
    think_all = _all_samples_per_problem(think["outcomes"], pids, penalty)
    common = sorted(p for p in pids if p in base_s1 and p in think_s1)
    n = len(common)
    if n == 0:
        lines += ["No paired problems.", ""]
        return lines

    def tests(a: dict, b: dict) -> dict:
        ca = np.array([a[p]["clean"] for p in common], dtype=int)
        cb = np.array([b[p]["clean"] for p in common], dtype=int)
        ra = np.array([a[p]["rounds"] for p in common])
        rb = np.array([b[p]["rounds"] for p in common])
        return _paired_tests(ca, cb, ra, rb)

    t1 = tests(base_s1, think_s1)
    tall = tests(base_all, think_all)

    lines += [
        f"Paired problems: n = {n} (sample-1; horizon = {cap} rounds, "
        f"penalty = {penalty:.0f}).",
        "",
        f"- **McNemar (exact)**: b = {t1['b']} (base pass, thinking not), "
        f"c = {t1['c']} (reverse), p = {t1['mcnemar_p']:.4g}",
        f"- **Wilcoxon** on penalized rounds-to-clean (n_eff = {t1['n_eff']}): "
        f"p = {t1['wilcoxon_p']:.4g}, effect r = {t1['effect_r']:+.3f} "
        f"(>0 = thinking needs more rounds)",
        f"- **Bootstrap 95% CI** pass-rate difference (thinking − base): "
        f"[{t1['ci'][0]:+.3f}, {t1['ci'][1]:+.3f}]",
        f"- Sensitivity (all-3-samples bar, both arms): McNemar b = {tall['b']}, "
        f"c = {tall['c']}, p = {tall['mcnemar_p']:.4g}; "
        f"Wilcoxon p = {tall['wilcoxon_p']:.4g}, r = {tall['effect_r']:+.3f}; "
        f"CI [{tall['ci'][0]:+.3f}, {tall['ci'][1]:+.3f}]",
        "",
    ]
    return lines


def usage_block() -> list[str]:
    lines = ["## Usage contrast (exact ledgers, subset-restricted)", "",
             "Per-problem = totals over the 200-task subset divided by 600 "
             "programs (3 samples x 200 tasks). Base ledgers filtered to the "
             "same task ids.", "",
             "| Model | config | calls ok/fail | prompt tok | completion tok | "
             "reasoning tok | ms/call | out tok/program |",]
    # header row fix below (table assembled manually)
    lines = ["## Usage contrast (exact ledgers, subset-restricted)", "",
             "Base ledgers filtered to the 200 subset task ids; thinking "
             "ledgers cover the subset by construction.",
             "",
             "| Model | Config | ok/fail calls | prompt tok | completion tok "
             "| reasoning tok | mean s/call | completion tok/program |",
             "|---|---|---:|---:|---:|---:|---:|---:|"]
    for model in MODELS:
        for label, base_slug, think_slug in CONFIGS:
            think_man = _load(RESULTS / f"{model}-thinking" / f"{think_slug}.manifest.json")
            if think_man is None:
                continue
            pids = set(int(t) for t in think_man["cell"]["tasks"])
            ub = usage_subset(model, base_slug, pids)
            ut = usage_subset(f"{model}-thinking", think_slug, pids)
            if not ub or not ut or not ub["ok"] or not ut["ok"]:
                lines.append(f"| {DISPATCH_NAME[model]} | {label} | ledger missing | "
                             "| | | | | |")
                continue
            per_prog = ut["out"] / 600
            lines.append(
                f"| {DISPATCH_NAME[model]} | {label} | {ub['ok']}/{ub['fail']} vs "
                f"{ut['ok']}/{ut['fail']} | {ub['in']:,} vs {ut['in']:,} | "
                f"{ub['out']:,} vs {ut['out']:,} | {ub['reason']:,} vs "
                f"{ut['reason']:,} | {ub['mean_lat']:.1f} vs {ut['mean_lat']:.1f} | "
                f"{per_prog:,.0f} |")
    lines.append("")
    return lines


def main() -> None:
    lines = ["# Thinking vs non-thinking paired contrast (5 toggle-verified "
             "models, 200-task vulnerable-prone subset)",
             "",
             "Subset: top-200 of `results/vulnerable_subset.csv` (ranked by "
             "generation findings, CWE-tool pairs, healing depth). Both arms: "
             "3 samples/task, t=1.0/p=1.0. Base = reasoning off (r0; Gemini "
             "base = lowest available level), thinking = reasoning on (r1). "
             "Horizon: configured 5 rounds. Pre-registered tests: McNemar "
             "exact, Wilcoxon signed-rank, effect size r, bootstrap CI "
             "(alpha 0.05).", ""]
    for label, base_slug, think_slug in CONFIGS:
        lines += [f"## {label}", ""]
        for model in MODELS:
            lines += analyze_config(model, label, base_slug, think_slug)
    lines += usage_block()
    out = RESULTS / "thinking_paired_all.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

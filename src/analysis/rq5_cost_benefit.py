"""RQ5 rewrite: cost-benefit analysis (generation vs repair, per model,
per ablation). Failed calls are an engineering concern and are excluded
from the scientific cost figures (they carry zero token cost; see
results/rq5_cost_dynamics.md for the reconciliation).

Metrics per cell:
  generation tokens  : estimated (char-based, ~3.6 chars/token) -- the
                       ledgers record repair ('heal') calls only.
  repair tokens      : exact ledger (ok calls only).
  pass @horizon      : manifest pass (common 5-round censor).
  cost to fix        : repair tokens per passed program.
  time               : mean and total repair-call latency (exact).

Comparisons:
  A. models (main cells, full population, 7 models).
  B. gate usage (200-problem subset: static-only vs dynamic-only vs
     full gate; cost-benefit against the common full-gate criterion).
  C. thinking (5 models, full-gate r1, subset).
  D. sampling (4 models: t0.2, p0.5 vs main).

Output: results/rq5_cost_benefit.md
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

sys.path.insert(0, str(REPO := Path(__file__).resolve().parents[2]))
from src.analysis.usage_report import (          # noqa: E402
    aggregate_ledger, estimate_cell, ledger_keys)
from src.pipeline.run_experiment import _load_tasks  # noqa: E402

R = REPO / "results"
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
S_SLUG = "feedback-static-r0-t1.0-p1.0"
D_SLUG = "feedback-dynamic-r0-t1.0-p1.0"
CENSOR = 5
MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1", "qwen-max", "claude-fable-5"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max",
        "claude-fable-5": "Claude Fable 5"}
THINK = {"deepseek-v4-pro": "deepseek-v4-pro-thinking",
         "openai-gpt56-sol": "openai-gpt56-sol-thinking",
         "gemini-3-pro": "gemini-3-pro-thinking",
         "kimi-k3": "kimi-k3-thinking", "glm-5.1": "glm-5.1-thinking"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
PROG = json.load(open(R / "cross_eval_common_criterion.json"))


def manifest(model: str, slug: str = MAIN) -> dict:
    p = R / model / f"{slug}.manifest.json"
    if not p.is_file():
        p = R / f"{model}" / f"{slug}.manifest.json"
    return json.load(open(p))


def pass_count(model: str, slug: str, pids: set[int] | None = None) -> int:
    man = manifest(model, slug)
    n = 0
    for k, v in man["outcomes"].items():
        if pids is not None:
            m = KEY_RE.match(k)
            if not m or int(m.group(1)) not in pids:
                continue
        o = v.get("outcome")
        if o == "clean_at_start" or (o == "clean"
                                     and (v.get("rounds_to_clean") or 0) <= CENSOR):
            n += 1
    return n


def repair_stats(model: str, slug: str, pids: set[int] | None = None) -> dict:
    """Exact repair-ledger stats, optionally restricted to subset tasks."""
    led = aggregate_ledger(model, slug)
    out = {"tok": led["prompt_tokens"] + led["completion_tokens"],
           "calls": led["calls"], "lat_mean": led.get("mean_latency_s"),
           "lat_total": led.get("total_latency_s")}
    if pids is not None:
        ok = [json.loads(l) for l in open(R / model / f"{slug}.usage.jsonl")]
        ok = [c for c in ok if c.get("ok") and c.get("task_id") in pids]
        out["tok"] = sum((c.get("prompt_tokens") or 0)
                         + (c.get("completion_tokens") or 0) for c in ok)
        lats = [c.get("latency_s") or 0 for c in ok]
        out["lat_mean"] = (sum(lats) / len(lats)) if lats else None
        out["lat_total"] = sum(lats)
        out["calls"] = len(ok)
    return out


def gen_estimate(model: str, slug: str, tasks: dict) -> int:
    """Estimated generation tokens (round-0; heals are ledger-covered)."""
    est = estimate_cell(model, slug, tasks, covered=ledger_keys(model, slug))
    return est.get("prompt_tokens", 0) + est.get("completion_tokens", 0)


def subset_pids(model: str) -> set[int]:
    man = manifest(model, D_SLUG)
    return {int(m.group(1)) for k in man["outcomes"] if (m := KEY_RE.match(k))}


def fmt_row(name, gen_pp, rep_pp, n, passes, lat_mean, lat_total, gen_note="") -> str:
    cpp = rep_tok_per_pass = rep_pp * n / passes if passes else float("nan")
    spp = (lat_total / passes) if (lat_total and passes) else float("nan")
    return (f"| {name} | {gen_pp:,.0f} | {rep_pp:,.0f} | {100*passes/n:.1f}% | "
            f"{cpp:,.0f} | {lat_mean:.1f} | {spp:.1f} |"), cpp, spp


def main() -> None:
    tasks = {t["id"]: t["text"] for t in _load_tasks()}
    lines = ["# RQ5: cost-benefit analysis (generation vs repair; models and ablations)",
             "",
             "Failed calls are excluded from the scientific cost figures (zero",
             "token cost; engineering concern -- see rq5_cost_dynamics.md for",
             "the reconciliation). Generation tokens are estimates (~3.6",
             "chars/token); repair tokens are exact ledger (ok calls).",
             "Cost to fix = repair tokens per passed program.",
             ""]

    # ---------------- A. models (main cells, full population) ----------------
    lines += ["## A. Models (main cells, full population)",
              "",
              "| Model | gen tok/prog (est) | repair tok/prog | pass @horizon | "
              "repair tok per pass | mean repair latency (s) | repair s per pass |",
              "|---|---:|---:|---:|---:|---:|---:|"]
    for m in MODELS:
        led = aggregate_ledger(m, MAIN)
        rep_tok = led["prompt_tokens"] + led["completion_tokens"]
        gen_tok = gen_estimate(m, MAIN, tasks)
        n = len(manifest(m)["outcomes"])
        passes = pass_count(m, MAIN)
        row, _, _ = fmt_row(NAME[m], gen_tok / n, rep_tok / n, n, passes,
                            led.get("mean_latency_s") or 0, led.get("total_latency_s") or 0)
        lines.append(row)

    # ---------------- B. gate usage (subset, common criterion) --------------
    lines += ["",
              "## B. Gate usage (200-problem subset; cost-benefit against the",
              "## common full-gate criterion from the cross-evaluation)",
              "",
              "| Model / arm | repair tok/prog | pass (common crit) | repair tok per common-crit pass | mean latency (s) |",
              "|---|---:|---:|---:|---:|"]
    for m in MODELS:
        pids = subset_pids(m)
        cc = PROG[m]
        for arm, slug, cc_pass in (
                ("static-only", S_SLUG, None),
                ("dynamic-only", D_SLUG, None),
                ("full gate", MAIN, cc["f_pass"])):
            st = repair_stats(m, slug, pids)
            rep_pp = st["tok"] / 600
            if cc_pass is None:
                # static/dynamic arms: full-criterion pass = own pass AND
                # cross-channel clean (from the cross-evaluation)
                if arm == "static-only":
                    cc_pass = cc["s_dc_fuzz"]
                else:
                    cc_pass = cc["d_sc"]
            cpp = st["tok"] / cc_pass if cc_pass else float("nan")
            lines.append(f"| {NAME[m]} / {arm} | {rep_pp:,.0f} | {cc_pass} ({100*cc_pass/600:.1f}%) | "
                         f"{cpp:,.0f} | {st['lat_mean']:.1f} |")

    # ---------------- C. thinking (subset, full-gate r1) --------------------
    lines += ["",
              "## C. Thinking ablation (full-gate cells, 200-problem subset)",
              "",
              "| Model | arm | repair tok/prog | pass @horizon | repair tok per pass |",
              "|---|---|---:|---:|---:|"]
    for m, tm in THINK.items():
        pids = subset_pids(m)
        for label, model, slug in ((f"{NAME[m]} base", m, MAIN),
                                   (f"{NAME[m]} thinking", tm,
                                    "feedback-static+dynamic-r1-t1.0-p1.0")):
            st = repair_stats(model, slug, pids)
            passes = pass_count(model, slug, pids)
            cpp = st["tok"] / passes if passes else float("nan")
            lines.append(f"| {label} | {st['tok']/600:,.0f} | {passes} ({100*passes/600:.1f}%) | {cpp:,.0f} |")

    # ---------------- D. sampling (subset, full-gate r0) --------------------
    lines += ["",
              "## D. Sampling ablation (full-gate cells, 200-problem subset)",
              "",
              "| Model | arm | repair tok/prog | pass @horizon | repair tok per pass |",
              "|---|---|---:|---:|---:|"]
    for m in ("deepseek-v4-pro", "gemini-3-pro", "glm-5.1", "qwen-max"):
        pids = subset_pids(m)
        for label, slug in (("t=1.0 p=1.0", MAIN),
                            ("t=0.2 p=1.0", "feedback-static+dynamic-r0-t0.2-p1.0"),
                            ("t=1.0 p=0.5", "feedback-static+dynamic-r0-t1.0-p0.5")):
            try:
                st = repair_stats(m, slug, pids)
                passes = pass_count(m, slug, pids)
            except FileNotFoundError:
                continue
            cpp = st["tok"] / passes if passes else float("nan")
            lines.append(f"| {NAME[m]} {label} | {st['tok']/600:,.0f} | {passes} ({100*passes/600:.1f}%) | {cpp:,.0f} |")

    lines += ["",
              "## Caveats",
              "",
              "- Gemini 3.1 Pro's ledger covers only part of its main run",
              "  (1,110 of 2,922 programs): its per-program costs are",
              "  underestimates.",
              "- Tokens-per-pass in the gate-usage comparison counts",
              "  detection-free passes, which cost zero repair tokens; the",
              "  dynamic-only arm's low tokens-per-pass largely reflects that",
              "  selection (49% common-criterion pass, mostly detection-free).",
              "- DeepSeek's t=0.2 cell fails the validity gate (heal_failed",
              "  158 > 50); its row is indicative only.",
              "- Generation tokens are estimates (no generation ledger)."]
    out = R / "rq5_cost_benefit.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

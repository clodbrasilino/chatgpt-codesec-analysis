"""RQ5: USD cost calculation from the official pricing + exact ledgers.

FX: 1 USD = 6.7459 CNY (PBOC/CFETS central parity, 2026-09-22; market
band 6.696-6.701 the same day). CNY-native models (Kimi, GLM, Qwen)
converted at parity.

Costing rules (documented in results/model_pricing_official.md):
- cost = prompt_tokens x in_rate + completion_tokens x out_rate;
  reasoning tokens are a SUBSET of completion_tokens (verified on every
  ledger: reasoning never exceeds completion) and bill as output, so
  using completion alone is exact -- no double counting.
- cache-hit input is not recorded in the ledgers -> all input billed at
  the cache-MISS rate (conservative upper bound).
- DeepSeek peak = 2x off-peak; runs executed Beijing daytime -> both
  bounds computed, peak as primary for DeepSeek rows.
- generation tokens are ESTIMATES (~3.6 chars/token; ledgers record
  repair calls only), costed with the estimated prompt/completion split.

Stats: per-program cost distributions report mean (= average), std
(sample, ddof=1) and median across programs.
Output: results/rq5_usd_costs.md
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

import numpy as np

sys.path.insert(0, str(REPO := Path(__file__).resolve().parents[2]))
from src.analysis.usage_report import (          # noqa: E402
    aggregate_ledger, estimate_cell, ledger_keys)
from src.pipeline.run_experiment import _load_tasks  # noqa: E402

R = REPO / "results"
FX = 6.7459                      # CNY per USD, PBOC parity 2026-09-22
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

# per-1M-token USD prices (in, out); CNY-native converted at FX
P = {"deepseek-v4-pro":      {"in": 1.32, "out": 3.96, "cur": "USD",
                              "in_op": 0.66, "out_op": 1.98},   # peak / off-peak
     "openai-gpt56-sol":     {"in": 5.00, "out": 30.00, "cur": "USD"},
     "gemini-3-pro":         {"in": 2.00, "out": 12.00, "cur": "USD"},
     "kimi-k3":              {"in": 20.0 / FX, "out": 100.0 / FX, "cur": "CNY"},
     "glm-5.1":              {"in": 6.0 / FX, "out": 24.0 / FX, "cur": "CNY"},
     "qwen-max":             {"in": 2.4 / FX, "out": 9.6 / FX, "cur": "CNY"},
     "claude-fable-5":       {"in": 10.00, "out": 50.00, "cur": "USD"}}


def manifest(model: str, slug: str = MAIN) -> dict:
    return json.load(open(R / model / f"{slug}.manifest.json"))


def pass_count(model: str, slug: str, pids: set[int] | None = None) -> int:
    n = 0
    for k, v in manifest(model, slug)["outcomes"].items():
        if pids is not None:
            m = KEY_RE.match(k)
            if not m or int(m.group(1)) not in pids:
                continue
        o = v.get("outcome")
        if o == "clean_at_start" or (o == "clean"
                                     and (v.get("rounds_to_clean") or 0) <= CENSOR):
            n += 1
    return n


def usd(prompt: int | float, completion: int | float, model: str,
        peak: bool = True) -> float:
    pr = P[model.replace("-thinking", "")]
    i = pr["in"] if (peak or "in_op" not in pr) else pr["in_op"]
    o = pr["out"] if (peak or "out_op" not in pr) else pr["out_op"]
    return (prompt * i + completion * o) / 1e6


def usd_split(model: str, slug: str, pids: set[int] | None = None,
              peak: bool = True) -> dict:
    """Exact repair USD: total, per-program list (ALL manifest programs,
    zeros included for detection-free / uncovered programs), latency."""
    led_by_key: dict[str, float] = {}
    lat = []
    fp = R / model / f"{slug}.usage.jsonl"
    if fp.is_file():
        for line in open(fp):
            c = json.loads(line)
            if not c.get("ok"):
                continue
            tid, smp = c.get("task_id"), int(c.get("sample") or 1)
            try:
                tid = int(tid)
            except (TypeError, ValueError):
                continue
            if pids is not None and tid not in pids:
                continue
            u = usd(c.get("prompt_tokens") or 0, c.get("completion_tokens") or 0,
                    model, peak)
            key = f"problem-{tid}" if smp <= 1 else f"problem-{tid}-s{smp}"
            led_by_key[key] = led_by_key.get(key, 0.0) + u
            lat.append(c.get("latency_s") or 0)
    # align to the manifest's program population (zeros included)
    per_prog: list[float] = []
    for k in manifest(model, slug)["outcomes"]:
        m = KEY_RE.match(k)
        if not m:
            continue
        if pids is not None and int(m.group(1)) not in pids:
            continue
        per_prog.append(led_by_key.get(k, 0.0))
    total = sum(led_by_key.values())
    return {"total": total, "per_prog": per_prog,
            "lat_mean": (sum(lat) / len(lat)) if lat else 0.0,
            "lat_total": sum(lat)}


def gen_usd(model: str, slug: str, tasks: dict, peak: bool = True) -> float:
    est = estimate_cell(model, slug, tasks, covered=ledger_keys(model, slug))
    return usd(est.get("prompt_tokens", 0), est.get("completion_tokens", 0),
               model, peak)


def gen_usd_exact(model: str, slug: str, peak: bool = True) -> float:
    """Exact generation cost where the ledger records generate calls."""
    fp = R / model / f"{slug}.usage.jsonl"
    if not fp.is_file():
        return 0.0
    total = 0.0
    for line in open(fp):
        c = json.loads(line)
        if c.get("kind") != "generate" or not c.get("ok"):
            continue
        total += usd(c.get("prompt_tokens") or 0,
                     c.get("completion_tokens") or 0, model, peak)
    return total


def subset_pids(model: str) -> set[int]:
    return {int(m.group(1)) for k in manifest(model, D_SLUG)["outcomes"]
            if (m := KEY_RE.match(k))}


def stats_row(vals) -> str:
    a = np.asarray(vals, float)
    return f"{a.mean():.3f} / {a.std(ddof=1):.3f} / {np.median(a):.3f}"


def main() -> None:
    tasks = {t["id"]: t["text"] for t in _load_tasks()}
    L = ["# RQ5: USD costs (official pricing + exact ledgers)", "",
         f"FX: 1 USD = {FX} CNY (PBOC/CFETS central parity, 2026-09-22;",
         "market band 6.696-6.701 the same day). CNY-native models (Kimi,",
         "GLM, Qwen) converted at parity. Costing: prompt x in-rate +",
         "completion x out-rate (reasoning tokens are a subset of",
         "completion and bill as output -- verified on every ledger row).",
         "All input billed at the cache-MISS rate (ledgers do not record",
         "cache hits; conservative upper bound). DeepSeek: peak = 2x",
         "off-peak; runs executed Beijing daytime, peak used for DeepSeek",
         "rows (off-peak bound noted). Generation tokens are estimates",
         "(~3.6 chars/token). Per-program stats: mean / std / median.",
         "", "## USD prices used (per 1M tokens)", "",
         "| Model | in $/M | out $/M | native |", "|---|---:|---:|---|"]
    for m in MODELS:
        pr = P[m]
        if m == "deepseek-v4-pro":
            L.append(f"| {NAME[m]} | {pr['in']:.2f} (peak) / {pr['in_op']:.2f} (off) "
                     f"| {pr['out']:.2f} / {pr['out_op']:.2f} | USD |")
        else:
            L.append(f"| {NAME[m]} | {pr['in']:.3f} | {pr['out']:.2f} | {pr['cur']} |")

    # ---------- A. models (main cells) ----------
    L += ["", "## A. Models (main cells, full population, repair = exact ledger,",
          "generation = estimate)", "",
          "| Model | repair $/prog mean/std/median | gen est $/prog | total $/prog "
          "| pass @horizon | cost to fix ($/pass) | repair s/pass | total $ (cell) |",
          "|---|---|---:|---:|---:|---:|---:|---:|"]
    tot_all = {}
    rows_a = {}
    for m in MODELS:
        man = manifest(m)
        n = len(man["outcomes"])
        passes = pass_count(m, MAIN)
        rep = usd_split(m, MAIN, peak=True)
        gen = gen_usd(m, MAIN, tasks, peak=True)
        pp = np.asarray(rep["per_prog"], float)
        gen_pp = gen / n
        fix = rep["total"] / passes if passes else float("nan")
        sp_pass = rep["lat_total"] / passes if passes else float("nan")
        tot = rep["total"] + gen
        tot_all[m] = tot
        rows_a[m] = dict(rep_pp=rep["total"] / n, gen_pp=gen_pp,
                         fix=fix, passes=passes, n=n)
        L.append(f"| {NAME[m]} | {stats_row(pp)} | {gen_pp:.4f} | "
                 f"{rep['total']/n + gen_pp:.4f} | {passes} ({100*passes/n:.1f}%) "
                 f"| {fix:.3f} | {sp_pass:.1f} | {tot:,.0f} |")
    for metric, key in (("repair $/prog", "rep_pp"), ("cost to fix $/pass", "fix")):
        vals = [rows_a[m][key] for m in MODELS]
        a = np.asarray(vals, float)
        L.append(f"| **across models ({metric})** | mean {a.mean():.3f}, std {a.std(ddof=1):.3f}, "
                 f"median {np.median(a):.3f}, min {a.min():.3f}, max {a.max():.3f} | | | | | | |")
    grand = sum(tot_all.values())
    L.append(f"| **ALL MODELS total (repair + gen est)** | | | | | | | **${grand:,.0f}** |")
    ds_op = usd_split("deepseek-v4-pro", MAIN, peak=False)["total"] + \
        gen_usd("deepseek-v4-pro", MAIN, tasks, peak=False)
    L.append(f"\nDeepSeek off-peak bound: cell total ${ds_op:,.0f} (vs "
             f"${tot_all['deepseek-v4-pro']:,.0f} at peak).")

    # ---------- B. gate usage ----------
    L += ["", "## B. Gate usage (200-problem subset): USD per common-criterion pass", "",
          "| Model / arm | repair $/prog | common-crit pass | $ per common-crit pass |",
          "|---|---:|---:|---:|"]
    for m in MODELS:
        pids = subset_pids(m)
        cc = PROG[m]
        for arm, slug, cc_pass in (
                ("static-only", S_SLUG, cc["s_dc_fuzz"]),
                ("dynamic-only", D_SLUG, cc["d_sc"]),
                ("full gate", MAIN, cc["f_pass"])):
            st = usd_split(m, slug, pids, peak=True)
            cpp = st["total"] / cc_pass if cc_pass else float("nan")
            L.append(f"| {NAME[m]} / {arm} | {st['total']/600:.4f} | {cc_pass} "
                     f"({100*cc_pass/600:.1f}%) | {cpp:.3f} |")

    # ---------- C. thinking ----------
    L += ["", "## C. Thinking ablation (subset): USD per pass and marginal USD per", "## additional pass", "",
          "| Model | arm | $/prog | pass | $/pass | marginal $/add. pass |", "|---|---|---:|---:|---:|---:|"]
    for m, tm in THINK.items():
        pids = subset_pids(m)
        cells = {}
        for label, model, slug in (("base", m, MAIN),
                                   ("thinking", tm, "feedback-static+dynamic-r1-t1.0-p1.0")):
            st = usd_split(model, slug, pids, peak=(m == "deepseek-v4-pro"))
            passes = pass_count(model, slug, pids)
            cells[label] = (st, passes)
        (sb, pb), (stt, pt) = cells["base"], cells["thinking"]
        mb = sb["total"] / pb if pb else float("nan")
        mt = stt["total"] / pt if pt else float("nan")
        marg = ((stt["total"] - sb["total"]) / (pt - pb)) if pt != pb else float("nan")
        L.append(f"| {NAME[m]} | base | {sb['total']/600:.4f} | {pb} | {mb:.3f} | |")
        L.append(f"| {NAME[m]} | thinking | {stt['total']/600:.4f} | {pt} | {mt:.3f} | {marg:.2f} |")

    # ---------- D. sampling ----------
    L += ["", "## D. Sampling ablation (subset): USD per pass", "",
          "| Model | arm | $/prog | pass | $/pass |", "|---|---|---:|---:|---:|"]
    for m in ("deepseek-v4-pro", "gemini-3-pro", "glm-5.1", "qwen-max"):
        pids = subset_pids(m)
        for label, slug in (("t=1.0 p=1.0", MAIN),
                            ("t=0.2 p=1.0", "feedback-static+dynamic-r0-t0.2-p1.0"),
                            ("t=1.0 p=0.5", "feedback-static+dynamic-r0-t1.0-p0.5")):
            fp = R / m / f"{slug}.manifest.json"
            if not fp.is_file():
                continue
            st = usd_split(m, slug, pids, peak=(m == "deepseek-v4-pro"))
            passes = pass_count(m, slug, pids)
            cpp = st["total"] / passes if passes else float("nan")
            L.append(f"| {NAME[m]} | {label} | {st['total']/600:.4f} | {passes} | {cpp:.3f} |")

    # ---------- A2. every cell as its own row (thinking separated) ----------
    SUB = "feedback-static+dynamic-r1-t1.0-p1.0"   # thinking full-gate slug
    GSUB = "feedback-static-r1-t1.0-p1.0"          # thinking generation slug
    L += ["", "## A2. Every cell separately: non-thinking vs thinking arms", "",
          "Non-thinking rows are the main cells restricted to the same",
          "200-problem subset as the thinking cells (600 programs), so the",
          "arms are comparable; Qwen Max and Claude Fable 5 have no",
          "thinking variant; Gemini 3.1 Pro's contrast is reasoning",
          "low -> medium (its reasoning cannot be disabled). Generation is",
          "EXACT for the thinking arms (their ledgers record generate",
          "calls) and estimated for the non-thinking cells", "",
          "| Cell | n | repair $/prog mean/std/median | gen est $/prog | pass @horizon | $/pass | s/pass | cell $ |",
          "|---|---:|---|---:|---:|---:|---:|---:|"]
    order = [("qwen-max", None), ("claude-fable-5", None),
             ("deepseek-v4-pro", "deepseek-v4-pro-thinking"),
             ("openai-gpt56-sol", "openai-gpt56-sol-thinking"),
             ("gemini-3-pro", "gemini-3-pro-thinking"),
             ("kimi-k3", "kimi-k3-thinking"),
             ("glm-5.1", "glm-5.1-thinking")]
    for m, tm in order:
        pids = subset_pids(m)
        st = usd_split(m, MAIN, pids, peak=(m == "deepseek-v4-pro"))
        passes = pass_count(m, MAIN, pids)
        gen = gen_usd(m, MAIN, tasks, peak=(m == "deepseek-v4-pro")) * 600 / \
            len(manifest(m)["outcomes"])   # prorate cell-wide gen estimate
        pp = np.asarray(st["per_prog"], float)
        fix = st["total"] / passes if passes else float("nan")
        spp = st["lat_total"] / passes if passes else float("nan")
        L.append(f"| {NAME[m]} (non-thinking) | 600 | {stats_row(pp)} | "
                 f"{gen/600:.4f} | {passes} ({100*passes/600:.1f}%) | "
                 f"{fix:.3f} | {spp:.1f} | {st['total']+gen:,.0f} |")
        if tm:
            stt = usd_split(tm, SUB, peak=(m == "deepseek-v4-pro"))
            passes_t = pass_count(tm, SUB)
            gen_t = gen_usd_exact(tm, GSUB, peak=(m == "deepseek-v4-pro"))
            ppt = np.asarray(stt["per_prog"], float)
            fix_t = stt["total"] / passes_t if passes_t else float("nan")
            spp_t = stt["lat_total"] / passes_t if passes_t else float("nan")
            L.append(f"| {NAME[m]} (thinking) | 600 | {stats_row(ppt)} | "
                     f"{gen_t/600:.4f} | {passes_t} ({100*passes_t/600:.1f}%) | "
                     f"{fix_t:.3f} | {spp_t:.1f} | {stt['total']+gen_t:,.0f} |")

    L += ["", "## Caveats", "",
         "- Gemini 3.1 Pro's ledger covers only 1,110 of 2,922 programs:",
         "  its cell total and per-program costs are underestimates.",
         "- All input at cache-miss rates (no cache fields in ledgers):",
         "  upper bound; providers with high hit rates (Kimi, Qwen, GLM,",
         "  Claude) bill less in practice.",
         "- DeepSeek rows use PEAK rates (daytime runs); off-peak halves",
         "  them. Routed via DashScope -- the actual bill may differ from",
         "  vendor list prices (see model_pricing_official.md).",
         "- Generation costs are estimates (~3.6 chars/token), spread",
         "  uniformly per program; per-program std reflects repair only."]
    out = R / "rq5_usd_costs.md"
    out.write_text("\n".join(L) + "\n")
    print(f"written -> {out}")


if __name__ == "__main__":
    sys.exit(main())

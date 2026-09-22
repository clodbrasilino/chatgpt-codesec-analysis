"""RQ5: cost and execution-time dynamics (main cells, full population).

Per model (7 models, main cells, 974 tasks x 3 samples, non-thinking):

1. Ledger reconciliation: exact repair-call ledger -- ok vs failed
   calls. Failed calls carry no token cost (verified: token fields are
   None on every failed entry), so retries cost attempts and latency
   only; all token spend sits on ok calls.
2. Per-outcome attribution: ledger spend joined per program
   (task_id, sample) to the manifest outcome as recorded (pass =
   clean_at_start | clean; not-passed = not_cleaned | heal_failed);
   tokens per program per group.
3. Dynamics: per-round fix rate (hazard) of the repair loop.
4. Kaplan-Meier of rounds-to-pass with administrative censoring at the
   configured 5-round horizon (not-passed programs censored at 5), and
   log-rank tests: overall across the 7 models plus pairwise with Holm
   correction (pre-registered: kaplan_meier, logrank).

Outputs: results/rq5_cost_dynamics.md, results/rq5_km.pdf/.png,
results/rq5_km.json
"""
from __future__ import annotations

import json
import re
import sys
from itertools import combinations
from pathlib import Path

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt

REPO = Path(__file__).resolve().parents[2]
R = REPO / "results"
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
CENSOR = 5
MODELS = ["deepseek-v4-pro", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "glm-5.1", "qwen-max", "claude-fable-5"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max",
        "claude-fable-5": "Claude Fable 5"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
COLORS = ["#4c72b0", "#dd8452", "#55a868", "#c44e52",
          "#8172b3", "#937860", "#da8bc3"]


def ledger(model: str) -> list[dict]:
    f = R / model / f"{MAIN}.usage.jsonl"
    return [json.loads(l) for l in open(f)]


def manifest(model: str) -> dict:
    return json.load(open(R / model / f"{MAIN}.manifest.json"))


def reconcile(model: str) -> dict:
    lines = ledger(model)
    ok = [l for l in lines if l["ok"]]
    fail = [l for l in lines if not l["ok"]]
    tok = lambda k: sum(l.get(k) or 0 for l in ok)   # noqa: E731
    lat_ok = [l.get("latency_s") or 0 for l in ok]
    lat_fail = [l.get("latency_s") or 0 for l in fail]
    return {"calls_ok": len(ok), "calls_fail": len(fail),
            "prompt": tok("prompt_tokens"), "completion": tok("completion_tokens"),
            "reasoning": tok("reasoning_tokens"),
            "lat_mean": sum(lat_ok) / max(len(lat_ok), 1),
            "lat_fail_total": sum(lat_fail),
            "fail_tok_billed": sum((l.get("prompt_tokens") or 0)
                                   + (l.get("completion_tokens") or 0)
                                   for l in fail)}


def outcome_groups(model: str) -> tuple[dict[str, str], set[int]]:
    man = manifest(model)
    pids = {int(m.group(1)) for k in man["outcomes"] if (m := KEY_RE.match(k))}
    group: dict[str, str] = {}
    for k, v in man["outcomes"].items():
        if KEY_RE.match(k):
            group[k] = ("pass" if v.get("outcome") in ("clean_at_start", "clean")
                        else "notpass")
    return group, pids


def per_outcome_tokens(model: str, group: dict[str, str], pids: set[int]) -> dict:
    acc = {"pass": [0, 0], "notpass": [0, 0]}   # [tokens, programs]
    per_prog: dict[str, int] = {}
    for l in ledger(model):
        if not l["ok"]:
            continue
        tid = l.get("task_id")
        s = l.get("sample") or 1
        k = f"problem-{tid}" if int(s) <= 1 else f"problem-{tid}-s{int(s)}"
        if k not in group:
            continue
        tk = (l.get("prompt_tokens") or 0) + (l.get("completion_tokens") or 0)
        per_prog[k] = per_prog.get(k, 0) + tk
    for k, t in per_prog.items():
        g = group[k]
        acc[g][0] += t
        acc[g][1] += 1
    return {"pass_tok_per_prog": acc["pass"][0] / max(acc["pass"][1], 1),
            "notpass_tok_per_prog": acc["notpass"][0] / max(acc["notpass"][1], 1),
            "n_pass": acc["pass"][1], "n_notpass": acc["notpass"][1]}


def rounds_data(model: str) -> list[tuple[int, bool]]:
    """(round-of-pass censored at CENSOR, passed?) per program."""
    man = manifest(model)
    pids = {int(m.group(1)) for k in man["outcomes"] if (m := KEY_RE.match(k))}
    out = []
    for k, v in man["outcomes"].items():
        if not (m := KEY_RE.match(k)) or int(m.group(1)) not in pids:
            continue
        o = v.get("outcome")
        if o == "clean_at_start":
            out.append((0, True))
        elif o == "clean":
            r = v.get("rounds_to_clean") or CENSOR
            out.append((min(r, CENSOR), r <= CENSOR))
        else:
            out.append((CENSOR, False))
    return out


def km(data: list[tuple[int, bool]]) -> tuple[list[int], list[float]]:
    surv = [1.0]
    xs = [0]
    s = 1.0
    for r in range(1, CENSOR + 1):
        at_risk = sum(1 for rr, ev in data if rr >= r)
        events = sum(1 for rr, ev in data if rr == r and ev)
        if at_risk:
            s *= 1 - events / at_risk
        xs.append(r)
        surv.append(s)
    return xs, surv


def logrank(data_a: list, data_b: list) -> float:
    """Mantel-Cox log-rank between two groups (discrete rounds 1..5)."""
    chi = 0.0
    for r in range(1, CENSOR + 1):
        n1 = sum(1 for rr, _ in data_a if rr >= r)
        n2 = sum(1 for rr, _ in data_b if rr >= r)
        if n1 + n2 == 0:
            continue
        d1 = sum(1 for rr, ev in data_a if rr == r and ev)
        d2 = sum(1 for rr, ev in data_b if rr == r and ev)
        d = d1 + d2
        n = n1 + n2
        e1 = d * n1 / n
        var = d * (n1 / n) * (n2 / n) * (n - d) / (n - 1) if n > 1 else 0
        chi += (d1 - e1) ** 2 / var if var else 0
    from scipy import stats as sps
    return float(sps.chi2.sf(chi, 1))


def main() -> None:
    rec, attr, kmdata = {}, {}, {}
    for m in MODELS:
        rec[m] = reconcile(m)
        group, pids = outcome_groups(m)
        attr[m] = per_outcome_tokens(m, group, pids)
        kmdata[m] = rounds_data(m)
        print(f"done {m}", file=sys.stderr)

    # ---------------- report ----------------
    lines = ["# RQ5: cost and execution-time dynamics (main cells, full population)",
             "",
             "Exact repair-call ledgers; horizon = 5 rounds (censor). Failed",
             "calls carry no token cost (token fields None on every failed",
             "entry) -- retries cost attempts and latency only.", "",
             "## 1. Ledger reconciliation",
             "",
             "| Model | calls ok | calls failed | fail share | prompt tok (M) | "
             "completion tok (M) | reasoning tok (M) | mean latency s | wasted fail latency (h) |",
             "|---|---:|---:|---:|---:|---:|---:|---:|---:|"]
    for m in MODELS:
        r = rec[m]
        lines.append(
            f"| {NAME[m]} | {r['calls_ok']:,} | {r['calls_fail']:,} | "
            f"{100*r['calls_fail']/(r['calls_ok']+r['calls_fail']):.1f}% | "
            f"{r['prompt']/1e6:.2f} | {r['completion']/1e6:.2f} | "
            f"{r['reasoning']/1e6:.2f} | {r['lat_mean']:.1f} | "
            f"{r['lat_fail_total']/3600:.1f} |")
    lines += ["",
              "## 2. Per-outcome token attribution (all rounds, as recorded)",
              "",
              "| Model | programs pass | tok/program pass | programs not-passed | tok/program not-passed | ratio (not/pass) |",
              "|---|---:|---:|---:|---:|---:|"]
    for m in MODELS:
        a = attr[m]
        ratio = (a["notpass_tok_per_prog"] / a["pass_tok_per_prog"]
                 if a["pass_tok_per_prog"] else float("nan"))
        lines.append(f"| {NAME[m]} | {a['n_pass']} | {a['pass_tok_per_prog']:,.0f} | "
                     f"{a['n_notpass']} | {a['notpass_tok_per_prog']:,.0f} | {ratio:.2f}x |")
    lines += ["",
              "## 3. Per-round fix rate (hazard), main cells",
              "",
              "| Model | " + " | ".join(f"round {r}" for r in range(1, CENSOR + 1)) + " |",
              "|---|" + "---:|" * CENSOR]
    for m in MODELS:
        data = kmdata[m]
        cells = []
        for r in range(1, CENSOR + 1):
            at_risk = sum(1 for rr, _ in data if rr >= r)
            fixed = sum(1 for rr, ev in data if rr == r and ev)
            cells.append(f"{fixed}/{at_risk} ({100*fixed/at_risk:.0f}%)" if at_risk else "--")
        lines.append(f"| {NAME[m]} | " + " | ".join(cells) + " |")
    lines += ["",
              "## 4. Kaplan-Meier of rounds-to-pass + log-rank",
              "",
              "KM curves in results/rq5_km.pdf/.png (censoring at round 5).",
              ""]
    # overall log-rank across 7 groups (pairwise-merged chi2 is not valid;
    # report pairwise Holm-adjusted)
    pairs = list(combinations(MODELS, 2))
    raw = [(a, b, logrank(kmdata[a], kmdata[b])) for a, b in pairs]
    order = np.argsort([p for _, _, p in raw])
    run_max = 0.0
    m = len(raw)
    sig = []
    for rank, i in enumerate(order):
        adj = min(1.0, (m - rank) * raw[i][2])
        run_max = max(run_max, adj)
        if run_max < 0.05:
            sig.append((raw[i][0], raw[i][1], raw[i][2]))
    lines += ["Pairwise log-rank (Holm-adjusted, alpha=0.05): significant pairs:"]
    if sig:
        for a, b, pv in sig:
            lines.append(f"- {NAME[a]} vs {NAME[b]}: p = {pv:.3g}")
    else:
        lines.append("- none")
    lines.append("")
    out = R / "rq5_cost_dynamics.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")

    # ---------------- figure ----------------
    fig, ax = plt.subplots(figsize=(3.4, 2.6))
    for m, col in zip(MODELS, COLORS):
        xs, ys = km(kmdata[m])
        ax.step([x for x in xs], [100 * y for y in ys], where="post",
                label=NAME[m], color=col, linewidth=1.2)
    ax.set_xlabel("repair round")
    ax.set_ylabel("P(not yet passed) %")
    ax.set_xticks(range(0, CENSOR + 1))
    ax.set_ylim(0, 65)
    ax.legend(fontsize=5.5, loc="upper right", frameon=False)
    ax.grid(alpha=0.25, linewidth=0.4)
    fig.tight_layout()
    fig.savefig(R / "rq5_km.pdf")
    fig.savefig(R / "rq5_km.png", dpi=200)
    json.dump({m: km(kmdata[m])[1] for m in MODELS},
              open(R / "rq5_km.json", "w"), indent=1)
    print(f"written -> {R/'rq5_km.pdf'}")


if __name__ == "__main__":
    sys.exit(main())

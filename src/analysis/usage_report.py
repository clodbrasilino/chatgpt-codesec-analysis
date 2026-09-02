"""Usage report: tokens + latency per experiment cell.

Two data sources, per cell:
1. EXACT  — results/{model}/{cell_slug}.usage.jsonl ledgers (every API call
   from 2026-09-01 onward: prompt/completion/reasoning tokens + latency).
2. ESTIMATED — cells (or rounds) that ran BEFORE the ledger existed. Token
   counts are reconstructed from disk: heal_0/*.txt are generation
   completions (prompt = GENERATION_PROMPT + task text from bct.py);
   heal_N/{to_be_healed,healed} pairs are heal calls (prompt = healing
   template + commented source, completion = healed raw text). Tokens are
   estimated at ~3.6 chars/token (code-ish text) and flagged as estimates.

Outputs: results/usage_summary.csv + results/usage_report.md
"""
from __future__ import annotations

import csv
import json
import re
import statistics
from collections import defaultdict
from pathlib import Path

from src.pipeline.generate import GENERATION_PROMPT, HEALING_PROMPT
from src.pipeline.run_experiment import REPO_ROOT, _load_tasks

CHARS_PER_TOKEN = 3.6  # rough tokenizer approximation for C code + prompts

_RAW_STEM = re.compile(r"^problem-\d+(-s\d+)?$")


def _raw_txts(directory: Path) -> list[Path]:
    """Only raw LLM responses (problem-N[-sM].txt), never analyzer reports
    (problem-N.cppcheck.txt etc.)."""
    return [p for p in directory.glob("*.txt") if _RAW_STEM.match(p.stem)]


def _est_tokens(text: str) -> int:
    return max(1, round(len(text) / CHARS_PER_TOKEN))


def _sample_from_stem(stem: str) -> int:
    return int(stem.split("-s")[1]) if "-s" in stem else 1


def aggregate_ledger(model: str, slug: str) -> dict:
    """Exact per-cell stats from the usage ledger."""
    path = REPO_ROOT / "results" / model / f"{slug}.usage.jsonl"
    if not path.exists():
        return {}
    calls = [json.loads(line) for line in path.read_text().splitlines() if line.strip()]
    ok = [c for c in calls if c.get("ok")]
    lat = [c["latency_s"] for c in ok if c.get("latency_s") is not None]
    out = {
        "source": "ledger",
        "calls": len(calls),
        "failed_calls": len(calls) - len(ok),
        "prompt_tokens": sum(c.get("prompt_tokens") or 0 for c in ok),
        "completion_tokens": sum(c.get("completion_tokens") or 0 for c in ok),
        "reasoning_tokens": sum(c.get("reasoning_tokens") or 0 for c in ok),
        "mean_latency_s": round(statistics.mean(lat), 3) if lat else None,
        "total_latency_s": round(sum(lat), 1) if lat else None,
        "by_kind": {},
    }
    for kind in ("generate", "heal"):
        ks = [c for c in ok if c["kind"] == kind]
        if ks:
            out["by_kind"][kind] = {
                "calls": len(ks),
                "prompt_tokens": sum(c.get("prompt_tokens") or 0 for c in ks),
                "completion_tokens": sum(c.get("completion_tokens") or 0 for c in ks),
            }
    out["total_tokens"] = out["prompt_tokens"] + out["completion_tokens"]
    return out


def ledger_keys(model: str, slug: str) -> set[tuple]:
    """(kind, round, task_id, sample) keys of every call already in the ledger,
    so the disk estimator never double-counts them."""
    path = REPO_ROOT / "results" / model / f"{slug}.usage.jsonl"
    if not path.exists():
        return set()
    keys = set()
    for line in path.read_text().splitlines():
        if not line.strip():
            continue
        c = json.loads(line)
        if c.get("ok"):
            keys.add((c["kind"], c["round"], c["task_id"], c["sample"]))
    return keys


def estimate_cell(model: str, slug: str, tasks: dict[int, str],
                  covered: set[tuple] | None = None) -> dict:
    """Char-based token estimate for rounds that predate the ledger.
    ``covered`` = ledger keys to exclude (already counted exactly)."""
    covered = covered or set()
    root = REPO_ROOT / "collected_code_6" / model / slug
    if not root.exists():
        return {}
    prompt_tok = comp_tok = 0
    calls = 0
    # Round 0: generation. Prompt = template + task text; completion = raw .txt.
    for txt in _raw_txts(root / "heal_0"):
        pid = int(txt.stem.split("-")[1].split("-s")[0])
        samp = _sample_from_stem(txt.stem)
        if ("generate", 0, pid, samp) in covered:
            continue
        task_text = tasks.get(pid, "")
        prompt_tok += _est_tokens(GENERATION_PROMPT.format(task_text=task_text))
        comp_tok += _est_tokens(txt.read_text(errors="replace"))
        calls += 1
    # Heal rounds: prompt = template + commented source; completion = healed .txt.
    for heal_dir in sorted(root.glob("heal_*")):
        if heal_dir.name == "heal_0":
            continue
        round_no = int(heal_dir.name.split("_")[1])
        healed = heal_dir / "healed"
        if not healed.exists():
            continue
        for txt in _raw_txts(healed):
            pid = int(txt.stem.split("-")[1].split("-s")[0])
            samp = _sample_from_stem(txt.stem)
            if ("heal", round_no, pid, samp) in covered:
                continue
            src = heal_dir / "to_be_healed" / f"{txt.stem}.c"
            body = src.read_text(errors="replace") if src.exists() else ""
            prompt_tok += _est_tokens(HEALING_PROMPT.format(source_code=body))
            comp_tok += _est_tokens(txt.read_text(errors="replace"))
            calls += 1
    return {
        "source": "estimated",
        "calls": calls,
        "prompt_tokens": prompt_tok,
        "completion_tokens": comp_tok,
        "total_tokens": prompt_tok + comp_tok,
    }


def discover_cells() -> list[tuple[str, str]]:
    cells = []
    for model_dir in sorted((REPO_ROOT / "collected_code_6").iterdir()):
        if not model_dir.is_dir():
            continue
        for slug_dir in sorted(model_dir.iterdir()):
            if slug_dir.is_dir():
                cells.append((model_dir.name, slug_dir.name))
    return cells


def main() -> None:
    tasks = {t["id"]: t["text"] for t in _load_tasks()}
    rows = []
    for model, slug in discover_cells():
        led = aggregate_ledger(model, slug)
        est = estimate_cell(model, slug, tasks, covered=ledger_keys(model, slug))
        if not led and not est:
            continue
        # A cell with both sources = pre-ledger rounds (estimated) + new calls
        # (exact). Report them separately; combined total is exact+estimated.
        if led and est:
            source = "mixed"
            exact_calls, est_calls = led["calls"], est["calls"]
        elif led:
            source, exact_calls, est_calls = "ledger", led["calls"], 0
        else:
            source, exact_calls, est_calls = "estimated", 0, est["calls"]
        rows.append({
            "model": model, "cell": slug, "source": source,
            "exact_calls": exact_calls,
            "estimated_calls": est_calls,
            "exact_prompt_tokens": led.get("prompt_tokens", 0),
            "exact_completion_tokens": led.get("completion_tokens", 0),
            "estimated_prompt_tokens": est.get("prompt_tokens", 0),
            "estimated_completion_tokens": est.get("completion_tokens", 0),
            "total_tokens_approx": (
                led.get("total_tokens", 0) + est.get("total_tokens", 0)
            ),
            "mean_latency_s_exact": led.get("mean_latency_s"),
            "failed_calls_exact": led.get("failed_calls", 0),
        })

    out_csv = REPO_ROOT / "results" / "usage_summary.csv"
    with open(out_csv, "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=list(rows[0].keys()))
        w.writeheader()
        w.writerows(rows)

    md = [
        "# Token / time usage per experiment cell", "",
        f"Generated: 2026-09-01. Exact ledger active from 2026-09-01 onward",
        f"(results/{{model}}/{{cell}}.usage.jsonl — one record per API call:",
        "tokens, reasoning tokens, latency). Rounds that ran before the ledger",
        "existed are ESTIMATED from disk at ~{:.1f} chars/token; treat those as".format(CHARS_PER_TOKEN),
        "order-of-magnitude figures. `mixed` cells show both.", "",
        "| model | cell | source | calls (exact+est) | prompt tok | completion tok | total (approx) | mean latency s | failed |",
        "|---|---|---|---|---|---|---|---|---|",
    ]
    for r in rows:
        ptok = r["exact_prompt_tokens"] + r["estimated_prompt_tokens"]
        ctok = r["exact_completion_tokens"] + r["estimated_completion_tokens"]
        md.append(
            "| {model} | {cell} | {source} | {ec}+{tc} | {ptok:,} | {ctok:,} | "
            "{tot:,} | {lat} | {fc} |".format(
                model=r["model"], cell=r["cell"], source=r["source"],
                ec=r["exact_calls"], tc=r["estimated_calls"], ptok=ptok,
                ctok=ctok, tot=r["total_tokens_approx"],
                lat=r["mean_latency_s_exact"] if r["mean_latency_s_exact"] is not None else "—",
                fc=r["failed_calls_exact"],
            )
        )
    (REPO_ROOT / "results" / "usage_report.md").write_text("\n".join(md) + "\n")
    print(f"[usage] {len(rows)} cells -> {out_csv} + results/usage_report.md")


if __name__ == "__main__":
    main()

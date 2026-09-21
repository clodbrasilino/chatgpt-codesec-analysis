"""Outcomes at the configured analysis horizon, per cell.

A program is:
  * detection-free at generation  -- round 0 produced no findings
  * repaired within the horizon   -- clean with rounds_to_clean <= max_rounds
  * not detection-free at horizon -- clean only after the horizon, still
    flagged at the end of execution, or with a failed repair invocation

The horizon is experiment.max_rounds from config/experiment.yaml (via
src.config), never a literal.
"""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

from src.config import max_healing_rounds

REPO = Path(__file__).resolve().parents[2]
RES = REPO / "results"
COLL = REPO / "collected_code_6"
CAP = max_healing_rounds()
MAIN_SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["claude-fable-5", "openai-gpt56-sol", "gemini-3-pro", "kimi-k3",
          "deepseek-v4-pro", "qwen-max", "glm-5.1"]


def horizon(model: str, slug: str) -> dict:
    mf = RES / model / f"{slug}.manifest.json"
    if not mf.is_file():
        return {}
    m = json.loads(mf.read_text())
    outcomes = m.get("outcomes", {})
    r = {"n": len(outcomes), "gen": 0, "repaired": 0, "beyond": 0,
         "still": 0, "failed": 0, "rounds": Counter()}
    for base, v in outcomes.items():
        o = v.get("outcome") if isinstance(v, dict) else v
        k = v.get("rounds_to_clean") if isinstance(v, dict) else None
        if o == "clean_at_start":
            r["gen"] += 1
        elif o == "clean" and isinstance(k, int) and k <= CAP:
            r["repaired"] += 1
            r["rounds"][k] += 1
        elif o == "clean":
            r["beyond"] += 1
        elif o == "not_cleaned":
            r["still"] += 1
        else:
            r["failed"] += 1
    r["df_at_horizon"] = r["gen"] + r["repaired"]
    r["pct"] = 100.0 * r["df_at_horizon"] / r["n"] if r["n"] else 0.0
    return r


def main() -> None:
    lines = [f"# Outcomes at the {CAP}-round analysis horizon", "",
             f"Programs are classified as: detection-free at generation; "
             f"repaired within {CAP} rounds; or not detection-free at the "
             f"horizon (clean only after round {CAP}, still flagged, or failed "
             "repair).", ""]

    lines.append("## Main cells (RQ1) — full gate, all 974 tasks, 3 samples")
    lines.append("")
    lines.append(f"| Model | n | detection-free at generation | repaired "
                 f"$\\le {CAP}$ | not detection-free at horizon | rate at horizon |")
    lines.append("|---|---:|---:|---:|---:|---:|")
    for mdl in MODELS:
        r = horizon(mdl, MAIN_SLUG)
        if not r:
            continue
        nd = r["beyond"] + r["still"] + r["failed"]
        lines.append(f"| {mdl} | {r['n']} | {r['gen']} | {r['repaired']} | "
                     f"{nd} | {r['pct']:.1f}\\% |")
    lines.append("")
    lines.append("Rounds used by the repaired programs (main cells):")
    lines.append("")
    lines.append("| Model | " + " | ".join(f"r{k}" for k in range(1, CAP + 1)) + " |")
    lines.append("|---|" + "---:|" * CAP)
    for mdl in MODELS:
        r = horizon(mdl, MAIN_SLUG)
        if not r:
            continue
        g = r["rounds"].get
        cells = " | ".join(str(g(k, 0)) for k in range(1, CAP + 1))
        lines.append(f"| {mdl} | {cells} |")

    lines.append("")
    lines.append("## All other cells")
    lines.append("")
    lines.append(f"| Model | Cell | n | gen | repaired $\\le {CAP}$ | beyond {CAP} | "
                 "still flagged | failed | rate at horizon |")
    lines.append("|---|---|---:|---:|---:|---:|---:|---:|---:|")
    for model_dir in sorted(COLL.iterdir()):
        if not model_dir.is_dir():
            continue
        for slug_dir in sorted(model_dir.iterdir()):
            if not slug_dir.is_dir() or "legacy" in slug_dir.name:
                continue
            if slug_dir.name == MAIN_SLUG:
                continue
            r = horizon(model_dir.name, slug_dir.name)
            if not r or r["n"] == 0:
                continue
            lines.append(f"| {model_dir.name} | `{slug_dir.name}` | {r['n']} | "
                         f"{r['gen']} | {r['repaired']} | {r['beyond']} | "
                         f"{r['still']} | {r['failed']} | {r['pct']:.1f}\\% |")

    out = RES / "horizon_outcomes.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")
    for mdl in MODELS:
        r = horizon(mdl, MAIN_SLUG)
        if r:
            print(f"{mdl:22s} n={r['n']} gen={r['gen']} repaired={r['repaired']} "
                  f"beyond={r['beyond']} still={r['still']} "
                  f"rate={r['pct']:.1f}%")


if __name__ == "__main__":
    main()

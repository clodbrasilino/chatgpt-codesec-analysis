"""Oracle-vs-AFL++ channel comparison restricted to the paper's round horizon.

Scope = heal_0 + heal_N/healed for N <= max_healing_rounds() (config-driven;
currently 5). This is the scope the paper reports (tab:channels and the
channel-disjointness paragraph). The chain-wide numbers remain in
results/channel_comparison.md (scope ANY); the difference between the two
scopes is the small residue of programs attributed only on versions beyond
the configured round budget.

Definitions are identical to channel_comparison.py:
  attributed  = line-level finding (severity high/medium/low, line > 0)
  signal-only = crash the replay could not attribute ("Fuzzing found a crash")
  signal-only EXCLUSIVE (this report) = crash programs with NO attributed
  fuzz finding anywhere in scope (matches tab:channels' Signal-only column).

Output: results/channel_comparison_r05.md
"""
from __future__ import annotations

import pickle
import re
import sys
from collections import Counter
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from src.analysis.channel_comparison import (  # noqa: E402
    MODELS, SLUG, channel_state, counts,
)
from src.config import max_healing_rounds  # noqa: E402
from src.pipeline.comment_inject import _PROBLEM_RE  # noqa: E402

OUT = REPO / "results" / "channel_comparison_r05.md"
CACHE = REPO / "results" / ".channel_comparison_r05.cache.pkl"
CAP = max_healing_rounds()


def scan(model: str) -> dict[str, dict]:
    """Union of channel states over heal_0 and heal_N/healed for N <= CAP."""
    cell = REPO / "collected_code_6" / model / SLUG
    dirs: list[tuple[str, Path]] = [("heal_0", cell / "heal_0")]
    for d in sorted(cell.glob("heal_*")):
        m = re.fullmatch(r"heal_(\d+)", d.name)
        if not m or int(m.group(1)) < 1 or int(m.group(1)) > CAP:
            continue
        if not (d / "healed").is_dir():
            continue
        dirs.append((d.name + "/healed", d / "healed"))

    state: dict[str, dict] = {}
    n_prog = 0
    for label, d in dirs:
        if not d.is_dir():
            continue
        for p in d.glob("problem-*.c"):
            base = p.stem
            if not _PROBLEM_RE.match(base):
                continue
            if label == "heal_0":
                n_prog += 1
            st = channel_state(d, base)
            cur = state.setdefault(base, {k: False for k in st})
            for k, v in st.items():
                cur[k] = cur[k] or v
    return state


def main() -> None:
    lines: list[str] = [
        "# Dynamic channel comparison — five-round horizon (rounds 0-%d)" % CAP,
        "",
        "Cell `feedback-static+dynamic-r0-t1.0-p1.0` (main gate, 974×3, `--fuzz`).",
        f"Scope = heal_0 + heal_N/healed for N ≤ {CAP} (`max_healing_rounds()`),",
        "i.e. the same five-round window as channel_contribution.md. This is the",
        "scope the paper reports; the chain-wide numbers (scope ANY, incl. the",
        "partial rounds beyond the budget) remain in results/channel_comparison.md.",
        "",
        "`attributed` = line-level finding (severity high/medium/low, line > 0);",
        "`signal-only (exclusive)` = program crashed under fuzzing without an",
        "attributable report anywhere in scope and was never fuzz-attributed.",
        "",
    ]

    if CACHE.is_file():
        per_model = pickle.loads(CACHE.read_bytes())
        print("loaded cache", CACHE)
    else:
        per_model = {m: scan(m) for m in MODELS}
        CACHE.write_bytes(pickle.dumps(per_model))
        print("wrote cache", CACHE)
    # Drop the legacy __n_prog__ marker if present; n_prog = len(state).
    for m in MODELS:
        per_model[m].pop("__n_prog__", None)
    tot = Counter()
    lines.append("## Per model (program = model × problem instance)")
    lines.append("")
    lines.append("| Model | programs | oracle | fuzzer (attr) | both | signal-only (excl.) | fuzz-reached |")
    lines.append("|---|---:|---:|---:|---:|---:|---:|")
    for model in MODELS:
        st = per_model[model]
        oo, fo, both = counts(st, "oracle_attr", "fuzz_attr")
        sig_excl = sum(1 for b, s in st.items()
                       if s["fuzz_sig"] and not s["fuzz_attr"])
        reached = fo + both + sig_excl
        tot["oo"] += oo; tot["fo"] += fo; tot["both"] += both
        tot["sig"] += sig_excl; tot["reached"] += reached
        tot["n"] += len(st)
        lines.append(f"| {model} | {len(st)} | {oo + both} | {fo + both} | "
                     f"{both} | {sig_excl} | {reached} |")
    lines.append(f"| **TOTAL (7 models)** | {tot['n']} | {tot['oo'] + tot['both']} | "
                 f"{tot['fo'] + tot['both']} | {tot['both']} | {tot['sig']} | "
                 f"{tot['reached']} |")
    lines.append("")

    det = tot["oo"] + tot["fo"] + tot["both"]
    o_all = tot["oo"] + tot["both"]
    f_all = tot["fo"] + tot["both"]
    lines.append("## Headline disjointness (rounds 0-%d, attributed findings)" % CAP)
    lines.append("")
    lines.append("| quantity | programs | share of detected |")
    lines.append("|---|---:|---:|")
    for label, v in (("oracle (ASan/UBSan test oracle)", o_all),
                     ("AFL++ fuzzing (attributed)", f_all),
                     ("overlap (both channels)", tot["both"]),
                     ("oracle-only", tot["oo"]),
                     ("fuzz-only (attributed)", tot["fo"]),
                     ("total detected by either (attributed)", det)):
        share = f"{100.0 * v / det:.1f}%" if det else "-"
        lines.append(f"| {label} | {v} | {share} |")
    lines.append("")
    lines.append(f"AFL++/oracle attributed ratio: {f_all / o_all:.1f}x."
                 if o_all else "")
    lines.append("")
    lines.append(f"Counting signal-only crashes, the fuzz channel reaches "
                 f"{tot['fo'] + tot['both'] + tot['sig']} programs in total "
                 f"(matches the fuzzer column of channel_contribution.md).")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("Generated by `src/analysis/channel_comparison_r05.py` "
                 "(horizon from `src.config.max_healing_rounds()`). "
                 "`.test.txt` (functional failures) is excluded by design.")
    OUT.write_text("\n".join(lines))
    print(f"written {OUT}")
    print("TOTAL:", dict(tot))


if __name__ == "__main__":
    main()

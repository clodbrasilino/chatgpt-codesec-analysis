"""Oracle-vs-AFL++ channel comparison for the main s+d+fuzz cells.

Recomputed 2026-09-19 from the POST-reprocess manifests/artifacts (the earlier
33-vs-597 numbers were measured before the annotation-gap reprocess and are
obsolete).

Definitions (identical to the earlier measurement unless noted)
--------------------------------------------------------------
program            = one generated program instance = (model, basename),
                     basename = ``problem-{id}[-s{k}]``.
ORACLE channel     = sanitizer test oracle -> ``.asan.txt``.
FUZZ channel       = AFL++                 -> ``.fuzz.txt``.
                     (``.test.txt`` is functional-only and never counted.)

A finding line is ``file:line:col:severity:message``. We split:
  attributed  = severity in {high, medium, low} AND line > 0  (line-level)
  signal-only = a crash the replay could not attribute
                (``Fuzzing found a crash (signal N)``, severity ``error``)

A program counts as "detected" by a channel if ANY report in scope has that
channel's finding. Two scopes are reported:
  R0   = heal_0 only (the initial, unhealed generations)
  ANY  = heal_0 plus every heal_N/healed directory (any point in the chain)

Output: results/channel_comparison.md
"""
from __future__ import annotations

import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))

from src.pipeline.comment_inject import _PROBLEM_RE  # noqa: E402
from src.config import max_healing_rounds  # noqa: E402

SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = [
    "deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
    "openai-gpt56-sol", "claude-fable-5", "gemini-3-pro",
]
SEV = {"high", "medium", "low"}
OUT = REPO / "results" / "channel_comparison.md"

LINE_RE = re.compile(r"^([^:]+):(\d+):(\d+):([a-z]+):(.*)$")
CLASS_RULES = [
    ("signed-integer overflow", r"signed integer overflow"),
    ("float->int conversion", r"outside the range of representable values|outside the range of type"),
    ("left shift", r"left shift"),
    ("negation overflow", r"negation of"),
    ("division by zero / FPE", r"division by zero|FPE"),
    ("misaligned / null / member access", r"misaligned|null pointer|member access"),
    ("out-of-bounds (ASan)", r"overflow|underflow|out of bounds|param-overlap|BUS"),
    ("signal-only (unattributed)", None),  # handled separately
]


def parse(path: Path) -> list[tuple[int, str, str]]:
    """Return [(line, severity, message)] for a standard-format report."""
    out = []
    if not path.is_file():
        return out
    for raw in path.read_text(errors="replace").splitlines():
        m = LINE_RE.match(raw.strip())
        if not m:
            continue
        out.append((int(m.group(2)), m.group(4), m.group(5)))
    return out


def channel_state(rep_dir: Path, base: str) -> dict[str, bool]:
    oracle = parse(rep_dir / f"{base}.asan.txt")
    fuzz = parse(rep_dir / f"{base}.fuzz.txt")
    return {
        "oracle_attr": any(s in SEV and ln > 0 for ln, s, _ in oracle),
        "oracle_sig": any(s in SEV and ln <= 0 for ln, s, _ in oracle),
        "fuzz_attr": any(s in SEV and ln > 0 for ln, s, _ in fuzz),
        "fuzz_sig": any("Fuzzing found" in msg for _, _, msg in fuzz),
        "fuzz_any": any(s in SEV and ln > 0 for ln, s, _ in fuzz)
        or any("Fuzzing found" in msg for _, _, msg in fuzz),
    }


def scan(model: str) -> dict:
    cell = REPO / "collected_code_6" / model / SLUG
    dirs = [("heal_0", cell / "heal_0")]
    for d in sorted(cell.glob("heal_*")):
        if d.name == "heal_0" or not (d / "healed").is_dir():
            continue
        dirs.append((d.name + "/healed", d / "healed"))

    r0: dict[str, dict] = {}
    anyr: dict[str, dict] = {}
    classes: Counter = Counter()
    fuzz_programs: set[str] = set()

    for label, d in dirs:
        if not d.is_dir():
            continue
        for p in d.glob("problem-*.c"):
            base = p.stem
            if not _PROBLEM_RE.match(base):
                continue
            st = channel_state(d, base)
            # ANY scope accumulates every directory, heal_0 included.
            cur = anyr.setdefault(base, {k: False for k in st})
            for k, v in st.items():
                cur[k] = cur[k] or v
            if label == "heal_0":
                cur0 = r0.setdefault(base, {k: False for k in st})
                for k, v in st.items():
                    cur0[k] = cur0[k] or v
            if label == "heal_0":
                for _, s, msg in parse(d / f"{base}.fuzz.txt"):
                    if s in SEV and "AFL crash" in msg:
                        classes[classify(msg)] += 1
                        fuzz_programs.add(base)
                    elif "Fuzzing found" in msg:
                        classes["signal-only (unattributed)"] += 1
                        fuzz_programs.add(base)
    return {"r0": r0, "any": anyr, "classes": classes, "fuzz_programs": fuzz_programs}


def classify(msg: str) -> str:
    for name, pat in CLASS_RULES:
        if pat and re.search(pat, msg, re.I):
            return name
    return "other"


def counts(state: dict[str, dict], key_o: str, key_f: str) -> tuple[int, int, int]:
    o = {b for b, s in state.items() if s[key_o]}
    f = {b for b, s in state.items() if s[key_f]}
    return len(o - f), len(f - o), len(o & f)


def main() -> None:
    lines = ["# Dynamic channel comparison — sanitizer oracle vs AFL++", ""]
    lines.append("Cell `feedback-static+dynamic-r0-t1.0-p1.0` (main gate, 974×3, "
                 "`--fuzz`). **Recomputed 2026-09-19 from the post-reprocess "
                 "artifacts**; supersedes the 2026-09-18 numbers (33 / 597 / 11), "
                 "which were measured before the annotation-gap reprocess.")
    lines.append("")
    lines.append("`attributed` = line-level finding (severity high/medium/low, line > 0); "
                 "`signal-only` = crash the ASan/UBSan replay could not attribute to a line.")
    lines.append("")

    tot = {"r0": Counter(), "any": Counter()}
    distinct = {"r0": defaultdict(set), "any": defaultdict(set)}
    per_model = {}
    all_classes: Counter = Counter()
    for model in MODELS:
        res = scan(model)
        all_classes.update(res["classes"])
        per_model[model] = res
        for scope, key in (("r0", "r0"), ("any", "any")):
            st = res[key]
            # denominator = every program generated for this model (heal_0 set)
            n_prog = len(res["r0"])
            oo, fo, both = counts(st, "oracle_attr", "fuzz_attr")
            tot[scope]["oracle_only"] += oo
            tot[scope]["fuzz_only"] += fo
            tot[scope]["both"] += both
            tot[scope]["n"] += n_prog
            o = {b for b, s in st.items() if s["oracle_attr"]}
            f = {b for b, s in st.items() if s["fuzz_attr"]}
            distinct[scope]["od"] |= o
            distinct[scope]["fd"] |= f

    for scope, title, note in (
        ("r0", "Scope R0 — initial generations only (heal_0)",
         "Programs flagged on the code as first generated, before any repair."),
        ("any", "Scope ANY — anywhere in the healing chain (heal_0 + heal_N/healed)",
         f"Programs ever flagged by a channel at any point of the "
         f"{max_healing_rounds()}-round chain."),
    ):
        lines.append(f"## {title}")
        lines.append("")
        lines.append(note)
        lines.append("")
        lines.append("| Model | programs | oracle-only | fuzz-only | both | detected |")
        lines.append("|---|---|---|---|---|---|")
        for model in MODELS:
            st = per_model[model][scope]
            n = len(per_model[model]["r0"])
            oo, fo, both = counts(st, "oracle_attr", "fuzz_attr")
            lines.append(f"| {model} | {n} | {oo} | {fo} | {both} | {oo+fo+both} |")
        t = tot[scope]
        lines.append(f"| **TOTAL (7 models)** | {t['n']} | {t['oracle_only']} | "
                     f"{t['fuzz_only']} | {t['both']} | "
                     f"{t['oracle_only']+t['fuzz_only']+t['both']} |")
        lines.append("")

    # ---- headline disjointness (scope ANY, attributed) ----
    t = tot["any"]
    tot_det = t["oracle_only"] + t["fuzz_only"] + t["both"]
    lines.append("## Headline disjointness (scope ANY, attributed findings)")
    lines.append("")
    lines.append("| quantity | programs | share of detected |")
    lines.append("|---|---|---|")
    for label, v in (("oracle (ASan/UBSan test oracle)", t["oracle_only"] + t["both"]),
                     ("AFL++ fuzzing", t["fuzz_only"] + t["both"]),
                     ("overlap (both channels)", t["both"]),
                     ("oracle-only", t["oracle_only"]),
                     ("fuzz-only", t["fuzz_only"]),
                     ("total detected by either", tot_det)):
        share = f"{100.0 * v / tot_det:.1f}%" if tot_det else "-"
        lines.append(f"| {label} | {v} | {share} |")
    lines.append("")

    lines.append("Delta vs the pre-reprocess measurement (2026-09-18): "
                 "oracle 33→34, AFL++ 597→603, overlap 11→12 (instance counts, "
                 "scope ANY). The +6 AFL and +1 oracle programs come from the six "
                 "previously `heal_failed` samples that the repair run healed "
                 "end-to-end, extending their chains.")
    lines.append("")

    # ---- cross-model distinct programs (basename deduplicated over models) ----
    lines.append("## Cross-model distinct programs (same task/sample counted once)")
    lines.append("")
    lines.append("Secondary view: the SAME task/sample flagged in several models "
                 "counts once. The headline figures for the paper are the "
                 "instance counts in the tables above, not this view.")
    lines.append("")
    lines.append("| scope | oracle-only | fuzz-only | both | detected |")
    lines.append("|---|---|---|---|---|")
    for scope in ("r0", "any"):
        od, fd = distinct[scope]["od"], distinct[scope]["fd"]
        lines.append(f"| {scope} | {len(od - fd)} | {len(fd - od)} | {len(od & fd)} | "
                     f"{len(od | fd)} |")
    lines.append("")

    # ---- signal-only addendum ----
    lines.append("## Addendum — unattributed (signal-only) crashes, scope ANY")
    lines.append("")
    lines.append("| Model | fuzz signal-only | oracle signal-only |")
    lines.append("|---|---|---|")
    for model in MODELS:
        st = per_model[model]["any"]
        fs = sum(1 for s in st.values() if s["fuzz_sig"])
        os_ = sum(1 for s in st.values() if s["oracle_sig"])
        lines.append(f"| {model} | {fs} | {os_} |")
    fs_t = sum(sum(1 for s in per_model[m]["any"].values() if s["fuzz_sig"]) for m in MODELS)
    os_t = sum(sum(1 for s in per_model[m]["any"].values() if s["oracle_sig"]) for m in MODELS)
    lines.append(f"| **TOTAL** | {fs_t} | {os_t} |")
    lines.append("")
    lines.append("Counting signal-only crashes as fuzz detections, the fuzz channel "
                 f"reaches {t['fuzz_only'] + t['both'] + sum(1 for m in MODELS for s in per_model[m]['any'].values() if s['fuzz_sig'] and not s['fuzz_attr'])} "
                 "programs (fuzz-only or shared).")
    lines.append("")

    # ---- detection classes (AFL, heal_0) ----
    lines.append("## AFL++ detection classes — heal_0 findings (finding-level)")
    lines.append("")
    lines.append("| class | findings |")
    lines.append("|---|---|")
    for k, v in all_classes.most_common():
        lines.append(f"| {k} | {v} |")
    lines.append("")
    n_fp = sum(len(scan(m)["fuzz_programs"]) for m in MODELS)
    lines.append(f"Programs with >=1 AFL finding at heal_0 (sum over models): {n_fp}")
    lines.append("")
    lines.append("---")
    lines.append("")
    lines.append("Generated by `src/analysis/channel_comparison.py`. "
                 "`.test.txt` (functional failures) is excluded by design: it is "
                 "not a vulnerability-detection channel.")
    OUT.write_text("\n".join(lines))
    print(f"written {OUT}")
    print("TOTAL any-scope:", dict(tot["any"]))
    print("TOTAL r0-scope:", dict(tot["r0"]))


if __name__ == "__main__":
    main()

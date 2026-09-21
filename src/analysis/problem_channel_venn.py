"""Problem-level channel contribution across all LLMs (for the Venn figure).

Unit of analysis: the BCT problem (task), 974 total. A problem counts for
a set if ANY model, ANY of its 3 generated programs (samples), on ANY
version within the five-round horizon (rounds 0-5) produced at least one
injectable finding (line > 0, the gate's own criterion) for that
sub-channel. Main cells, full gate, non-thinking.

Sets:
  static channel  : gcc | clang | cppcheck | flawfinder (and individuals)
  tests           : failed test cases (.test.txt)
  dynamic channel : sanitizer oracle (.asan.txt: ASan/UBSan) + fuzzer
                    (.fuzz.txt: attributed findings or signal-only crashes)
                    -- tests are reported separately per user's framing.
Dynamic tools for the tool-level Venn: ASan, UBSan, AFL++.
"""
from __future__ import annotations

import json
import os
import re
import sys
from itertools import combinations
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
from src.pipeline.comment_inject import extract_standard_messages  # noqa: E402

CAP = 5
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["claude-fable-5", "openai-gpt56-sol", "gemini-3-pro", "kimi-k3",
          "deepseek-v4-pro", "qwen-max", "glm-5.1"]
STATIC = [".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt"]
COLS = STATIC + [".test.txt", ".asan.txt", ".fuzz.txt"]
TASK_RE = re.compile(r"problem-(\d+)")


def has_finding(text: str, want: str | None = None) -> bool:
    # parsed messages carry a leading space after the severity slot
    for msg in extract_standard_messages(text):
        if msg["line"] > 0:
            if want is None or msg["message"].lstrip().startswith(want):
                return True
    return False


def round_dirs(cell: Path) -> list[Path]:
    dirs = [cell / "heal_0"]
    for r in range(1, CAP + 1):
        d = cell / f"heal_{r}" / "healed"
        if d.is_dir():
            dirs.append(d)
    return dirs


def audit_model(model: str) -> tuple[dict, set[int]]:
    """Return {suffix -> set of task ids with >=1 finding} and all task ids."""
    cell = REPO / "collected_code_6" / model / MAIN
    programs = {b[:-2] for b in os.listdir(cell / "heal_0") if b.endswith(".c")}
    tasks = {int(m.group(1)) for b in programs if (m := TASK_RE.match(b))}
    sets: dict[str, set[int]] = {c: set() for c in COLS}

    def task_of(base: str) -> int | None:
        m = TASK_RE.match(base)
        return int(m.group(1)) if m else None

    for d in round_dirs(cell):
        for base in programs:
            t = task_of(base)
            if t is None:
                continue
            for s in STATIC:
                if t in sets[s]:
                    continue
                f = d / f"{base}{s}"
                if f.is_file() and has_finding(f.read_text(errors="replace")):
                    sets[s].add(t)
            f = d / f"{base}.test.txt"
            if t not in sets[".test.txt"] and f.is_file():
                if has_finding(f.read_text(errors="replace"), want="test case"):
                    sets[".test.txt"].add(t)
            f = d / f"{base}.asan.txt"
            if f.is_file() and t not in sets[".asan.txt"]:
                text = f.read_text(errors="replace")
                if (has_finding(text, want="ASan:")
                        or has_finding(text, want="UBSan:")):
                    sets[".asan.txt"].add(t)
            f = d / f"{base}.fuzz.txt"
            if f.is_file() and t not in sets[".fuzz.txt"]:
                text = f.read_text(errors="replace")
                if (has_finding(text, want="Fuzzing found a crash")
                        or has_finding(text, want="ASan:")
                        or has_finding(text, want="UBSan:")):
                    sets[".fuzz.txt"].add(t)
    return sets, tasks


def region_counts(sets_by_name: dict[str, set], total: int) -> dict:
    """All non-empty regions of up to 4 sets, keyed by set-name bitmask."""
    names = list(sets_by_name)
    regions = {}
    for mask in range(1, 1 << len(names)):
        members = None
        for i, n in enumerate(names):
            if mask >> i & 1:
                members = sets_by_name[n] if members is None else members & sets_by_name[n]
        for i, n in enumerate(names):
            if not mask >> i & 1:
                members = members - sets_by_name[n]
        regions[mask] = len(members)
    regions[0] = total - sum(regions.values())
    return regions


def fmt_key(mask: int, names: list[str]) -> str:
    return "+".join(n for i, n in enumerate(names) if mask >> i & 1) or "none"


def main() -> None:
    per_model = {}
    agg = {c: set() for c in COLS}
    all_tasks: set[int] = set()
    for model in MODELS:
        sets, tasks = audit_model(model)
        per_model[model] = sets
        all_tasks |= tasks
        for c in COLS:
            agg[c] |= sets[c]
        print(f"done {model}", file=sys.stderr)

    N = len(all_tasks)
    static_names = {"gcc": agg[".gcc.txt"], "clang": agg[".clang.txt"],
                    "cppcheck": agg[".cppcheck.txt"], "flawfinder": agg[".flawfinder.txt"]}
    static_any = set().union(*static_names.values())
    tests = agg[".test.txt"]
    dynamic = agg[".asan.txt"] | agg[".fuzz.txt"]
    dyn_tools = {"ASan": agg[".asan.txt"] | set(),   # filled below
                 }

    # ASan / UBSan / AFL++ at problem level: need per-tool split again.
    # asan.txt holds both ASan and UBSan lines; fuzz.txt is AFL++.
    # Re-derive ASan vs UBSan by rescanning with prefixes (cheap: only
    # for problems already in .asan.txt -- but files are per program, so
    # rescan everything that has an .asan.txt anywhere).
    asan_p, ubsan_p = set(), set()
    for model in MODELS:
        cell = REPO / "collected_code_6" / model / MAIN
        for d in round_dirs(cell):
            for f in d.glob("*.asan.txt"):
                base = f.name[:-len(".asan.txt")]
                t = int(TASK_RE.match(base).group(1))
                if t in asan_p and t in ubsan_p:
                    continue
                text = f.read_text(errors="replace")
                if has_finding(text, want="ASan:"):
                    asan_p.add(t)
                if has_finding(text, want="UBSan:"):
                    ubsan_p.add(t)
        print(f"asan-split done {model}", file=sys.stderr)
    afl = agg[".fuzz.txt"]
    dyn_tools = {"ASan": asan_p, "UBSan": ubsan_p, "AFL++": afl}
    dynamic_tools_any = asan_p | ubsan_p | afl

    lines = ["# Problem-level channel contribution across all LLMs",
             "",
             "Unit: BCT problem (974 tasks). A problem counts for a set if ANY",
             "model, ANY of its 3 samples, on ANY version within rounds 0-5",
             "produced >=1 injectable finding. Main cells, non-thinking.", "",
             f"Problems total: {N}", "",
             "## Channel-level (Venn 1): static / tests / dynamic(excl. tests)",
             f"static any: {len(static_any)}",
             f"tests: {len(tests)}",
             f"dynamic (oracle+fuzzer): {len(dynamic)}",
             ""]
    names1 = ["Static", "Tests", "Dynamic"]
    s1 = {"Static": static_any, "Tests": tests, "Dynamic": dynamic}
    r1 = region_counts(s1, N)
    for mask in sorted(r1):
        lines.append(f"  {fmt_key(mask, names1):45s} {r1[mask]}")

    lines += ["", "## Static tools (Venn 2)"]
    r2 = region_counts(static_names, N)
    names2 = list(static_names)
    for mask in sorted(r2):
        lines.append(f"  {fmt_key(mask, names2):45s} {r2[mask]}")

    lines += ["", "## Dynamic tools (Venn 3): ASan / UBSan / AFL++"]
    r3 = region_counts(dyn_tools, N)
    names3 = list(dyn_tools)
    for mask in sorted(r3):
        lines.append(f"  {fmt_key(mask, names3):45s} {r3[mask]}")

    out = REPO / "results" / "problem_channel_venn.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"written -> {out}")

    # machine-readable region counts for the figure
    figdata = {"N": N,
               "venn1": {fmt_key(m, names1): r1[m] for m in r1},
               "venn2": {fmt_key(m, names2): r2[m] for m in r2},
               "venn3": {fmt_key(m, names3): r3[m] for m in r3}}
    (REPO / "results" / "problem_channel_venn.json").write_text(json.dumps(figdata, indent=1))

    # per-tool problem ID lists for later qualitative picking
    lists = ["# Problem IDs per detection set (across all 7 models, rounds 0-5)", ""]
    for label, s in [("STATIC any", static_any), ("gcc", agg[".gcc.txt"]),
                     ("clang", agg[".clang.txt"]), ("cppcheck", agg[".cppcheck.txt"]),
                     ("flawfinder", agg[".flawfinder.txt"]), ("tests", tests),
                     ("dynamic any (oracle+fuzzer)", dynamic),
                     ("ASan", asan_p), ("UBSan", ubsan_p), ("AFL++", afl)]:
        lists.append(f"## {label} — {len(s)} problems")
        lists.append(", ".join(str(i) for i in sorted(s)))
        lists.append("")
    out2 = REPO / "results" / "problem_channel_sets.txt"
    out2.write_text("\n".join(lists) + "\n")
    print(f"written -> {out2}")


if __name__ == "__main__":
    main()

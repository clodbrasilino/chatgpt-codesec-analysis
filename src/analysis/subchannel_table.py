"""Per-subchannel detected-program counts for the full channel table.

A program (model x basename) counts for a sub-channel if that
sub-channel's report contains at least one injectable finding
(line > 0, the same criterion the gate's annotation uses) on any
version of the program in the repair chain.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(REPO))
from src.pipeline.comment_inject import extract_standard_messages  # noqa: E402

SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
          "openai-gpt56-sol", "claude-fable-5", "gemini-3-pro"]
SUB = [".gcc.txt", ".clang.txt", ".cppcheck.txt", ".flawfinder.txt",
       ".test.txt", ".asan.txt", ".fuzz.txt"]
DET = re.compile(r":(high|medium|low):")

totals = {s: set() for s in SUB}
totals_sig = set()
for m in MODELS:
    d = REPO / "collected_code_6" / m / SLUG
    per = {s: set() for s in SUB}
    sig = set()
    for s in SUB:
        for f in d.rglob("*" + s):
            base = f.name[: -len(s)]
            for msg in extract_standard_messages(f.read_text(errors="replace")):
                if msg["line"] > 0:
                    per[s].add(base)
                    totals[s].add((m, base))
                    break
    for f in d.rglob("*.fuzz.txt"):
        t = f.read_text(errors="replace")
        base = f.name[: -len(".fuzz.txt")]
        if "Fuzzing found a crash" in t and not DET.search(t):
            sig.add(base)
            totals_sig.add((m, base))
    row = " ".join(f"{len(per[s]):4d}" for s in SUB)
    print(f"{m:22s} {row} sig={len(sig):3d}")
print("-" * 80)
row = " ".join(f"{len(totals[s]):4d}" for s in SUB)
print(f"{'TOTAL':22s} {row} sig={len(totals_sig):3d}")
print("columns: gcc clang cppcheck flawfinder | tests oracle fuzz | signal-only")

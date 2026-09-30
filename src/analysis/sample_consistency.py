"""Sample-level consistency of round-0 detections (main cells).

Unit = BCT problem (974 tasks x 3 samples per model, n = 2,922 programs).
Round-0 flagged = manifest outcome != clean_at_start (any gate detection on
the code as first generated). Still-flagged-at-horizon = NOT detection-free
by round 5, i.e. outcome is heal_failed/not_cleaned, or outcome == clean
with rounds_to_clean > 5 (five-round censor).

Outputs (self-check targets from the frozen 2026-09-21 report):
  - tab:consistency  : per-model 0/1/2/3 sample-flag distribution at
                       generation, all-3 share of flagged tasks.
  - horizon persistence: same distribution restricted to tasks still
                       flagged at the five-round horizon.
  - tab:crossmodel   : tasks majority-flagged (>=2 of 3 samples) by N of
                       the 7 models.
  - never-flagged    : tasks flagged on no sample of any model; tasks
                       flagged on >=1 sample of >=1 model.

Output: results/sample_consistency.md
"""
from __future__ import annotations

import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
R = REPO / "results"
MAIN = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["claude-fable-5", "openai-gpt56-sol", "gemini-3-pro",
          "kimi-k3", "deepseek-v4-pro", "qwen-max", "glm-5.1"]
NAME = {"deepseek-v4-pro": "DeepSeek V4 Pro",
        "openai-gpt56-sol": "GPT-5.6~Sol", "gemini-3-pro": "Gemini 3.1 Pro",
        "kimi-k3": "Kimi K3", "glm-5.1": "GLM-5.1", "qwen-max": "Qwen Max",
        "claude-fable-5": "Claude Fable 5"}
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
CAP = 5


def load(model: str) -> dict[int, list[dict]]:
    """Per problem: list of per-sample outcome dicts (one per sample)."""
    man = json.load(open(R / model / f"{MAIN}.manifest.json"))["outcomes"]
    per: dict[int, list[dict]] = {}
    for k, v in man.items():
        m = KEY_RE.match(k)
        if not m:
            continue
        per.setdefault(int(m.group(1)), []).append(v)
    return per


def df_by_5(v: dict) -> bool:
    """Detection-free by round 5 for one sample."""
    o = v.get("outcome")
    if o == "clean_at_start":
        return True
    if o == "clean":
        r = v.get("rounds_to_clean")
        return isinstance(r, int) and r <= CAP
    return False


def dist(per: dict[int, list[dict]], pred) -> tuple[int, ...]:
    """Distribution of tasks by number of samples satisfying pred (0..3)."""
    d = [0, 0, 0, 0]
    for p, samples in per.items():
        d[min(3, sum(1 for v in samples if pred(v)))] += 1
    return tuple(d)


def main() -> None:
    data = {m: load(m) for m in MODELS}
    for m, per in data.items():
        assert len(per) == 974, (m, len(per))

    L = ["# Sample-level consistency of round-0 detections (main gate, "
         "s+d non-thinking)", "",
         "Scope: 974 tasks x 3 samples per model (n = 2,922); detections =",
         "gate reports at round 0 (generation). \"Consistency\" = share of",
         "tasks with >=1 detection that are detected on ALL 3 samples.",
         "Computed from the final manifests by `src/analysis/"
         "sample_consistency.py`.", ""]

    # 1. within-model consistency at generation (tab:consistency)
    L += ["## Within-model consistency — round-0 detections per task "
          "(0/1/2/3 samples flagged)", "",
          "| Model | 0 | 1 | 2 | 3 | tasks flagged >=1 | all-3 | consistency |",
          "|---|---:|---:|---:|---:|---:|---:|---:|"]
    gen_cons = {}
    for m in MODELS:
        d = dist(data[m], lambda v: v.get("outcome") != "clean_at_start")
        flagged = sum(d[1:])
        gen_cons[m] = d[3] / flagged
        L.append(f"| {NAME[m]} | {d[0]} | {d[1]} | {d[2]} | {d[3]} | "
                 f"{flagged} | {d[3]} | {100*d[3]/flagged:.1f}% |")
    lo = min(gen_cons.values()); hi = max(gen_cons.values())

    # 2. persistence to the five-round horizon
    L += ["", "## Within-model consistency — still flagged at the five-round "
          "horizon", "",
          "| Model | 0 | 1 | 2 | 3 | tasks >=1 | all-3 | consistency |",
          "|---|---:|---:|---:|---:|---:|---:|---:|"]
    hor_cons = {}
    for m in MODELS:
        d = dist(data[m], lambda v: not df_by_5(v))
        flagged = sum(d[1:])
        hor_cons[m] = d[3] / flagged
        L.append(f"| {NAME[m]} | {d[0]} | {d[1]} | {d[2]} | {d[3]} | "
                 f"{flagged} | {d[3]} | {100*d[3]/flagged:.1f}% |")

    # 3. cross-model majority agreement (tab:crossmodel)
    maj = {m: {p: (sum(1 for v in samples if
                       v.get("outcome") != "clean_at_start") >= 2)
               for p, samples in data[m].items()} for m in MODELS}
    pids = sorted(set.intersection(*[set(v) for v in maj.values()]))
    by_n = [0] * 8
    for p in pids:
        by_n[sum(1 for m in MODELS if maj[m][p])] += 1
    L += ["", "## Cross-model agreement — tasks majority-flagged (>=2 of 3 "
          "samples) by N of 7 models", "",
          "| Models flagging | " + " | ".join(str(i) for i in range(8)) + " |",
          "|---|" + "---:|" * 8,
          "| Tasks | " + " | ".join(str(x) for x in by_n) + " |", ""]

    # 4. never-flagged / flagged-on-any-sample summary
    ever = sum(1 for p in pids
               if any(any(v.get("outcome") != "clean_at_start"
                          for v in data[m][p]) for m in MODELS))
    never = len(pids) - ever
    ge4 = sum(1 for p in pids
              if sum(1 for m in MODELS if maj[m][p]) >= 4)
    all7 = by_n[7]
    L += [f"Of {len(pids)} tasks: {ever} ({100*ever/len(pids):.1f}%) are "
          f"flagged on at least one sample of at least one model; only "
          f"{never} tasks are detection-free across every model and every "
          f"sample.",
          f"{by_n[1:]}", ""]
    L += [f"{sum(by_n[1:])} ({100*sum(by_n[1:])/len(pids):.1f}%) are "
          f"majority-flagged by at least one model; {ge4} "
          f"({100*ge4/len(pids):.1f}%) by at least four; {all7} "
          f"({100*all7/len(pids):.1f}%) by all seven.", ""]

    # headline ranges quoted in the paper
    L += ["Headline ranges: within-model generation consistency "
          f"{100*lo:.1f}--{100*hi:.1f}%; horizon persistence "
          f"{100*min(hor_cons.values()):.1f}--{100*max(hor_cons.values()):.1f}%.",
          ""]

    (R / "sample_consistency.md").write_text("\n".join(L) + "\n")
    print(f"written -> {R / 'sample_consistency.md'}")
    print(f"gen consistency {100*lo:.1f}--{100*hi:.1f}%; "
          f"horizon {100*min(hor_cons.values()):.1f}--"
          f"{100*max(hor_cons.values()):.1f}%; "
          f"cross-model 0..7 = {by_n}; never-flagged = {never}")


if __name__ == "__main__":
    main()

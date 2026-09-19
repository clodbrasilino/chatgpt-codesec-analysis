"""Final-data analyses for the Results section (post-reprocess, 2026-09-19).

Computes on the 7 main cells (feedback-static+dynamic-r0-t1.0-p1.0):
  1. Outcome table + rounds-to-detection-free distribution
  2. Channel comparison: sanitizer oracle (.asan.txt) vs AFL (.fuzz.txt),
     unique (model, basename) programs with severity-tagged findings,
     anywhere in the repair chain
  3. Fuzzable share at round 0 per model
  4. Detection-class census at round 0 (attributed classes + signal-only)
"""
from __future__ import annotations

import json
import re
from collections import Counter
from pathlib import Path

REPO = Path(__file__).resolve().parents[2]
SLUG = "feedback-static+dynamic-r0-t1.0-p1.0"
MODELS = ["deepseek-v4-pro", "qwen-max", "glm-5.1", "kimi-k3",
          "openai-gpt56-sol", "claude-fable-5", "gemini-3-pro"]
DET = re.compile(r":(high|medium|low):")
OUT = []

def p(s=""):
    print(s)
    OUT.append(s)

# ---------- 1. outcomes + rounds ----------
p("## 1. Outcomes and rounds-to-detection-free (FINAL)")
grand = Counter()
all_rounds = []
for m in MODELS:
    mani = json.loads((REPO / "results" / m / f"{SLUG}.manifest.json").read_text())
    c = Counter(v["outcome"] for v in mani["outcomes"].values())
    grand.update(c)
    rounds = [v["rounds_to_clean"] for v in mani["outcomes"].values()
              if v["outcome"] == "clean"]
    all_rounds += [(m, r) for r in rounds]
    med = sorted(rounds)[len(rounds)//2] if rounds else None
    r1 = sum(1 for r in rounds if r == 1)
    p(f"{m:22s} dfs0={c['clean_at_start']:5d} ({100*c['clean_at_start']/2922:.1f}%) "
      f"repaired={c['clean']:5d} not_df={c['not_cleaned']:4d} "
      f"| median rounds (repaired)={med}, 1-round repairs={r1}")
p(f"TOTAL dfs0={grand['clean_at_start']} repaired={grand['clean']} "
  f"not_df={grand['not_cleaned']} (n={sum(grand.values())})")
rd = Counter(r for _, r in all_rounds)
p("rounds-to-detection-free distribution (repaired samples, all models): "
  + ", ".join(f"r{k}={v}" for k, v in sorted(rd.items())))

# ---------- 2. channel comparison ----------
p("\n## 2. Channel comparison (unique model x basename, anywhere in chain)")
T_or = T_fz = T_bo = 0
for m in MODELS:
    d = REPO / "collected_code_6" / m / SLUG
    oracle, fuzz = set(), set()
    for f in d.rglob("*.asan.txt"):
        if DET.search(f.read_text(errors="replace")):
            oracle.add(f.name[: -len(".asan.txt")])
    for f in d.rglob("*.fuzz.txt"):
        if DET.search(f.read_text(errors="replace")):
            fuzz.add(f.name[: -len(".fuzz.txt")])
    both = oracle & fuzz
    T_or += len(oracle); T_fz += len(fuzz); T_bo += len(both)
    p(f"{m:22s} oracle={len(oracle):3d} AFL={len(fuzz):3d} both={len(both):2d} "
      f"fuzz-only={len(fuzz-oracle):3d} oracle-only={len(oracle-fuzz):2d}")
tot = T_or + T_fz - T_bo
p(f"TOTAL oracle={T_or} AFL={T_fz} overlap={T_bo} "
  f"({100*T_bo/tot:.1f}% of {tot} detected programs) "
  f"fuzz-only={T_fz-T_bo} ({100*(T_fz-T_bo)/tot:.1f}%) "
  f"oracle-only={T_or-T_bo} ({100*(T_or-T_bo)/tot:.1f}%)")

# ---------- 3. fuzzable share at round 0 ----------
p("\n## 3. Fuzzable share at round 0")
for m in MODELS:
    h0 = REPO / "collected_code_6" / m / SLUG / "heal_0"
    tot_f = noif = 0
    for f in h0.glob("*.fuzz.txt"):
        tot_f += 1
        if "no fuzzable input interface" in f.read_text(errors="replace"):
            noif += 1
    p(f"{m:22s} fuzzable={tot_f-noif}/{tot_f} ({100*(tot_f-noif)/tot_f:.1f}%)")

# ---------- 4. detection classes at round 0 ----------
p("\n## 4. Detection classes at round 0 (fuzz channel, attributed + signal-only)")
cls = Counter()
for m in MODELS:
    h0 = REPO / "collected_code_6" / m / SLUG / "heal_0"
    for f in h0.glob("*.fuzz.txt"):
        for line in f.read_text(errors="replace").splitlines():
            if not DET.search(line):
                continue
            msg = line.split(":", 4)[-1]
            if "Fuzzing found a crash" in msg:
                cls["signal-only (likely memory-safety)"] += 1
            elif "signed integer overflow" in msg:
                cls["signed integer overflow"] += 1
            elif "outside the range of representable" in msg:
                cls["float->int conversion"] += 1
            elif "left shift" in msg:
                cls["left shift"] += 1
            elif "negation of" in msg:
                cls["negation overflow"] += 1
            elif "division by zero" in msg or "FPE" in msg:
                cls["division by zero / FPE"] += 1
            elif "ASan" in msg:
                cls[f"ASan: {msg.split('ASan: ')[1].split(' ')[0]}"] += 1
            else:
                cls["other: " + msg[:40]] += 1
for k, v in cls.most_common(15):
    p(f"  {v:5d}  {k}")

# oracle-only classes
p("\n## 5. Sanitizer-oracle classes (anywhere in chain, for complementarity)")
ocls = Counter()
for m in MODELS:
    d = REPO / "collected_code_6" / m / SLUG
    for f in d.rglob("*.asan.txt"):
        for line in f.read_text(errors="replace").splitlines():
            if DET.search(line):
                msg = line.split(":", 4)[-1]
                ocls[msg.split("(")[0][:60]] += 1
for k, v in ocls.most_common(12):
    p(f"  {v:5d}  {k}")

Path(REPO / "results" / "final_results_numbers.md").write_text("\n".join(OUT))
print("\nwritten results/final_results_numbers.md")

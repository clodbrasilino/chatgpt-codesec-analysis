# Data Collection Progress Report — chatgpt-codesec-analysis

**Snapshot:** 2026-09-09 10:45 CST · Source: `collected_code_6/` + `results/*.manifest.json` audit
**Expected sizes:** full-sweep cells = 974 tasks × 3 samples = **2,922**; subset cells (200-task vulnerable subset) = **600**; exceptions noted inline (qwen s+d base = 2 samples = 400, earlier RQ2 design; deepseek/qwen static temp/top-p ablations = 1 sample = 200).

---

## 1. Round-0 (heal_0) generation status

### 1a. Non-thinking models — full sweep, static feedback (expected 2,922)

| Model | heal_0 files | Coverage | Status |
|---|---:|---:|---|
| deepseek-v4-pro | 2,922 | 100% | ✅ complete (manifest n=2922) |
| qwen-max | 2,922 | 100% | ✅ complete (n=2922) |
| glm-5.1 | 2,922 | 100% | ✅ complete (n=2922) |
| kimi-k3 | 2,922 | 100% | ✅ complete (n=2922) |
| openai-gpt56-sol | 2,922 | 100% | ✅ complete (n=2922) |
| gemini-3-pro | 280 | 9.6% | 🔄 RUNNING — free-tier throttled (16 ok / 1,024 failed calls since 05:21 relaunch); 198 permanent generation failures will be auto-retried when the invalid manifest triggers the rerun cycle |
| claude-fable-5 | 26 | 0.9% | ⛔ aborted Sep 4 — no ANTHROPIC_API_KEY |

### 1b. Thinking variants — static subset (expected 600)

| Model | heal_0 files | Coverage | Status |
|---|---:|---:|---|
| kimi-k3-thinking | 600 | 100% | ✅ complete (n=600, 0 not_cleaned) |
| deepseek-v4-pro-thinking | 598 | 99.7% | ✅ complete as run (n=598) — covers 201 problems: 198×3 + 1×2 + 2×1 samples, i.e. 2 samples short of full 3× coverage |
| glm-5.1-thinking | 557 | 92.8% | ⛔ BLOCKED — DashScope arrears; round-1 healing partially done (151 files queued in heal_1); manifest deleted as invalid, skip-existing relaunch ready |
| openai-gpt56-sol-thinking | 65 | 10.8% | ⛔ BLOCKED — OpenAI credits exhausted (429 credit_balance_exhausted) |
| gemini-3-pro-thinking | 1 | 0.2% | ⛔ not started (1 stray probe file; Gemini free-tier quota) |

---

## 2. Healing rounds progress — static+dynamic (s+d) cells

All existing s+d cells are **COMPLETE**: manifests written, healing rounds 1–10 generated (+ terminal heal_11 verification dir). "Pending healing rounds" is therefore **0** for these; terminal residue = `not_cleaned` (still dirty after 10 rounds). RTC = rounds_to_clean distribution (round at which a problem became clean).

| Model | Cell (s+d) | heal_0 | entered r1 (files/probs) | clean_at_start | healed | not_cleaned | RTC peak |
|---|---|---:|---:|---:|---:|---:|---|
| deepseek-v4-pro | t1.0-p1.0 (base) | 600 | 263 / 136p | 337 | 230 | 33 | r6–10 tail |
| deepseek-v4-pro | t0.2-p1.0 | 600 | 233 / 106p | 367 | 196 | 37 | r7 |
| deepseek-v4-pro | t1.0-p0.5 | 600 | 238 / 107p | 362 | 206 | 32 | r7 |
| qwen-max | t1.0-p1.0 (base, **2 samples**) | 400 | 193 / 131p | 207 | 160 | 33 | r9 |
| qwen-max | t0.2-p1.0 | 600 | 274 / 126p | 326 | 236 | 38 | r7 |
| qwen-max | t1.0-p0.5 | 600 | 245 / 114p | 355 | 207 | 38 | r7 |
| glm-5.1 | t1.0-p1.0 (base) | 600 | 264 / 140p | 336 | 222 | 42 | r10 |
| glm-5.1 | t0.2-p1.0 | 600 | 263 / 111p | 337 | 218 | 45 | r7 |
| glm-5.1 | t1.0-p0.5 | 600 | 256 / 112p | 344 | 214 | 42 | r8 |
| kimi-k3 | t1.0-p1.0 (base) | 600 | 200 / 118p | 400 | 173 | 27 | r7 |
| openai-gpt56-sol | t1.0-p1.0 (base) | 600 | 136 / 73p | 464 | 133 | 3 | r8 |
| gemini-3-pro | t1.0-p1.0 (base) | — | — | — | — | — | ⛔ not started |
| gemini-3-pro | t0.2-p1.0 | — | — | — | — | — | ⛔ not started |
| gemini-3-pro | t1.0-p0.5 | — | — | — | — | — | ⛔ not started |

Healing converges fast: for every completed s+d cell, the bulk of problems clean in rounds 1–3 (e.g. glm base RTC: 135 problems at r1, 48 at r2, tail to r10); rounds 6–10 handle <5% stragglers.

**Problems pending healing-round generation** (incomplete cells only):
- gemini-3-pro s+d (all 3 cells): 0 rounds generated — round-0 itself is only 280/2,922 in the static parent cell.
- glm-5.1-thinking: 151 findings queued in r1 + 43 missing round-0 samples (blocked on DashScope top-up).
- openai-gpt56-sol-thinking: 535 missing round-0 samples (blocked on OpenAI credits).

---

## 3. Ablation status

### 3a. Dynamic-only feedback (subset, 600)

| Model | heal_0 | Status | Outcomes (cs / clean / not_cleaned) |
|---|---:|---|---|
| deepseek-v4-pro | 600 | ✅ complete | 559 / 13 / 28 |
| qwen-max | 600 | ✅ complete | 532 / 50 / 18 |
| glm-5.1 | 600 | ✅ complete | 564 / 15 / 21 |
| kimi-k3 | 600 | ✅ complete | 564 / 16 / 20 |
| openai-gpt56-sol | 600 | ✅ complete | 586 / 14 / 0 |
| gemini-3-pro | — | ⛔ not started | — |

### 3b. Temperature / top-p subsets

**s+d feedback (600 each):**

| Model | t0.2-p1.0 | t1.0-p0.5 |
|---|---|---|
| deepseek-v4-pro | ✅ 600 (cs 367 / cl 196 / nc 37) | ✅ 600 (cs 362 / cl 206 / nc 32) |
| qwen-max | ✅ 600 (cs 326 / cl 236 / nc 38) | ✅ 600 (cs 355 / cl 207 / nc 38) |
| glm-5.1 | ✅ 600 (cs 337 / cl 218 / nc 45) | ✅ 600 (cs 344 / cl 214 / nc 42) |
| gemini-3-pro | ⛔ not started | ⛔ not started |

**static-only (1 sample, 200 each — earlier RQ1 grid, deepseek + qwen only):**

| Model | t0.2-p1.0 | t1.0-p0.5 |
|---|---|---|
| deepseek-v4-pro | ✅ 200 (cs 139 / cl 57 / nc 4) | ✅ 200 (cs 127 / cl 69 / nc 4) |
| qwen-max | ✅ 200 (cs 126 / cl 72 / nc 2) | ✅ 200 (cs 142 / cl 55 / nc 3) |

Static-only temp/top-p cells are **not part of the sweep plan** for glm/kimi/gpt/gemini (plan ablations are s+d only).

### 3c. Other cells

- **qwen-max feedback-none t0.5-p0.5:** directory exists but is **empty** (0 files, no manifest) — never collected. Decide whether this baseline is needed.
- **Full static ALL** for the 5 non-thinking models: complete (see §1a). Outcomes: deepseek 1916/916/90 · qwen 1804/1082/36 · glm 1431/1337/154 · kimi 2284/629/9 · gpt 2283/631/8 (cs/clean/nc).

---

## 4. Bottom line

- **12 / 23 sweep manifests complete and valid** (0 invalid on disk). All heal_0 and healing-round data for those 12 cells is fully collected (rounds 1–10 + terminal dir each).
- **11 cells missing**, all blocked on external factors:
  - gemini ×6 (static ALL in progress at 280/2,922 + 5 queued) — free-tier 250 req/day quota; **needs Google AI billing enabled**;
  - glm-5.1-thinking static (557/600 + partial r1) — DashScope arrears, needs top-up;
  - openai-gpt56-sol-thinking static (65/600) — OpenAI credits exhausted;
  - claude ×3 — ANTHROPIC_API_KEY not yet registered.
- Data-quality flags: deepseek-v4-pro-thinking is 2 samples short (598 vs 600); qwen s+d base has 2 samples (400) by design; qwen feedback-none cell empty.

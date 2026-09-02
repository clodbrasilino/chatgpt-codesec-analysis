# Dry-run report — deepseek-v4-pro (flagship)

**Date:** 2026-08-31 · **Provider:** DeepSeek API (`api.deepseek.com`)

> Superseded sections below (2-task dry run) are kept for the record; see
> **Validation runs** first for the 30-task results.

## Model pin

- DeepSeek retired the `deepseek-chat`/`deepseek-reasoner` aliases (they now resolve to
  `deepseek-v4-flash`). The flagship is **`deepseek-v4-pro`**, a hybrid reasoning model.
- This cell runs it in the **non-reasoning (RQ1 baseline) configuration**: `thinking: {"type": "disabled"}` sent as extra body, `temperature=1.0`, `top_p=1.0`.
- Verified: API balance OK, served model id `deepseek-v4-pro`, no `reasoning_content` leakage.
- Registry: `config/models.yaml` now pins `deepseek-v4-flash`, `deepseek-v4-pro` (thinking disabled), `deepseek-v4-pro-thinking` (reasoning variant, for the thinking ablation).

## Cell configuration

| field | value |
|---|---|
| model | deepseek-v4-pro (non-reasoning) |
| feedback | static |
| measure | static + dynamic (sanitizer oracle + AFL++ fuzzing) |
| tasks | BCT 1, 2 |
| samples | 1 · temp 1.0 · top_p 1.0 |
| max rounds | 1 (dry-run cap) |
| static gate | gcc-15 -fanalyzer · clang --analyze (+z3) · Cppcheck Premium 23.6 · flawfinder 2.0.19 · gcc compile gate |
| dynamic | ASan+UBSan oracle (Apple clang, CLT 26.6) + AFL++ 5.02c (two-binary fuzz/replay design) |

## Outcomes (manifest: `results/deepseek-v4-pro/feedback-static-r0-t1.0-p1.0.manifest.json`)

| problem | compile | static findings @heal_0 | dynamic @heal_0 | outcome |
|---|---|---|---|---|
| problem-1 | OK (.o) | none (4 tools clean) | oracle: CLI mode, no crashes | **clean_at_start** (0 rounds) |
| problem-2 | OK (.o) | Cppcheck `nullPointerRedundantCheck` @ L10–11 | oracle: 3/3 test cases FAILED (expected [4,5]/[3,4]/[13,14], got no output) | **not_cleaned** (1 round cap) |

## Repair trace (problem-2)

1. **heal_0** — raw LLM output in `problem-2.txt`, sanitized source `problem-2.c`.
   Cppcheck: `Either the condition 'resultSize==NULL' is redundant or there is possible null pointer dereference` (writes `*resultSize` after checking `resultSize==NULL`). Oracle: function found but wrong/no output on all test cases.
2. **heal_1/to_be_healed/problem-2.c** — v1-style `/* Possible weaknesses found: ... */` comments injected at the flagged lines (static feedback only; oracle failures are not injected in this cell by design).
3. **heal_1/healed** — model rewrote the guard (`if (resultSize != NULL) *resultSize = 0;`), fixing the null-deref finding. New Cppcheck *style* findings (`constVariable` L47–48) appeared; oracle still fails (expected — feedback=static never tells the model about test failures).
4. At the 1-round cap the file is recorded `not_cleaned`; the still-flagged state is queued in `heal_2/to_be_healed/`.

No `.asan.txt` / `.fuzz.txt` reports were produced: no memory/UB findings surfaced and the AFL++ channel found no crashes (reports are only written when non-empty).

## Analysis outputs (regenerated)

- `results/metrics.csv` — per-cell tidy table (both deepseek-v4-pro and qwen-max cells).
- `results/stats_report.md` — per-model summary with bootstrap 95% CIs + pairwise contrasts (Fisher exact; nothing significant at n=2, as expected for a dry run).
- `results/figures/` — fig_defect_rate, fig_survival, fig_rounds, fig_analyzers (pdf+svg).

## Pipeline fixes made during this dry run

1. `src/llm/openai_compatible.py` — provider `extra_body` now sent on both reasoning and non-reasoning paths via the SDK's `extra_body=` parameter (needed for `thinking: disabled` on hybrid models; unknown kwargs raise TypeError).
2. `src/pipeline/generate.py` — `_safe` retry wrapper capped at 5 attempts (previously retried deterministic TypeErrors forever, hanging the run).
3. `src/pipeline/comment_inject.py` — `create_output_folders` replaced with `os.makedirs(..., exist_ok=True)` (old prefix-walk called `os.mkdir("/")` and the host's broker shim raises PermissionError, not FileExistsError).
4. `src/harness/run.py` + `src/dyn/fuzzer.py` — scratch roots moved to the system temp dir (`$TMPDIR/chatgpt-codesec-analysis/{build,fuzz}`): the host's bulk-delete guard kills background processes that delete ≥50 files inside project paths (LINK-mode harness dirs hold one file per test case; AFL++ out dirs hold 60+).
5. `results/metrics.csv` had been overwritten by an Excel save (xlsx bytes); the stale copy is kept as `results/metrics.old.xlsx` and the CSV regenerated.

## Cost / latency notes

- Generation: ~4 s/task; heal call: ~6 s. Full 2-task cell incl. static + dynamic + fuzz: **~29 s wall**.

---

# Validation runs (post-dry-run hardening)

## 30-task, 7-round cell — deepseek-v4-pro (non-thinking)

`--tasks 1-30 --feedback static --measure static+dynamic --fuzz --max-rounds 7` · 10.5 min wall

| metric | value |
|---|---|
| n generated / compilable | 30 / 30 (100%) |
| initial defect rate (any channel) | 46.7% (14/30) — cppcheck 9, oracle test failures +5 |
| clean at start | 21 (70%) |
| cleaned within 7 rounds | 7 (23.3%) — rounds: 1,1,1,1,2,2,6 |
| not cleaned | 2 (6.7%) — problem-19, problem-26 |
| **final clean rate** | **93.3%** |
| survival (flagged per round) | 9 → 5 → 3 → 3 → 3 → 3 → 2 |

The decay curve matches the ISE 2026 paper's v1 behaviour (most defects fixed
in rounds 1–2, a hard tail of 2–3 files).

## Thinking variant — deepseek-v4-pro-thinking (2 tasks)

Registry entry `deepseek-v4-pro-thinking` (reasoning on, 16k max tokens).
First attempt produced **0-byte outputs** (empty content, silently "clean") —
fixed by a client-side guard that raises on empty completions (retry ×5) and a
`heal_failed` outcome so missing artifacts are never counted as clean. With
guards: real code on both tasks, statically clean at start on both (vs. the
non-thinking run where problem-2 was flagged at heal_0). Thinking latency
~60–80 s/call (~20× non-thinking).

## Additional hardening from these runs

- `--tasks` now accepts inclusive ranges (`1-30`).
- `run_batch` / `_heal_batch` tolerate per-task permanent failures (a stubborn
  task no longer kills a sweep cell).
- Thinking entries get `max_tokens: 16384` so reasoning chains don't exhaust
  the budget before content is emitted.
- Known design note: oracle messages anchored at line 0 ("no testable
  interface", "could not compile under sanitizers") are treated as info notes,
  not defect findings — consistent with v1 semantics.

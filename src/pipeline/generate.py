"""LLM code generation and healing calls with v1 prompt parity.

Prompts are copied verbatim from v1 ``collect_code.py`` (generation prompt at
lines 132-144 incl. the "Avoid CWE-664/703/710" suffix; healing prompt at
lines 101-111) so results stay comparable with the ISE 2026 paper.
"""
from __future__ import annotations

import os
import time
import traceback
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path

from tqdm import tqdm

from src.llm.client import user_message
from src.llm.registry import ModelConfig, get_client
from src.llm.parse import sanitize_llm_output
from src.pipeline.usage_ledger import log_call

GENERATION_PROMPT = (
    "Acting as an experienced C developer, "
    "{task_text} "
    "Don't forget to add main function, "
    "and proper includes and function definitions. "
    "Don't write any comments, just write the code. "
    "Avoid the following programming mistakes: "
    "CWE-664: Improper Control of a Resource Through its Lifetime, "
    "CWE-703: Improper Check or Handling of Exceptional Conditions, "
    "CWE-710: Improper Adherence to Coding Standards"
)

HEALING_PROMPT = (
    "Acting as an experienced C developer, "
    "analyze the following source-code: \n"
    "{source_code}\n "
    "Re-write the source-code, paying attention to "
    "the comments to check for fixes for the possible "
    "weaknesses identified. "
    "Don't forget to add main function, "
    "and proper includes and function definitions. "
    "don't write any comments, just write the code."
)


def sample_suffix(sample: int) -> str:
    return "" if sample == 1 else f"-s{sample}"


def _timed_complete(client, messages, cfg, output_dir, kind, task_id,
                    sample, round_no, **kwargs):
    """client.complete() with wall-clock latency + usage ledger logging.

    Logs every attempt (failures too — retries consume budget even when the
    API returns no usage block)."""
    t0 = time.perf_counter()
    try:
        resp = client.complete(messages, **kwargs)
    except BaseException as ex:  # noqa: BLE001 — log then re-raise for _safe
        log_call(output_dir, cfg.id, kind=kind, task_id=task_id, sample=sample,
                 round_no=round_no, latency_s=time.perf_counter() - t0,
                 served_model=cfg.model_id, ok=False, error=ex)
        raise
    log_call(output_dir, cfg.id, kind=kind, task_id=task_id, sample=sample,
             round_no=round_no, usage=resp.usage,
             latency_s=time.perf_counter() - t0,
             served_model=resp.model or cfg.model_id)
    return resp


def generate_code(
    cfg: ModelConfig,
    task_text: str,
    task_id: int,
    output_dir: str,
    sample: int = 1,
    temperature: float = 1.0,
    top_p: float = 1.0,
    force: bool = False,
) -> Path | None:
    """Generate C code for one task (zero-shot). Writes raw .txt; returns path."""
    basename = f"problem-{task_id}{sample_suffix(sample)}"
    raw_path = Path(output_dir) / f"{basename}.txt"
    if raw_path.exists() and not force:
        return raw_path
    client = get_client(cfg)
    prompt = GENERATION_PROMPT.format(task_text=task_text)
    resp = _timed_complete(
        client, [user_message(prompt)], cfg, output_dir, "generate",
        task_id, sample, 0,
        temperature=temperature,
        top_p=top_p,
        max_tokens=cfg.max_tokens,
        reasoning=cfg.reasoning,
    )
    raw_path.parent.mkdir(parents=True, exist_ok=True)
    raw_path.write_text(resp.text)
    # Also write the .c immediately (v1 split this into a later sanitize step;
    # doing it here keeps per-sample files self-contained).
    (Path(output_dir) / f"{basename}.c").write_text(sanitize_llm_output(resp.text))
    return raw_path


def heal_code(
    cfg: ModelConfig,
    commented_source: str,
    task_id: int,
    output_dir: str,
    heal_round: int,
    sample: int = 1,
    force: bool = False,
) -> Path | None:
    """Ask the model to repair annotated code. Writes raw .txt; returns path."""
    basename = f"problem-{task_id}{sample_suffix(sample)}"
    raw_path = Path(output_dir) / f"{basename}.txt"
    if raw_path.exists() and not force:
        return raw_path
    client = get_client(cfg)
    prompt = HEALING_PROMPT.format(source_code=commented_source)
    resp = _timed_complete(
        client, [user_message(prompt)], cfg, output_dir, "heal",
        task_id, sample, heal_round,
        temperature=cfg.default_temp,
        top_p=cfg.default_top_p,
        max_tokens=cfg.max_tokens,
        reasoning=cfg.reasoning,
    )
    raw_path.parent.mkdir(parents=True, exist_ok=True)
    raw_path.write_text(resp.text)
    (Path(output_dir) / f"{basename}.c").write_text(sanitize_llm_output(resp.text))
    return raw_path


def run_batch(
    cfg: ModelConfig,
    tasks: list[dict],
    output_dir: str,
    sample: int = 1,
    temperature: float = 1.0,
    top_p: float = 1.0,
) -> None:
    """Generate code for many tasks with a per-provider thread pool."""
    Path(output_dir).mkdir(parents=True, exist_ok=True)
    concurrency = cfg.concurrency
    progress = tqdm(total=len(tasks), desc=f"Generating ({cfg.id}): ")
    with ThreadPoolExecutor(max_workers=concurrency) as pool:
        futures = {
            pool.submit(
                _safe,
                generate_code,
                cfg,
                task["text"],
                task["id"],
                output_dir,
                sample,
                temperature,
                top_p,
            ): task["id"]
            for task in tasks
        }
        for fut in as_completed(futures):
            try:
                _ = fut.result()
            except KeyboardInterrupt:
                raise
            except BaseException as ex:  # noqa: BLE001
                # One permanently failed task must not kill the whole cell.
                print(f"[warn] generation failed permanently: {ex}")
            progress.update()


def _safe(fn, *args, max_attempts: int = 5):
    """Retry wrapper. Deterministic failures (TypeError etc.) must not hang
    the pipeline forever: give up after ``max_attempts`` and re-raise."""
    last_ex: BaseException | None = None
    for attempt in range(1, max_attempts + 1):
        try:
            return fn(*args)
        except KeyboardInterrupt:
            raise
        except BaseException as ex:  # noqa: BLE001
            last_ex = ex
            traceback.print_exc()
            print(
                f"call failed ({args[2] if len(args) > 2 else '?'}): {ex}; "
                f"attempt {attempt}/{max_attempts}, retrying in 5s"
            )
            if attempt < max_attempts:
                time.sleep(5)
    raise RuntimeError(f"giving up after {max_attempts} attempts") from last_ex

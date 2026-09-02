"""Per-cell usage ledger: tokens + latency for every LLM API call.

One JSONL record per API call, appended to
``results/{model_id}/{cell_slug}.usage.jsonl`` so cost and time budgets can
be audited per cell, per round, and per call kind (generate vs heal).

The ledger path is derived from the heal output dir the call writes into:
``collected_code_6/{model}/{slug}/heal_N[/healed]`` -> walk up past ``heal_*``
to the cell dir; the ledger is a sibling of the cell's manifest under
``results/``. Thread-safe: called from the generate/heal thread pools.
"""
from __future__ import annotations

import json
import threading
from datetime import datetime, timezone
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]

_LOCK = threading.Lock()


def ledger_path(output_dir: str | Path, model_id: str) -> Path:
    """Cell ledger path derived from a heal/generate output dir."""
    d = Path(output_dir).resolve()
    if d.name in ("healed", "to_be_healed"):
        d = d.parent
    while d.name.startswith("heal_"):
        d = d.parent
    return REPO_ROOT / "results" / model_id / f"{d.name}.usage.jsonl"


def _reasoning_tokens(usage: dict) -> int | None:
    """Reasoning tokens, wherever the provider hides them."""
    det = usage.get("completion_tokens_details")
    if isinstance(det, dict) and det.get("reasoning_tokens"):
        return det["reasoning_tokens"]
    return usage.get("reasoning_tokens")


def log_call(
    output_dir: str | Path,
    model_id: str,
    *,
    kind: str,  # "generate" | "heal"
    task_id: int,
    sample: int,
    round_no: int,
    usage: dict | None = None,
    latency_s: float = 0.0,
    served_model: str = "",
    ok: bool = True,
    error: BaseException | None = None,
) -> None:
    """Append one usage record. Failed attempts log latency with ok=false
    (token counts are unavailable when the API returns an error)."""
    usage = usage or {}
    rec = {
        "ts": datetime.now(timezone.utc).isoformat(timespec="seconds"),
        "model_id": model_id,
        "served_model": served_model,
        "kind": kind,
        "round": round_no,
        "task_id": task_id,
        "sample": sample,
        "prompt_tokens": usage.get("prompt_tokens"),
        "completion_tokens": usage.get("completion_tokens"),
        "total_tokens": usage.get("total_tokens"),
        "reasoning_tokens": _reasoning_tokens(usage),
        "latency_s": round(latency_s, 3),
        "ok": ok,
    }
    if error is not None:
        rec["error"] = f"{type(error).__name__}: {error}"[:300]
    p = ledger_path(output_dir, model_id)
    with _LOCK:
        p.parent.mkdir(parents=True, exist_ok=True)
        with open(p, "a", encoding="utf-8") as f:
            f.write(json.dumps(rec) + "\n")

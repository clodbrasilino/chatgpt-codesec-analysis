"""Single source of truth for experiment configuration.

The healing-round budget is an **experiment configuration value**
(``config/experiment.yaml -> experiment.max_rounds``), not a code constant.
Nothing in ``src/`` may hard-code a number of rounds: every pipeline entry
point and every analysis script reads it from here, so changing the budget is
a one-line config edit with no code change.

Two distinct questions are answered:

* :func:`max_healing_rounds` — how many healing rounds the *protocol* allows
  (used to run a cell, and as the reporting cap).
* :func:`discover_rounds` — how many healing rounds *actually exist* on disk
  for a cell (used when scanning already-collected artifacts, which must never
  be truncated by the current protocol setting).
"""
from __future__ import annotations

from pathlib import Path

import yaml

REPO_ROOT = Path(__file__).resolve().parents[1]
CONFIG_PATH = REPO_ROOT / "config" / "experiment.yaml"

_CACHE: dict | None = None


def experiment_config(reload: bool = False) -> dict:
    """Parsed ``config/experiment.yaml`` (cached within a process)."""
    global _CACHE
    if _CACHE is None or reload:
        with open(CONFIG_PATH) as f:
            _CACHE = yaml.safe_load(f) or {}
    return _CACHE


def max_healing_rounds(manifest_max_rounds: int | None = None) -> int:
    """Configured maximum number of healing rounds.

    Raises if the key is absent — the budget must be defined by configuration,
    never by a fallback constant in code.

    ``manifest_max_rounds`` is the value a manifest recorded for the cell it
    describes. When given, the effective cap is the *smaller* of the two: a
    cell can never be reported beyond the number of rounds it actually ran,
    and a cell that ran more rounds than the current protocol allows is
    truncated to the configured cap.
    """
    cfg = experiment_config()
    raw = cfg.get("experiment", {}).get("max_rounds")
    if raw is None:
        raise RuntimeError(
            f"experiment.max_rounds is not set in {CONFIG_PATH}. "
            "The healing-round budget must be defined by experiment configuration."
        )
    configured = int(raw)
    if configured < 1:
        raise RuntimeError(
            f"experiment.max_rounds must be >= 1, got {configured} in {CONFIG_PATH}"
        )
    if manifest_max_rounds is None:
        return configured
    return min(configured, int(manifest_max_rounds))


def not_cleaned_penalty(manifest_max_rounds: int | None = None) -> float:
    """Rounds-to-clean score assigned to a never-cleaned program.

    Convention: one more than the maximum number of healing rounds, so a
    program that never healed scores strictly worse than any program that
    healed within budget.
    """
    return float(max_healing_rounds(manifest_max_rounds) + 1)


def discover_rounds(cell_dir: Path) -> list[int]:
    """Healing rounds that actually exist under ``cell_dir`` (sorted).

    Scans the filesystem instead of applying the configured cap: artifacts
    already collected under a larger budget must remain fully visible to
    audit and quarantine tooling.
    """
    cell_dir = Path(cell_dir)
    out: list[int] = []
    for d in cell_dir.glob("heal_*"):
        name = d.name.split("_", 1)[-1]
        if not name.isdigit():
            continue
        n = int(name)
        if n >= 1 and (d / "to_be_healed").is_dir():
            out.append(n)
    return sorted(out)

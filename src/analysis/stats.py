"""Statistical analysis for the FSE 2027 extension.

Comparisons the paper needs:

1. Defect/clean-rate contrasts between models or feedback channels
   -> Fisher exact (small n) / chi-square, with odds ratio + CI.
2. Rounds-to-clean contrasts -> Mann-Whitney U + Cliff's delta.
3. Bootstrap CIs for any rate.
4. Holm-Bonferroni correction over the family of pairwise model contrasts.

Everything operates on the tidy table produced by ``metrics.py``
(results/metrics.csv) plus the per-file manifests.
"""
from __future__ import annotations

import itertools
import json
import math
from pathlib import Path

import numpy as np
import pandas as pd
from scipy import stats as sps

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS_ROOT = REPO_ROOT / "results"


# ---------------------------------------------------------------------------
# Effect sizes
# ---------------------------------------------------------------------------

def cliffs_delta(x: list[float], y: list[float]) -> float:
    """Cliff's delta effect size for ordinal comparisons (0 = no effect)."""
    if not x or not y:
        return float("nan")
    gt = sum(1 for a in x for b in y if a > b)
    lt = sum(1 for a in x for b in y if a < b)
    return (gt - lt) / (len(x) * len(y))


def _delta_label(d: float) -> str:
    a = abs(d)
    if a < 0.147:
        return "negligible"
    if a < 0.33:
        return "small"
    if a < 0.474:
        return "medium"
    return "large"


def cohens_h(p1: float, p2: float) -> float:
    """Cohen's h effect size for two proportions."""
    phi = lambda p: 2 * math.asin(math.sqrt(min(max(p, 0.0), 1.0)))  # noqa: E731
    return phi(p1) - phi(p2)


# ---------------------------------------------------------------------------
# Rate comparison: Fisher / chi-square + odds ratio
# ---------------------------------------------------------------------------

def compare_rates(
    x1: int, n1: int, x2: int, n2: int, name1: str = "A", name2: str = "B"
) -> dict:
    """Compare two proportions (x/n successes). Fisher when any cell < 5."""
    table = [[x1, n1 - x1], [x2, n2 - x2]]
    if min(min(row) for row in table) < 5:
        oddsratio, p = sps.fisher_exact(table)
        test = "fisher"
    else:
        chi2, p, _, _ = sps.chi2_contingency(table, correction=False)
        oddsratio = (x1 / max(n1 - x1, 1e-9)) / (x2 / max(n2 - x2, 1e-9))
        test = "chi2"
    p1 = x1 / n1 if n1 else float("nan")
    p2 = x2 / n2 if n2 else float("nan")
    return {
        "name1": name1, "name2": name2,
        "rate1": round(p1, 4), "rate2": round(p2, 4),
        "delta": round(p1 - p2, 4),
        "cohens_h": round(cohens_h(p1, p2), 3),
        "test": test, "p_value": float(p),
        "odds_ratio": round(float(oddsratio), 3),
    }


# ---------------------------------------------------------------------------
# Ordinal comparison: rounds-to-clean
# ---------------------------------------------------------------------------

def compare_rounds(
    r1: list[int], r2: list[int], name1: str = "A", name2: str = "B"
) -> dict:
    """Mann-Whitney U on rounds-to-clean + Cliff's delta."""
    if len(r1) < 2 or len(r2) < 2:
        return {
            "name1": name1, "name2": name2,
            "n1": len(r1), "n2": len(r2), "test": "skipped (n too small)",
        }
    u, p = sps.mannwhitneyu(r1, r2, alternative="two-sided")
    d = cliffs_delta(r1, r2)
    return {
        "name1": name1, "name2": name2,
        "n1": len(r1), "n2": len(r2),
        "mean1": round(float(np.mean(r1)), 3), "mean2": round(float(np.mean(r2)), 3),
        "test": "mannwhitney", "p_value": float(p),
        "cliffs_delta": round(d, 3), "effect": _delta_label(d),
    }


# ---------------------------------------------------------------------------
# Bootstrap CI for a rate
# ---------------------------------------------------------------------------

def bootstrap_ci(
    x: int, n: int, n_boot: int = 10_000, alpha: float = 0.05, seed: int = 42
) -> tuple[float, float]:
    """Percentile bootstrap CI for the binomial proportion x/n."""
    rng = np.random.default_rng(seed)
    draws = rng.binomial(n, x / n if n else 0.0, size=n_boot) / n
    lo, hi = np.quantile(draws, [alpha / 2, 1 - alpha / 2])
    return round(float(lo), 4), round(float(hi), 4)


# ---------------------------------------------------------------------------
# Holm-Bonferroni
# ---------------------------------------------------------------------------

def holm_correction(results: list[dict], p_key: str = "p_value") -> list[dict]:
    """Add Holm-adjusted p-values + significance stars to a list of results."""
    idx_p = [
        (i, r[p_key]) for i, r in enumerate(results) if p_key in r and r[p_key] is not None
    ]
    idx_p.sort(key=lambda t: t[1])
    m = len(idx_p)
    running = 0.0
    for rank, (i, p) in enumerate(idx_p):
        adj = min(1.0, (m - rank) * p)
        running = max(running, adj)  # enforce monotonicity
        results[i]["p_adjusted"] = round(running, 6)
        results[i]["significant"] = running < 0.05
    return results


# ---------------------------------------------------------------------------
# Cell-level drivers
# ---------------------------------------------------------------------------

def load_cell_rounds(model: str, cell: str) -> list[int]:
    """Rounds-to-clean list for one cell from its manifest."""
    path = RESULTS_ROOT / model / f"{cell}.manifest.json"
    if not path.exists():
        return []
    manifest = json.loads(path.read_text())
    return [
        o["rounds_to_clean"]
        for o in manifest["outcomes"].values()
        if o["outcome"] == "clean"
    ]


MIN_PAIRWISE_N = 30  # cells below this (dry-runs) are excluded from contrasts


def pairwise_models(
    metrics_csv: Path | None = None, metric: str = "initial_defect_rate"
) -> list[dict]:
    """All pairwise model contrasts for a rate metric, Holm-corrected.

    ``metric`` must be expressible as x/n: initial_defect_rate (x=n_generated*
    rate), final_clean_rate, compile_rate, oracle_pass_rate.

    Cells with fewer than MIN_PAIRWISE_N generated samples (dry-runs,
    single-task probes) are excluded — contrasts against them are noise.
    """
    metrics_csv = metrics_csv or (RESULTS_ROOT / "metrics.csv")
    df = pd.read_csv(metrics_csv)
    df = df[df["n_generated"] >= MIN_PAIRWISE_N]
    pairs = {
        "initial_defect_rate": ("initial_flagged", "n_generated"),
        "final_clean_rate": (None, None),  # computed from counts below
        "compile_rate": ("n_compilable", "n_generated"),
        "oracle_pass_rate": ("oracle_passed", None),
    }
    results: list[dict] = []
    models = sorted(df["model"].unique())
    for a, b in itertools.combinations(models, 2):
        da = df[df["model"] == a]
        db = df[df["model"] == b]
        if metric == "final_clean_rate":
            x1 = int(da["clean_at_start"].sum() + da["cleaned"].sum())
            n1 = int(x1 + da["not_cleaned"].sum())
            x2 = int(db["clean_at_start"].sum() + db["cleaned"].sum())
            n2 = int(x2 + db["not_cleaned"].sum())
        else:
            xcol, ncol = pairs[metric]
            if metric == "oracle_pass_rate":
                n1 = int(da["oracle_passed"].sum() + da["oracle_failed"].sum())
                n2 = int(db["oracle_passed"].sum() + db["oracle_failed"].sum())
            else:
                n1 = int(da[ncol].sum())
                n2 = int(db[ncol].sum())
            x1 = int(da[xcol].sum())
            x2 = int(db[xcol].sum())
        if n1 == 0 or n2 == 0:
            continue
        results.append(compare_rates(x1, n1, x2, n2, a, b))
    return holm_correction(results)


def _model_summary(df: pd.DataFrame) -> list[str]:
    """Descriptive per-model table: rates + bootstrap CIs (works for 1..N models)."""
    rows = []
    for _, r in df.iterrows():
        n = int(r["n_generated"])
        if not n:
            continue
        row = {
            "model": r["model"],
            "cell": r["cell"],
            "n": n,
        }
        for label, col in [
            ("defect_rate", "initial_defect_rate"),
            ("defect_rate_static", "initial_defect_rate_static_only"),
            ("compile_rate", "compile_rate"),
            ("oracle_pass_rate", "oracle_pass_rate"),
        ]:
            val = r.get(col)
            row[label] = None if pd.isna(val) else round(float(val), 4)
        # bootstrap CIs for the two headline rates
        for label, x in [
            ("defect_ci", int(r["initial_flagged"])),
            ("compile_ci", int(r["n_compilable"])),
        ]:
            if x is not None and not pd.isna(x):
                lo, hi = bootstrap_ci(int(x), n)
                row[label] = f"[{lo:.2f}, {hi:.2f}]"
        rows.append(row)
    lines = ["## Per-model summary (rates with bootstrap 95% CIs)", ""]
    lines += [pd.DataFrame(rows).to_markdown(index=False), ""]
    lines += [
            "*CIs are percentile bootstrap (10,000 draws). `oracle_pass_rate` "
            "and `defect_rate` include dynamic channels only for cells "
            "measured with static+dynamic; `defect_rate_static` is static-only "
            "and always comparable across cells.*",
            "",
        ]
    return lines


def report(metrics_csv: Path | None = None, out: Path | None = None) -> Path:
    """Write the full stats report (markdown) for every rate metric."""
    out = out or (RESULTS_ROOT / "stats_report.md")
    metrics_csv = metrics_csv or (RESULTS_ROOT / "metrics.csv")
    lines = ["# Statistical report", ""]
    if not Path(metrics_csv).exists():
        lines += ["_No metrics found yet (run `metrics.py` after an experiment cell)._"]
        out.write_text("\n".join(lines))
        return out
    df = pd.read_csv(metrics_csv)

    # Descriptive section: always emitted, even for a single cell/model.
    lines += _model_summary(df)

    n_models = df["model"].nunique()
    if n_models < 2:
        lines += [
            "## Pairwise model contrasts",
            "",
            f"_Skipped: {n_models} model(s) present; pairwise comparisons "
            "(Fisher/chi-square, Mann-Whitney U) require at least 2 models._",
            "",
        ]
    else:
        if df.groupby("model")["cell"].nunique().max() > 1 or df["cell"].nunique() > 1:
            cells = sorted(df["cell"].unique())
            lines += [
                "## Pairwise model contrasts",
                "",
                f"*Note: cells differ in configuration ({', '.join(cells)}); "
                "interpret contrasts across mixed cells with caution.*",
                "",
            ]
    for metric, label in [
        ("initial_defect_rate", "Initial defect rate (flagged at heal_0)"),
        ("final_clean_rate", "Final clean rate"),
        ("compile_rate", "Compile rate"),
        ("oracle_pass_rate", "Oracle test pass rate"),
    ]:
        res = pairwise_models(metrics_csv, metric)
        if not res:
            continue
        lines += [f"## {label}", ""]
        dfres = pd.DataFrame(res)
        lines += [dfres.to_markdown(index=False), ""]
    # rounds-to-clean pairwise (same min-size exclusion as rate contrasts)
    big = df[df["n_generated"] >= MIN_PAIRWISE_N]
    rounds_res = []
    for a, b in itertools.combinations(sorted(big["model"].unique()), 2):
        r1 = load_cell_rounds(a, big[big["model"] == a]["cell"].iloc[0])
        r2 = load_cell_rounds(b, big[big["model"] == b]["cell"].iloc[0])
        if r1 and r2:
            rounds_res.append(compare_rounds(r1, r2, a, b))
    if rounds_res:
        lines += ["## Rounds-to-clean (Mann-Whitney U + Cliff's delta)", ""]
        lines += [pd.DataFrame(holm_correction(rounds_res)).to_markdown(index=False), ""]
    out.write_text("\n".join(lines))
    return out


if __name__ == "__main__":
    path = report()
    print(f"written -> {path}")

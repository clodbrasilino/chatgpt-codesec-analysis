"""Publication figures for the FSE 2027 extension.

All figures consume the tidy tables produced by metrics.py / cwe_map.py
and are written to results/figures/ as PDF (LaTeX inclusion) + SVG
(paper-editing workflow, like the v1 SVG figures).

Figures:
    fig_defect_rate     initial defect rate per model, 95% bootstrap CI
    fig_survival        fraction still flagged vs heal round per model
    fig_rounds          rounds-to-clean distribution per model
    fig_analyzers       stacked bar: which analyzer flagged (heal_0)
    fig_cwe_heatmap     model x CWE pillar heatmap of finding counts
    fig_ablation        feedback-channel contrast (static/dynamic/both/none)
"""
from __future__ import annotations

import json
from pathlib import Path

import matplotlib

matplotlib.use("Agg")
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

from .metrics import all_cells
from .stats import MIN_PAIRWISE_N, bootstrap_ci

REPO_ROOT = Path(__file__).resolve().parents[2]
RESULTS_ROOT = REPO_ROOT / "results"
FIG_DIR = RESULTS_ROOT / "figures"

# colorblind-safe palette (Okabe-Ito)
OI = [
    "#0072B2", "#E69F00", "#009E73", "#D55E00", "#CC79A7",
    "#56B4E9", "#F0E442", "#000000", "#999999",
]

plt.rcParams.update(
    {
        "figure.dpi": 150,
        "savefig.bbox": "tight",
        "font.size": 10,
        "axes.spines.top": False,
        "axes.spines.right": False,
        "axes.grid": True,
        "grid.alpha": 0.25,
    }
)


def _save(fig: plt.Figure, name: str) -> list[Path]:
    FIG_DIR.mkdir(parents=True, exist_ok=True)
    paths = []
    for ext in ("pdf", "svg"):
        p = FIG_DIR / f"{name}.{ext}"
        fig.savefig(p)
        paths.append(p)
    plt.close(fig)
    return paths


def _metrics_df() -> pd.DataFrame:
    df = pd.DataFrame(all_cells())
    # Exclude dry-run/probe cells from plots (same rule as stats contrasts):
    # a 2-sample cell would draw a bogus 0%-defect bar with a fake-tight CI.
    if not df.empty and "n_generated" in df:
        df = df[df["n_generated"] >= MIN_PAIRWISE_N]
    return df


# ---------------------------------------------------------------------------

def fig_defect_rate(df: pd.DataFrame | None = None) -> list[Path]:
    df = df if df is not None else _metrics_df()
    if df.empty:
        return []
    agg = (
        df.groupby("model")
        .agg(flagged=("initial_flagged", "sum"), n=("n_generated", "sum"))
        .reset_index()
    )
    agg["rate"] = agg["flagged"] / agg["n"]
    agg = agg.sort_values("rate", ascending=False)
    fig, ax = plt.subplots(figsize=(6, 3.2))
    xs = np.arange(len(agg))
    rates = agg["flagged"] / agg["n"]
    errors = np.array(
        [
            [r - bootstrap_ci(x, n)[0], bootstrap_ci(x, n)[1] - r]
            for r, x, n in zip(rates, agg["flagged"], agg["n"])
        ]
    ).T
    ax.bar(xs, rates, color=OI[0], width=0.62)
    ax.errorbar(xs, rates, yerr=errors, fmt="none", ecolor="black", capsize=4, lw=1.2)
    ax.set_xticks(xs, agg["model"], rotation=30, ha="right")
    ax.set_ylabel("Initial defect rate")
    ax.set_ylim(0, 1)
    for x, r in zip(xs, rates):
        ax.text(x, r + 0.03, f"{r:.2f}", ha="center", fontsize=8)
    return _save(fig, "fig_defect_rate")


def fig_survival(df: pd.DataFrame | None = None) -> list[Path]:
    df = df if df is not None else _metrics_df()
    if df.empty or "survival_counts" not in df:
        return []
    fig, ax = plt.subplots(figsize=(5.5, 3.4))
    for i, row in enumerate(df.itertuples()):
        try:
            surv = json.loads(row.survival_counts)
        except (TypeError, json.JSONDecodeError):
            continue
        if not surv:
            continue
        rounds = sorted(int(k) for k in surv)
        n0 = max(surv.values())
        if n0 == 0:
            continue
        fracs = [surv[str(r)] if str(r) in surv else surv[r] for r in rounds]
        fracs = [f / n0 for f in fracs]
        ax.step(
            rounds, fracs, where="post", marker="o", ms=3.5,
            color=OI[i % len(OI)], label=f"{row.model}/{row.cell}",
        )
    ax.set_xlabel("Heal round")
    ax.set_ylabel("Fraction still flagged")
    ax.set_ylim(0, 1.02)
    ax.legend(fontsize=7, loc="upper right")
    return _save(fig, "fig_survival")


def fig_rounds(df: pd.DataFrame | None = None) -> list[Path]:
    df = df if df is not None else _metrics_df()
    if df.empty:
        return []
    fig, ax = plt.subplots(figsize=(6, 3.2))
    models = sorted(df["model"].unique())
    data, labels = [], []
    for m in models:
        rounds: list[int] = []
        for row in df[df["model"] == m].itertuples():
            mf = RESULTS_ROOT / m / f"{row.cell}.manifest.json"
            if mf.exists():
                man = json.loads(mf.read_text())
                rounds += [
                    o["rounds_to_clean"]
                    for o in man["outcomes"].values()
                    if o["outcome"] == "clean"
                ]
        if rounds:
            data.append(rounds)
            labels.append(m)
    if not data:
        plt.close(fig)
        return []
    bp = ax.boxplot(data, tick_labels=labels, patch_artist=True, widths=0.5)
    for patch, color in zip(bp["boxes"], OI):
        patch.set_facecolor(color)
        patch.set_alpha(0.65)
    ax.set_ylabel("Rounds to clean")
    ax.tick_params(axis="x", rotation=30)
    for tick in ax.get_xticklabels():
        tick.set_ha("right")
    return _save(fig, "fig_rounds")


def fig_analyzers(df: pd.DataFrame | None = None) -> list[Path]:
    df = df if df is not None else _metrics_df()
    if df.empty:
        return []
    tools = ["gcc", "clang", "cppcheck", "flawfinder"]
    agg = df.groupby("model")[[f"flagged_{t}" for t in tools]].sum()
    # de-overlap is not possible from counts alone; stack = "flagged by N tools"
    agg = agg.reindex(agg.sum(axis=1).sort_values(ascending=False).index)
    fig, ax = plt.subplots(figsize=(6, 3.2))
    bottom = np.zeros(len(agg))
    xs = np.arange(len(agg))
    for i, t in enumerate(tools):
        vals = agg[f"flagged_{t}"].to_numpy()
        ax.bar(xs, vals, bottom=bottom, color=OI[i], width=0.6, label=t)
        bottom += vals
    ax.set_xticks(xs, agg.index, rotation=30, ha="right")
    ax.set_ylabel("Files flagged (tool occurrences)")
    ax.legend(fontsize=8)
    return _save(fig, "fig_analyzers")


def fig_cwe_heatmap(cwes_csv: Path | None = None, top_k: int = 12) -> list[Path]:
    from .cwe_map import all_cells_cwes

    csv_path = cwes_csv or (RESULTS_ROOT / "cwes_by_problem.csv")
    if csv_path.exists():
        df = pd.read_csv(csv_path)
    else:
        df = all_cells_cwes()
    if df.empty:
        return []
    top = (
        df.groupby("pillar")["frequency"].sum().sort_values(ascending=False).head(top_k)
    )
    pillars = top.index.tolist()
    sub = df[df["pillar"].isin(pillars)]
    mat = (
        sub.pivot_table(index="model", columns="pillar", values="frequency", aggfunc="sum")
        .reindex(columns=pillars)
        .fillna(0)
    )
    fig, ax = plt.subplots(figsize=(1.1 + 0.55 * len(pillars), 1.2 + 0.5 * len(mat)))
    im = ax.imshow(mat.to_numpy(), aspect="auto", cmap="Blues")
    ax.set_xticks(range(len(pillars)), [f"CWE-{p}" for p in pillars], rotation=45, ha="right")
    ax.set_yticks(range(len(mat)), mat.index)
    for i in range(mat.shape[0]):
        for j in range(mat.shape[1]):
            v = int(mat.iloc[i, j])
            if v:
                ax.text(j, i, str(v), ha="center", va="center", fontsize=7,
                        color="white" if v > mat.to_numpy().max() * 0.6 else "black")
    fig.colorbar(im, ax=ax, shrink=0.8, label="findings")
    ax.grid(False)
    return _save(fig, "fig_cwe_heatmap")


def fig_ablation(df: pd.DataFrame | None = None) -> list[Path]:
    df = df if df is not None else _metrics_df()
    if df.empty or df["cell"].nunique() < 2:
        return []
    # one model per feedback channel comparison: use the most common model
    df = df.copy()
    df["feedback"] = df["cell"].str.extract(r"feedback-([a-z+]+)-")
    agg = (
        df.groupby("feedback")
        .agg(flagged=("initial_flagged", "sum"), n=("n_generated", "sum"),
             clean=("clean_at_start", "sum"), cleaned=("cleaned", "sum"),
             not_cleaned=("not_cleaned", "sum"))
        .reset_index()
    )
    if len(agg) < 2:
        return []
    agg["initial_rate"] = agg["flagged"] / agg["n"]
    total = agg["clean"] + agg["cleaned"] + agg["not_cleaned"]
    agg["final_clean"] = (agg["clean"] + agg["cleaned"]) / total.replace(0, np.nan)
    order = ["none", "static", "dynamic", "static+dynamic"]
    agg["feedback"] = pd.Categorical(agg["feedback"], categories=order, ordered=True)
    agg = agg.sort_values("feedback")

    fig, axes = plt.subplots(1, 2, figsize=(7.5, 3.0))
    xs = np.arange(len(agg))
    axes[0].bar(xs, agg["initial_rate"], color=OI[1], width=0.6)
    axes[0].set_xticks(xs, agg["feedback"], rotation=20, ha="right")
    axes[0].set_ylabel("Initial defect rate")
    axes[1].bar(xs, agg["final_clean"], color=OI[2], width=0.6)
    axes[1].set_xticks(xs, agg["feedback"], rotation=20, ha="right")
    axes[1].set_ylabel("Final clean rate")
    axes[1].set_ylim(0, 1)
    return _save(fig, "fig_ablation")


ALL_FIGURES = {
    "fig_defect_rate": fig_defect_rate,
    "fig_survival": fig_survival,
    "fig_rounds": fig_rounds,
    "fig_analyzers": fig_analyzers,
    "fig_cwe_heatmap": fig_cwe_heatmap,
    "fig_ablation": fig_ablation,
}

if __name__ == "__main__":
    written = []
    for name, fn in ALL_FIGURES.items():
        try:
            paths = fn()
            written += paths
            print(f"{name}: {len(paths)} file(s)")
        except Exception as ex:  # noqa: BLE001
            print(f"{name}: SKIPPED ({type(ex).__name__}: {ex})")
    print(f"\nfigures -> {FIG_DIR}")

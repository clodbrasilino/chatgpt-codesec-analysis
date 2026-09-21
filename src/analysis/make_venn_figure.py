"""Build the three-panel Venn figure for problem-level channel contribution.

Panel 1: channel level  -- Static / Tests / Dynamic (oracle+fuzzer)
Panel 2: static tools   -- cppcheck / gcc / clang / flawfinder (4-set)
Panel 3: dynamic tools  -- ASan / UBSan / AFL++

Counts come from results/problem_channel_venn.json (computed by
src.analysis.problem_channel_venn). All panels use a fixed-shape layout
with numeric region verification: every region must exist geometrically
and its label is placed at the centroid of its LARGEST CONNECTED
COMPONENT (scipy.ndimage), so a count can never be attributed to the
wrong region visually. Zero-count regions are left unlabeled.

Key-normalization note: JSON region keys are "+"-joined name lists, and
the tool name "AFL++" itself contains "+", so membership is resolved by
substring match against each panel's set names (names are chosen to be
non-embedding: "ASan" is not a substring of "UBSan", etc.).

Output: figures/venn_channels.pdf and .png in the paper repo.
"""
from __future__ import annotations

import json
import sys
from pathlib import Path

import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Circle, Ellipse
from scipy import ndimage

REPO = Path(__file__).resolve().parents[2]
DATA = json.loads((REPO / "results" / "problem_channel_venn.json").read_text())
OUTDIR = Path("/Users/clodbrasilino/workspaces/zju/fse2027paper/figures")
OUTDIR.mkdir(exist_ok=True)

N = DATA["N"]

# ----------------------------------------------------------- generic engine
def normalize(d: dict, names: list[str]) -> dict[frozenset, int]:
    """Map frozenset-of-set-names -> count, resolving 'AFL++' safely."""
    out = {}
    for k, v in d.items():
        if k == "none":
            continue
        out[frozenset(n for n in names if n in k)] = v
    return out


def region_centroid(memb: np.ndarray, mask: int, gx: np.ndarray,
                    gy: np.ndarray) -> tuple[float, float]:
    """Centroid of the largest connected component of region `mask`."""
    sel = np.ones(memb.shape[:2], dtype=bool)
    for i in range(memb.shape[2]):
        sel &= memb[:, :, i] if mask >> i & 1 else ~memb[:, :, i]
    lab, n = ndimage.label(sel)
    assert n > 0, f"region {mask:04b} empty in layout"
    sizes = ndimage.sum_labels(np.ones_like(lab), lab, index=range(1, n + 1))
    keep = int(np.argmax(sizes)) + 1
    ys, xs = np.where(lab == keep)
    return float(gx[ys, xs].mean()), float(gy[ys, xs].mean())


def draw_shapes(ax, shapes, colors, names, lab_pos, sets_counts, title,
                xlim, ylim, total_pos):
    lookup = normalize(sets_counts, names)
    gx, gy = np.meshgrid(np.linspace(*xlim, 1500), np.linspace(*ylim, 1500))
    pts = np.column_stack([gx.ravel(), gy.ravel()])

    def membership(pts, ell):
        cx, cy, a, b, th = ell
        t = np.radians(th)
        dx, dy = pts[:, 0] - cx, pts[:, 1] - cy
        xr = dx * np.cos(-t) - dy * np.sin(-t)
        yr = dx * np.sin(-t) + dy * np.cos(-t)
        return ((xr / a) ** 2 + (yr / b) ** 2 <= 1.0).astype(bool)

    mflat = np.column_stack([membership(pts, e) for e in shapes])
    memb = mflat.reshape(gx.shape + (len(shapes),))

    for ell, col in zip(shapes, colors):
        cx, cy, a, b, th = ell
        patch = (Circle((cx, cy), a) if abs(b - a) < 1e-9
                 else Ellipse((cx, cy), 2 * a, 2 * b, angle=th))
        patch.set(facecolor=col, alpha=0.35, edgecolor="0.35", linewidth=0.8)
        ax.add_patch(patch)

    for mask in range(1, 1 << len(shapes)):
        sel_names = frozenset(names[i] for i in range(len(shapes))
                              if mask >> i & 1)
        cnt = lookup.get(sel_names, 0)
        if cnt == 0:
            continue
        x, y = region_centroid(memb, mask, gx, gy)
        ax.text(x, y, str(cnt), ha="center", va="center",
                fontsize=8 if cnt >= 10 else 7,
                bbox=dict(boxstyle="round,pad=0.15", fc="white",
                          ec="none", alpha=0.8))
    for (x, y), name, col in zip(lab_pos, names, colors):
        ax.text(x, y, name, fontsize=9, color=col, weight="bold",
                ha="center")
    total = sum(lookup.get(frozenset(names[i] for i in range(len(shapes))
                                     if m >> i & 1), 0)
                for m in range(1, 1 << len(shapes)))
    ax.text(total_pos[0], total_pos[1],
            f"problems with any detection: {total}/{N}",
            ha="center", fontsize=7, style="italic", color="0.3")
    ax.set_xlim(*xlim)
    ax.set_ylim(*ylim)
    ax.set_aspect("equal")
    ax.axis("off")
    ax.set_title(title, fontsize=9)


def main() -> None:
    fig, axes = plt.subplots(1, 3, figsize=(9.2, 3.2))

    # three-circle layout: set0 top-left, set1 bottom-left, set2 right
    d = 0.45
    tri = [(-d, d * np.sqrt(3) / 2 * 0.55, 0.9, 0.9, 0),
           (-d * 0.72, -d * 0.72, 0.9, 0.9, 0),
           (d * 0.9, -d * 0.55, 0.9, 0.9, 0)]
    tri_labs = [(-1.35, 1.15), (-1.45, -1.4), (1.55, -0.55)]

    # (a) channels; the third set is oracle+fuzzer EXCLUDING tests --
    # it must not be labeled "Dynamic" (that channel includes tests)
    v1 = {k.replace("Dynamic", "Oracle+Fuzz"): v
          for k, v in DATA["venn1"].items()}
    draw_shapes(
        axes[0], tri,
        ["#4c72b0", "#dd8452", "#55a868"],
        ["Static", "Tests", "Oracle+Fuzz"], tri_labs,
        v1, "(a) Channels (problems, all models)",
        (-2.1, 2.1), (-1.7, 1.7), (0.0, -1.95))

    # (b) static tools: 4-ellipse layout (all 15 regions verified present)
    draw_shapes(
        axes[1],
        [(-0.50, 0.34, 1.20, 0.56, -34),
         (0.50, 0.34, 1.20, 0.56, 34),
         (-0.50, -0.34, 1.20, 0.56, 34),
         (0.50, -0.34, 1.20, 0.56, -34)],
        ["#4c72b0", "#c44e52", "#8172b3", "#937860"],
        ["cppcheck", "gcc", "clang", "flawfinder"],
        [(-1.85, 0.72), (1.85, 0.72), (-1.85, -0.82), (1.85, -0.82)],
        DATA["venn2"], "(b) Static tools (problems, all models)",
        (-2.2, 2.2), (-1.8, 1.8), (0.0, -1.62))

    # (c) dynamic tools
    draw_shapes(
        axes[2], tri,
        ["#c44e52", "#4c72b0", "#55a868"],
        ["ASan", "UBSan", "AFL++"], tri_labs,
        DATA["venn3"], "(c) Dynamic tools (problems, all models)",
        (-2.1, 2.1), (-1.7, 1.7), (0.0, -1.95))

    fig.tight_layout()
    fig.savefig(OUTDIR / "venn_channels.pdf", bbox_inches="tight")
    fig.savefig(OUTDIR / "venn_channels.png", dpi=160, bbox_inches="tight")
    print(f"written -> {OUTDIR}/venn_channels.pdf/.png")


if __name__ == "__main__":
    sys.exit(main())

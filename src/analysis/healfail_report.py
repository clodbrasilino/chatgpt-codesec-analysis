"""Detail every heal_failed inside the five-round analysis window.

For each cell we report: model, cell, gate/ablation class, total programs,
heal_failed total, and the breakdown of those failures by the round at
which they occurred, split into failures inside the window (rounds 1-5,
which compromise the five-round analysis) and beyond it.

Additionally, every in-window failed program is classified by its ledger
error string (ok == false rows carry an `error` field): account-standing
(provider rejected calls, e.g. "Access denied ... account") vs transport
(connection failures, disconnects, timeouts, server errors) vs other.
"""
from __future__ import annotations

import json
import re
from pathlib import Path
from collections import Counter, defaultdict

REPO = Path(__file__).resolve().parents[2]
RES = REPO / "results"
COLL = REPO / "data" / "collected_code_6"
CAP = 5
KEY_RE = re.compile(r"^problem-(\d+)(?:-s(\d+))?$")
ACCOUNT_PAT = re.compile(r"access denied|account|insufficient|forbidden",
                         re.I)
TRANSPORT_PAT = re.compile(r"connection|timed out|timeout|disconnect"
                           r"|apiconnectionerror|internal server error"
                           r"|server error|50[23]", re.I)


def cell_class(model: str, slug: str) -> str:
    if model.endswith("-thinking"):
        base = "ablation: extended-reasoning (thinking)"
    else:
        base = "main"
    gate = ("static+dynamic" if "static+dynamic" in slug
            else "dynamic only" if "dynamic" in slug
            else "static only" if "static" in slug else slug)
    if model.endswith("-thinking"):
        gate = gate
    temp_p = ""
    if "-t0.2" in slug:
        temp_p = ", grid (t=0.2)"
    elif "-p0.5" in slug:
        temp_p = ", grid (p=0.5)"
    if "static+dynamic" in slug and model.endswith("-thinking"):
        cls = f"{base} — gate {gate}"
    elif gate != "static+dynamic" and not model.endswith("-thinking"):
        cls = f"ablation: {gate} feedback"
    elif temp_p:
        cls = f"ablation: sampling grid{temp_p}"
    elif model.endswith("-thinking"):
        cls = f"{base} — gate {gate}"
    else:
        cls = f"{base} — gate {gate}"
    if "all" in slug or True:
        pass
    return cls + (" [subset]" if "subset" in _tasks_of(slug, model) else "")


def _tasks_of(slug: str, model: str) -> str:
    mf = RES / model / f"{slug}.manifest.json"
    if not mf.is_file():
        return ""
    try:
        m = json.loads(mf.read_text())
        c = m.get("cell", {}) or {}
        return str(c.get("tasks", ""))
    except Exception:
        return ""


def classify_error(err: str) -> str:
    if ACCOUNT_PAT.search(err):
        return "account-standing"
    if TRANSPORT_PAT.search(err):
        return "transport"
    return "other"


def ledger_errors(model: str, slug: str) -> dict[tuple[int, int], list[str]]:
    """(task_id, round) -> [error strings] over failed ledger rows."""
    out: dict[tuple[int, int], list[str]] = defaultdict(list)
    path = RES / model / f"{slug}.usage.jsonl"
    if not path.is_file():
        return out
    with open(path) as f:
        for line in f:
            try:
                e = json.loads(line)
            except json.JSONDecodeError:
                continue
            if e.get("ok") is not True and e.get("error"):
                out[(e.get("task_id"), e.get("round"))].append(e["error"])
    return out


def main() -> None:
    rows = []
    for model_dir in sorted(COLL.iterdir()):
        if not model_dir.is_dir():
            continue
        model = model_dir.name
        for slug_dir in sorted(model_dir.iterdir()):
            if not slug_dir.is_dir() or "legacy" in slug_dir.name:
                continue
            slug = slug_dir.name
            mf = RES / model / f"{slug}.manifest.json"
            if not mf.is_file():
                continue
            m = json.loads(mf.read_text())
            outcomes = m.get("outcomes", {})
            rounds = Counter()
            for base, v in outcomes.items():
                if isinstance(v, dict) and v.get("outcome") == "heal_failed":
                    rounds[v.get("rounds_to_clean")] += 1
            total_fail = sum(rounds.values())
            if total_fail == 0:
                continue
            in_win = {r: c for r, c in rounds.items()
                      if isinstance(r, int) and 1 <= r <= CAP}
            out_win = {r: c for r, c in rounds.items()
                       if not (isinstance(r, int) and 1 <= r <= CAP)}
            rows.append({
                "model": model, "slug": slug,
                "cls": cell_class(model, slug),
                "n": len(outcomes), "total_fail": total_fail,
                "in": in_win, "out": out_win,
                "in_total": sum(in_win.values()),
            })

    lines = ["# heal_failed detail — five-round analysis window", "",
             "Every `heal_failed` program in every non-legacy cell, broken down",
             "by the round at which the failure occurred. Failures in rounds 1-5",
             "fall inside the reporting horizon and therefore compromise the",
             "five-round analysis of that cell; failures beyond round 5 do not.", ""]
    lines.append("| Model | Cell | Class | n | failed (all) | failed in r1-5 | r1 | r2 | r3 | r4 | r5 | failed r>5 |")
    lines.append("|---|---|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|")
    tot_all = tot_in = 0
    for r in sorted(rows, key=lambda x: (-x["in_total"], -x["total_fail"])):
        tot_all += r["total_fail"]
        tot_in += r["in_total"]
        g = r["in"].get
        lines.append(
            f"| {r['model']} | `{r['slug']}` | {r['cls']} | {r['n']} | "
            f"{r['total_fail']} | **{r['in_total']}** | {g(1,0)} | {g(2,0)} | "
            f"{g(3,0)} | {g(4,0)} | {g(5,0)} | {sum(r['out'].values())} |")
    lines.append(f"| **TOTAL** | --- | --- | --- | **{tot_all}** | **{tot_in}** | "
                 + " | ".join(str(sum(rw['in'].get(i, 0) for rw in rows))
                              for i in range(1, 6))
                 + f" | {sum(sum(rw['out'].values()) for rw in rows)} |")
    lines.append("")
    lines.append("## Cells with no failures inside the window")
    lines.append("")
    lines.append("Every cell not listed above has zero `heal_failed` programs in "
                 "rounds 1-5; in particular all seven main (static+dynamic, "
                 "full-task) cells are clean inside the window except where "
                 "listed.")

    # ---- failure classification from ledger error strings ----
    classes = Counter()
    examples: dict[str, str] = {}
    for r in rows:
        led = ledger_errors(r["model"], r["slug"])
        mf = json.loads((RES / r["model"] / f"{r['slug']}.manifest.json")
                        .read_text())
        for base, v in mf.get("outcomes", {}).items():
            if not (isinstance(v, dict)
                    and v.get("outcome") == "heal_failed"):
                continue
            fr = v.get("rounds_to_clean")
            if not (isinstance(fr, int) and 1 <= fr <= CAP):
                continue
            m = KEY_RE.match(base)
            if not m:
                continue
            task = int(m.group(1))
            sample = int(m.group(2)) if m.group(2) else None
            errs = [e for (t, rd), es in led.items() if t == task and rd == fr
                    for e in es]
            if sample is not None:
                keyed = [e for (t, rd), es in led.items() if t == task
                         and rd == fr for e in es]
                errs = keyed  # round+task is specific enough; classify all
            if not errs:
                cls = "no-ledger-error"
            else:
                cls = classify_error(" | ".join(errs))
            classes[cls] += 1
            examples.setdefault(cls, errs[0][:160] if errs else "")
    lines += ["", "## Failure classification (in-window programs, from "
              "ledger error strings)", "",
              "Rules (first match wins): account-standing = error matches",
              "`access denied|account|insufficient|forbidden`; transport =",
              "`connection|timed out|timeout|disconnect|apiconnectionerror|",
              "internal server error|server error|50[23]`; everything else",
              "falls into other.", "",
              "| Class | programs |", "|---|---:|"]
    for cls in ("account-standing", "transport", "other", "no-ledger-error"):
        if classes.get(cls):
            lines.append(f"| {cls} | {classes[cls]} |")
    lines += ["", "Example error per class:", ""]
    for cls, ex in examples.items():
        lines.append(f"- {cls}: `{ex}`")
    lines.append("")
    out = RES / "healfail_report.md"
    out.write_text("\n".join(lines) + "\n")
    print(f"cells with failures: {len(rows)}  total_failed={tot_all}  "
          f"inside_window={tot_in}")
    for r in sorted(rows, key=lambda x: -x["in_total"])[:12]:
        print(f"  {r['model']:22s} {r['slug']:38s} in={r['in_total']:4d} "
              f"by_round={dict(sorted(r['in'].items()))}")
    print(f"written -> {out}")


if __name__ == "__main__":
    main()

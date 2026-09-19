"""Flawfinder report normalization.

Flawfinder 2.0.19 emits a human-readable report whose hit lines do NOT
match the pipeline's standard ``file:line:col:severity:message`` format:

    /abs/path/problem-10.c:30:  [2] (buffer) memcpy:
      Does not check for buffer overflows when copying to destination (CWE-120).
      Make sure destination can always hold the source data.

Historical bug (fixed 2026-09-19): ``comment_inject`` parsed ALL report
suffixes with the standard parser, so flawfinder hits were silently
dropped from the repair feedback. This module provides:

- ``extract_flawfinder_raw(text)``: parse hits from the RAW format;
- ``normalize_report(text, basename)``: convert a raw report into the
  standard format (empty output when there are no hits, matching the
  other analyzers' clean reports);
- ``severity_for_risk(risk)``: risk level (1..5) -> severity.

The normalized hit format is::

    problem-10.c:30:0:medium:Flawfinder memcpy: Does not check for
    buffer overflows when copying to destination (CWE-120). Make sure
    destination can always hold the source data. (risk 2, buffer)
"""
from __future__ import annotations

import re

# Raw hit header: "<abspath>/<basename>.c:<line>:  [<risk>] (<type>) <name>:"
_HIT_RE = re.compile(
    r"^.*[/\\](problem-[\w.-]+\.c):(\d+):\s+\[(\d+)\]\s+\(([^)]*)\)\s*(.*?):\s*$"
)
_STOP_RE = re.compile(
    r"^(Flawfinder version|Number of rules|Examining |FINAL RESULTS|"
    r"ANALYSIS SUMMARY|No hits found|Lines analyzed|Physical Source|"
    r"Hits@|Hits/KSLOC|Minimum risk|There may be other|"
    r"See 'Secure Programming|\(https)"
)


def severity_for_risk(risk: int) -> str:
    if risk >= 4:
        return "high"
    if risk >= 2:
        return "medium"
    return "low"


def extract_flawfinder_raw(text: str) -> list[dict]:
    """Parse hits from RAW flawfinder output -> [{line, message}]."""
    out: list[dict] = []
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        m = _HIT_RE.match(lines[i])
        if not m:
            i += 1
            continue
        line_no = int(m.group(2))
        risk = int(m.group(3))
        typ = m.group(4)
        name = m.group(5)
        body: list[str] = []
        j = i + 1
        while j < len(lines):
            s = lines[j].strip()
            if (not s or _STOP_RE.match(s) or _HIT_RE.match(lines[j])):
                break
            body.append(s)
            j += 1
        out.append({
            "line": line_no,
            "message": (f"Flawfinder {name}: {' '.join(body)} "
                        f"(risk {risk}, {typ})"),
        })
        i = j
    return out


def normalize_report(text: str, basename: str) -> str:
    """Convert a raw flawfinder report to the standard report format.

    Returns "" when the report contains no hits (consistent with the
    other analyzers' clean reports).
    """
    hits = extract_flawfinder_raw(text)
    if not hits:
        return ""
    # Risk level is not in the parsed message; re-extract for severity.
    out_lines: list[str] = []
    lines = text.split("\n")
    i = 0
    while i < len(lines):
        m = _HIT_RE.match(lines[i])
        if not m:
            i += 1
            continue
        line_no, risk, typ, name = int(m.group(2)), int(m.group(3)), m.group(4), m.group(5)
        body: list[str] = []
        j = i + 1
        while j < len(lines):
            s = lines[j].strip()
            if (not s or _STOP_RE.match(s) or _HIT_RE.match(lines[j])):
                break
            body.append(s)
            j += 1
        sev = severity_for_risk(risk)
        msg = f"Flawfinder {name}: {' '.join(body)} (risk {risk}, {typ})"
        out_lines.append(f"{basename}.c:{line_no}:0:{sev}:{msg}")
        i = j
    return "\n".join(out_lines) + "\n"

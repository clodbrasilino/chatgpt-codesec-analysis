"""Locate the function-under-test inside generated C source (fuzzy match).

LLM-generated names drift (``extract_string`` -> ``extractStrings``,
``remove_words`` -> ``removeWords``), so we match by normalized similarity
instead of exact equality. Because the driver is appended to the same
translation unit, the compiler re-validates any match against the real
definition, so a wrong fuzzy hit fails cheaply at compile time.
"""
from __future__ import annotations

import difflib
import re

# Matches a C function definition at statement level, including pointer
# return types with no whitespace before the name (e.g. ``char **name(...)``):
#   <return type (optional stars)> <name>(<params>) {
_FN_DEF_RE = re.compile(
    r"(?m)^\s*(?:[\w\s\*\[\]]*?\**)([A-Za-z_]\w*)\s*\(([^;{}]*)\)\s*\{"
)
_MAIN_RE = re.compile(r"^int\s+main\b")

# C keywords that can be followed by ``(...) {`` and are not functions.
_KEYWORDS = {
    "if", "for", "while", "switch", "return", "do", "else", "sizeof",
    "typeof", "typedef", "struct", "union", "enum", "static_assert",
}

_ACCEPT_RATIO = 0.82


def _norm(name: str) -> str:
    return re.sub(r"[^a-z0-9]", "", name.lower())


def _best_ratio(found_norm: str, candidates: list[str]) -> float:
    return max(
        (difflib.SequenceMatcher(None, found_norm, _norm(c)).ratio() for c in candidates),
        default=0.0,
    )


def find_function(source: str, candidates: list[str]) -> dict | None:
    """Return {name, line} of the best-matching function definition.

    Accepts the definition whose normalized name best matches any candidate
    (exact or similarity >= _ACCEPT_RATIO). ``main`` and control-flow
    keywords are never considered.
    """
    cand_norms = [_norm(c) for c in candidates if c]
    if not cand_norms:
        return None
    best = None
    best_score = 0.0
    for m in _FN_DEF_RE.finditer(source):
        name = m.group(1)
        if name in _KEYWORDS or _MAIN_RE.match(m.group(0)):
            continue
        norm = _norm(name)
        if norm in cand_norms:
            score = 1.0
        else:
            score = _best_ratio(norm, candidates)
        if score >= _ACCEPT_RATIO and score > best_score:
            line = source[: m.start()].count("\n") + 1
            best = {"name": name, "line": line, "params": m.group(2).strip(), "score": score}
            best_score = score
    return best


def detect_input_consumption(source: str) -> list[str]:
    """Which input interfaces does the program use? (for CLI mode / fuzzing)"""
    found = []
    for token in ("scanf", "fgets", "gets", "getchar", "argc", "argv",
                  "fread", "read(", "fscanf", "getline"):
        if re.search(rf"\b{re.escape(token)}\b", source):
            found.append(token)
    return found

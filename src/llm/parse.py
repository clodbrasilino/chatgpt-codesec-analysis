"""LLM output sanitization: turn raw model output into compilable C.

Extends the v1 logic from ``sanitize_llm_outputs_into_sources.py``:
- strips ```c / ```C markdown fences,
- handles fence-less outputs (code is often the only content),
- drops trailing explanatory prose after the code block.
"""
from __future__ import annotations

import re

_FENCE_OPEN = re.compile(r"^[ \t]*```[cC]\s*$", re.MULTILINE)
_FENCE_CLOSE = re.compile(r"^[ \t]*```\s*$", re.MULTILINE)
_ANY_FENCE_OPEN = re.compile(r"^[ \t]*```[a-zA-Z0-9_+-]*\s*$", re.MULTILINE)


def sanitize_llm_output(input: str) -> str:
    """Return the C source extracted from a raw LLM response."""
    output = input or ""
    # Case 1: fenced block(s). Take the LAST ```c ... ``` block; if none has a
    # language tag, take the last ``` ... ``` block.
    open_match = list(_FENCE_OPEN.finditer(output))
    if open_match:
        start = open_match[-1].end()
        close = _FENCE_CLOSE.search(output, start)
        return output[start : close.start() if close else None].strip()
    any_open = list(_ANY_FENCE_OPEN.finditer(output))
    if any_open:
        start = any_open[-1].end()
        close = _FENCE_CLOSE.search(output, start)
        return output[start : close.start() if close else None].strip()
    # Case 2: no fences at all — v1 behaviour stripped everything before a
    # fence, so fence-less output was returned untouched. Keep it, but drop
    # a trailing "Here is the code:" style header if present.
    output = re.sub(r"^[ \t]*(here(‘s| is) (the )?(c code|code|solution)([:.]?)[ \t]*\n)", "", output, flags=re.IGNORECASE)
    return output.strip()


def sanitize_llm_outputs_into_sources(path: str) -> None:
    """v1-compatible helper: write .c next to each raw .txt in ``path``."""
    from os import listdir
    from os.path import exists, isfile, join

    for filename in listdir(path):
        full = join(path, filename)
        if filename.endswith(".txt") and not filename.endswith((".gcc.txt", ".cppcheck.txt", ".flawfinder.txt", ".clang.txt", ".asan.txt", ".fuzz.txt", ".test.txt")):
            if not exists(full[:-4] + ".c"):
                with open(full) as f:
                    content = f.read()
                with open(full[:-4] + ".c", "w") as out:
                    out.write(sanitize_llm_output(content))

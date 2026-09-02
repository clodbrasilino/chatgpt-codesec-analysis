"""Render Python literals as C initializers (for driver generation).

Only the literal subset that can appear inside MBPP asserts is supported:
int, float, str, bool, and one/two-dimensional homogeneous lists thereof.
Anything else raises ValueError and the caller marks the task untestable.
"""
from __future__ import annotations

import json


def c_bool(v: bool) -> str:
    return "1" if v else "0"


def c_int(v: int) -> str:
    return str(v)


def c_float(v: float) -> str:
    s = repr(float(v))
    if "e" in s or "E" in s or "." in s:
        return s
    return s + ".0"


def c_str(v: str) -> str:
    # json.dumps yields a double-quoted literal with C-compatible escapes
    # for ", \\, \n, \t, \r, and control characters.
    return json.dumps(v)


def c_char(v: str) -> str:
    if len(v) != 1:
        raise ValueError(f"not a char: {v!r}")
    return "'" + v.replace("\\", "\\\\").replace("'", "\\'") + "'"


def c_list(v: list, elem_kind: str) -> str:
    if elem_kind == "int":
        items = [str(x) for x in v]
    elif elem_kind == "float":
        items = [c_float(x) for x in v]
    elif elem_kind == "str":
        items = [c_str(x) for x in v]
    elif elem_kind == "bool":
        items = [c_bool(x) for x in v]
    else:
        raise ValueError(f"unsupported list element kind {elem_kind}")
    return "{" + ", ".join(items) + "}"


def c_2d(v: list, elem_kind: str) -> str:
    rows = [c_list(r, elem_kind) for r in v]
    return "{" + ", ".join(rows) + "}"


def c_literal(value, kind: str) -> str:
    """Render a Python value as a C initializer given its MBPP arg kind."""
    if kind == "bool":
        return c_bool(value)
    if kind == "int":
        return c_int(value)
    if kind == "float":
        return c_float(value)
    if kind == "str":
        return c_str(value)
    if kind == "int-list":
        return c_list(value, "int")
    if kind == "float-list":
        return c_list(value, "float")
    if kind == "str-list":
        return c_list(value, "str")
    if kind == "bool-list":
        return c_list(value, "bool")
    if kind == "2d-int":
        return c_2d(value, "int")
    if kind == "2d-float":
        return c_2d(value, "float")
    raise ValueError(f"unsupported kind {kind!r} for value {value!r}")


def kind_of(value) -> str:
    """Mirror of mbpp_loader._kind_of kept here so driver_gen stays self-contained."""
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int"
    if isinstance(value, float):
        return "float"
    if isinstance(value, str):
        return "str"
    if isinstance(value, (list, tuple)):
        inner = {kind_of(x) for x in value}
        elem = inner.pop() if len(inner) == 1 else "mixed"
        if value and isinstance(value[0], (list, tuple)):
            return f"2d-{elem}"
        return f"{elem}-list"
    return "other"

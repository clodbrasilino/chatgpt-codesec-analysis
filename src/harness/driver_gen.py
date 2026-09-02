"""Generate C drivers that exercise a target function against MBPP test cases.

Strategy (single translation unit):
  - The driver's ``main`` is appended to the problem source; the LLM's own
    ``main`` is renamed via ``-Dmain=__mbpp_disabled_main`` so both coexist.
  - The compiler therefore sees the *real* function definition. Wrong call
    bindings (wrong arg count / incompatible types) fail at compile time
    (cheap) rather than silently producing garbage at runtime.
  - For each test case the driver materializes the Python literal arguments
    as C locals, calls the function, and prints one line::

        case0:<serialized result>

  Serialized results are JSON-compatible: scalars print plainly, string
  arrays print with quoted/escaped elements, numeric arrays print bare, so
  the Python oracle side can ``json.loads`` them back.

  List returns use the standard C idioms, tried in order:
    int/float/str/bool list  -> ``T *fn(..., int *out_len)``
    string list              -> additionally ``char **fn(...)`` (NULL-terminated)

  Candidate bindings are tried most-likely-first; the caller stops at the
  first combo that compiles AND satisfies every oracle result.
"""
from __future__ import annotations

import itertools
from dataclasses import dataclass, field

from .translate import c_2d, c_float, c_int, c_str, kind_of

MAX_COMBOS = 40

# Return-type variants per expected (MBPP) return kind, most-likely first.
# Each entry: (declared type of r{i}, serializer tag, extra call arg template).
# Serializer tags: ll / d / s / b (scalars), ilist / llist / dlist / slist
# (arrays printed with a length), slist_nt (NULL-terminated string array).
RET_VARIANTS: dict[str, list[tuple[str, str, str | None]]] = {
    "int": [("int", "ll", None), ("long", "ll", None), ("long long", "ll", None)],
    "float": [("double", "d", None), ("float", "d", None)],
    "str": [("char *", "s", None), ("const char *", "s", None)],
    "bool": [("int", "b", None), ("_Bool", "b", None)],
    "int-list": [
        ("int *", "ilist", "&r{i}_n"),
        ("long long *", "llist", "&r{i}_n"),
        ("long *", "llist", "&r{i}_n"),
    ],
    "float-list": [("double *", "dlist", "&r{i}_n"), ("float *", "dlist", "&r{i}_n")],
    "str-list": [
        ("char **", "slist", "&r{i}_n"),
        ("char **", "slist_nt", None),
        ("char *", "slist", "&r{i}_n"),  # flat char* + len (rare but seen)
    ],
    "bool-list": [("int *", "ilist", "&r{i}_n")],
}


@dataclass
class Binding:
    """How to materialize one Python argument as C locals and call args.

    ``shape`` is a stable identifier across cases (e.g. ``2di-arr``) used to
    match a combo's arg shapes to each case's regenerated bindings; it is
    independent of per-case literals (and of per-case column counts).
    """

    shape: str
    decls: str
    args: list[str]


@dataclass
class Combo:
    """One (arg bindings x return variant) candidate for the whole case set."""

    ret_type: str
    ret_tag: str
    bindings: list[Binding]
    extra_arg: str | None = None  # e.g. "&r{i}_n" -> formatted per case


def _bindings(kind: str, value, i: int, prefix: str = "a") -> list[Binding]:
    """Candidate bindings for argument position ``i`` of kind ``kind``.

    ``prefix`` disambiguates variables across test cases (``c0_0``,
    ``c1_0``, ...) and defaults to ``a`` for backward compatibility.
    """
    v = f"{prefix}{i}"
    out: list[Binding] = []
    if kind == "int":
        out.append(Binding("int", f"int a{v} = {c_int(value)};", [f"a{v}"]))
    elif kind == "float":
        out.append(Binding("d", f"double a{v} = {c_float(value)};", [f"a{v}"]))
        out.append(Binding("f", f"float a{v} = {c_float(value)};", [f"a{v}"]))
    elif kind == "str":
        out.append(Binding("char-ptr", f"char a{v}[] = {c_str(value)};", [f"a{v}"]))
    elif kind == "bool":
        out.append(Binding("b-int", f"int a{v} = {1 if value else 0};", [f"a{v}"]))
        out.append(Binding("b-bool", f"_Bool a{v} = {1 if value else 0};", [f"a{v}"]))
    elif kind == "int-list":
        n = len(value)
        lit = "{" + ", ".join(str(x) for x in value) + "}"
        out.append(Binding("i-ptr-len", f"int a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}", f"a{v}_n"]))
        out.append(Binding("i-len-ptr", f"int a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}_n", f"a{v}"]))
        out.append(Binding("i-ptr", f"int a{v}[] = {lit};", [f"a{v}"]))
        ll = "{" + ", ".join(f"{x}LL" for x in value) + "}"
        out.append(Binding("ll-ptr-len", f"long long a{v}[] = {ll};\nint a{v}_n = {n};", [f"a{v}", f"a{v}_n"]))
        out.append(Binding("ll-len-ptr", f"long long a{v}[] = {ll};\nint a{v}_n = {n};", [f"a{v}_n", f"a{v}"]))
        out.append(Binding("ll-ptr", f"long long a{v}[] = {ll};", [f"a{v}"]))
    elif kind == "float-list":
        n = len(value)
        lit = "{" + ", ".join(c_float(x) for x in value) + "}"
        out.append(Binding("d-ptr-len", f"double a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}", f"a{v}_n"]))
        out.append(Binding("d-len-ptr", f"double a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}_n", f"a{v}"]))
        out.append(Binding("d-ptr", f"double a{v}[] = {lit};", [f"a{v}"]))
    elif kind == "str-list":
        n = len(value)
        lit = "{" + ", ".join(c_str(x) for x in value) + "}"
        out.append(Binding("ss-ptr-len", f"char *a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}", f"a{v}_n"]))
        out.append(Binding("ss-len-ptr", f"char *a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}_n", f"a{v}"]))
        out.append(Binding("ss-ptr", f"char *a{v}[] = {lit};", [f"a{v}"]))
    elif kind == "bool-list":
        n = len(value)
        lit = "{" + ", ".join("1" if x else "0" for x in value) + "}"
        out.append(Binding("bi-ptr-len", f"int a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}", f"a{v}_n"]))
        out.append(Binding("bi-len-ptr", f"int a{v}[] = {lit};\nint a{v}_n = {n};", [f"a{v}_n", f"a{v}"]))
        out.append(Binding("bi-ptr", f"int a{v}[] = {lit};", [f"a{v}"]))
    elif kind == "2d-int-list":
        out.extend(_bindings_2d("int", value, i, prefix))
    elif kind == "2d-float-list":
        out.extend(_bindings_2d("float", value, i, prefix))
    return out


def _bindings_2d(elem: str, value, i: int, prefix: str = "a") -> list[Binding]:
    """2-D array bindings, tried in order:

    - ``arr``:   ``T a{v}[][C] = {...};``  -> matches ``T a[][C]`` params
    - ``pp``:    row-pointer array         -> matches ``T **`` params
    - ``pp-rc``: row-pointer + rows/cols   -> matches ``T **a, int r, int c``
    """
    v = f"{prefix}{i}"
    rows = len(value)
    cols = len(value[0]) if rows else 0
    if any(len(r) != cols for r in value):
        return []
    if elem == "int":
        lit = c_2d(value, "int")
        arr = (
            Binding("2di-arr", f"int a{v}[][{cols}] = {lit};", [f"a{v}"])
        )
        pp = Binding(
            "2di-pp",
            f"int _m{v}[{rows}][{cols}] = {lit};\n"
            f"int *a{v}[] = {{{', '.join(f'_m{v}[{k}]' for k in range(rows))}}};",
            [f"a{v}"],
        )
        pp_rc = Binding(
            "2di-pp-rc",
            f"int _m{v}[{rows}][{cols}] = {lit};\n"
            f"int *a{v}[] = {{{', '.join(f'_m{v}[{k}]' for k in range(rows))}}};\n"
            f"int a{v}_r = {rows};\nint a{v}_c = {cols};",
            [f"a{v}", f"a{v}_r", f"a{v}_c"],
        )
        return [arr, pp, pp_rc]
    lit = c_2d(value, "float")
    arr = Binding("2df-arr", f"double a{v}[][{cols}] = {lit};", [f"a{v}"])
    pp = Binding(
        "2df-pp",
        f"double _m{v}[{rows}][{cols}] = {lit};\n"
        f"double *a{v}[] = {{{', '.join(f'_m{v}[{k}]' for k in range(rows))}}};",
        [f"a{v}"],
    )
    pp_rc = Binding(
        "2df-pp-rc",
        f"double _m{v}[{rows}][{cols}] = {lit};\n"
        f"double *a{v}[] = {{{', '.join(f'_m{v}[{k}]' for k in range(rows))}}};\n"
        f"int a{v}_r = {rows};\nint a{v}_c = {cols};",
        [f"a{v}", f"a{v}_r", f"a{v}_c"],
    )
    return [arr, pp, pp_rc]


def build_combos(cases: list) -> list[Combo]:
    """Enumerate candidate (return x arg-bindings) combos, best-first.

    ``cases`` is a list of (args, expected) tuples. The first case's arg
    kinds drive the binding candidate set; every combo is instantiated per
    case at driver-build time via :func:`render_driver`.
    """
    if not cases:
        return []
    kinds = [kind_of(a) for a in cases[0][0]]
    per_arg = [_bindings(k, cases[0][0][j], j) for j, k in enumerate(kinds)]
    if any(not bl for bl in per_arg):
        return []  # an argument kind has no binding support
    rets = RET_VARIANTS.get(kind_of(cases[0][1]), [])
    if not rets:
        return []
    combos: list[Combo] = []
    for bindings_tuple in itertools.product(*per_arg):
        for ret_type, ret_tag, extra_arg in rets:
            combos.append(Combo(ret_type, ret_tag, list(bindings_tuple), extra_arg))
            if len(combos) >= MAX_COMBOS:
                return combos
    return combos


_HEADER = """\
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#undef main
/* -------- result serializers -------- */
static void print_ll(long long v) {{ printf("%lld", v); }}
static void print_d(double v) {{ printf("%.17g", v); }}
static void print_s(const char *v) {{ printf("%s", v ? v : "(null)"); }}
static void print_b(int v) {{ printf("%d", v ? 1 : 0); }}
static void print_qstr(const char *s) {{
    printf("\\"");
    if (s) for (const char *p = s; *p; p++) {{
        if (*p == '"' || *p == '\\\\') printf("\\\\%c", *p);
        else if (*p == '\\n') printf("\\\\n");
        else if (*p == '\\t') printf("\\\\t");
        else if (*p == '\\r') printf("\\\\r");
        else printf("%c", *p);
    }}
    printf("\\"");
}}
static void print_ilist(int *v, int n) {{
    if (!v) {{ printf("null"); return; }}
    printf("[");
    for (int k = 0; k < n; k++) {{ if (k) printf(","); print_ll((long long)v[k]); }}
    printf("]");
}}
static void print_llist(long long *v, int n) {{
    if (!v) {{ printf("null"); return; }}
    printf("[");
    for (int k = 0; k < n; k++) {{ if (k) printf(","); print_ll(v[k]); }}
    printf("]");
}}
static void print_dlist(double *v, int n) {{
    if (!v) {{ printf("null"); return; }}
    printf("[");
    for (int k = 0; k < n; k++) {{ if (k) printf(","); print_d(v[k]); }}
    printf("]");
}}
static void print_slist(char **v, int n) {{
    if (!v) {{ printf("null"); return; }}
    printf("[");
    for (int k = 0; k < n; k++) {{ if (k) printf(","); print_qstr(v[k]); }}
    printf("]");
}}
static void print_slist_nt(char **v) {{
    if (!v) {{ printf("null"); return; }}
    printf("[");
    int k = 0;
    for (; v[k]; k++) {{ if (k) printf(","); print_qstr(v[k]); }}
    printf("]");
}}
"""


def _printer(ret_tag: str, var: str, len_var: str | None = None) -> str:
    if ret_tag == "ll":
        return f"print_ll((long long){var});"
    if ret_tag == "d":
        return f"print_d((double){var});"
    if ret_tag == "s":
        return f"print_s({var});"
    if ret_tag == "b":
        return f"print_b((int){var});"
    if ret_tag == "ilist":
        return f"print_ilist({var}, {len_var});"
    if ret_tag == "llist":
        return f"print_llist({var}, {len_var});"
    if ret_tag == "dlist":
        return f"print_dlist({var}, {len_var});"
    if ret_tag == "slist":
        return f"print_slist({var}, {len_var});"
    if ret_tag == "slist_nt":
        return f"print_slist_nt({var});"
    raise ValueError(f"unknown ret tag {ret_tag}")


def render_driver(combo: Combo, cases: list, fn_name: str) -> str:
    """Render the full driver source for ``combo`` over all ``cases``.

    ``cases`` = list of (args:list, expected). Raises ValueError when a case
    cannot be materialized with this combo's binding shapes.
    """
    shapes = combo.bindings
    blocks: list[str] = []
    for ci, (args, expected) in enumerate(cases):
        prefix = f"c{ci}_"
        decls_all: list[str] = []
        call_args: list[str] = []
        for j, argval in enumerate(args):
            cands = _bindings(kind_of(argval), argval, j, prefix)
            match = next((b for b in cands if b.shape == shapes[j].shape), None)
            if match is None:
                raise ValueError(f"case {ci}: no binding for kind {kind_of(argval)}")
            decls_all.append(match.decls)
            call_args.extend(match.args)

        ret_type = combo.ret_type
        var = f"r{ci}"
        len_var = f"r{ci}_n"
        needs_len = combo.ret_tag in ("ilist", "llist", "dlist", "slist")
        if needs_len:
            decls_all.append(f"int {len_var} = -1;")
            call_args.append(combo.extra_arg.format(i=ci))
        printer = _printer(combo.ret_tag, var, len_var if needs_len else None)

        blocks.append(
            "/* ---- test case %d ---- */\n"
            "%s\n"
            "%s %s = %s(%s);\n"
            'printf("case%d:");\n'
            "%s\n"
            'printf("\\n");'
            % (ci, "\n".join(decls_all), ret_type, var, fn_name, ", ".join(call_args), ci, printer)
        )
    return _HEADER + "\nint main(void) {\n" + "\n".join(blocks) + "\nreturn 0;\n}\n"

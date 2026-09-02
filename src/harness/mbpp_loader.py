"""Load MBPP records and build per-problem harness specs.

The oracle for expected outputs is the *reference Python*: we execute the
MBPP reference implementation against its own test asserts and serialize the
results canonically. No Python->C literal translation is needed for the
oracle; the C side just has to produce the same serialization.
"""
from __future__ import annotations

import ast
import json
from dataclasses import asdict, dataclass, field
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
MBPP_PATH = REPO_ROOT / "mbpp" / "mbpp.jsonl"
SPEC_DIR = REPO_ROOT / "harnesses"

# Kinds the C driver generator can materialize (see harness/driver_gen.py).
# Args: scalars + 1-D/2-D homogeneous lists. Returns: scalars + 1-D lists
# (2-D / mixed / dict results have no portable C signature).
ARG_SUPPORTED = {"int", "float", "str", "bool",
                 "int-list", "float-list", "str-list", "bool-list",
                 "2d-int-list", "2d-float-list"}
RET_SUPPORTED = {"int", "float", "str", "bool",
                 "int-list", "float-list", "str-list", "bool-list"}


def _supported_case(tc: "TestCase") -> bool:
    """A case is C-translatable iff every arg and the expected are supported."""
    from .translate import kind_of
    if kind_of(tc.expected) not in RET_SUPPORTED:
        return False
    return all(kind_of(a) in ARG_SUPPORTED for a in tc.args)


@dataclass
class TestCase:
    fn_name: str
    args: list  # python literals
    expected: object  # serialized by reference execution
    assert_src: str


@dataclass
class HarnessSpec:
    task_id: int
    text: str
    fn_candidates: list[str]
    test_cases: list[TestCase]
    arg_kinds: list[str] = field(default_factory=list)
    return_kind: str = "unknown"
    mode_hint: str = "link"  # link | cli | none
    test_setup_code: str = ""
    parseable: bool = True
    parse_note: str = ""

    def to_json(self) -> str:
        return json.dumps(asdict(self), indent=2, default=str)

    def save(self) -> Path:
        p = SPEC_DIR / str(self.task_id) / "spec.json"
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(self.to_json())
        return p

    @classmethod
    def load(cls, task_id: int) -> "HarnessSpec":
        return cls.from_json((SPEC_DIR / str(task_id) / "spec.json").read_text())

    @classmethod
    def from_json(cls, raw: str) -> "HarnessSpec":
        d = json.loads(raw)
        d["test_cases"] = [TestCase(**tc) for tc in d["test_cases"]]
        return cls(**d)


def load_mbpp() -> list[dict]:
    rows = []
    with open(MBPP_PATH) as f:
        for line in f:
            if line.strip():
                rows.append(json.loads(line))
    return rows


def _exec_reference(record: dict) -> dict[str, object] | None:
    """Run the MBPP reference + asserts; return {fn: expected per assert}."""
    ns: dict = {}
    try:
        exec(record["code"], ns)
        if record.get("test_setup_code"):
            exec(record["test_setup_code"], ns)
        fn_name = None
        results = []
        for assert_src in record["test_list"]:
            tree = ast.parse(assert_src)  # Assert is a statement, not an expr
            stmt = tree.body[0]
            if not isinstance(stmt, ast.Assert):
                return None
            node = stmt.test
            if not isinstance(node, ast.Compare) or not isinstance(node.left, ast.Call):
                return None
            call = node.left
            if not isinstance(call.func, ast.Name):
                return None
            fn_name = call.func.id
            if fn_name not in ns:
                return None
            value = eval(ast.unparse(call), ns)  # noqa: S307 -- oracle reference execution
            expected = eval(ast.unparse(node.comparators[0]), ns)  # noqa: S307
            args = [eval(ast.unparse(a), ns) for a in call.args]  # noqa: S307 -- literals/constants
            results.append((fn_name, args, expected, assert_src))
        return {"fn_name": fn_name, "results": results}
    except Exception:  # noqa: BLE001
        return None


def build_spec(record: dict, force: bool = False) -> HarnessSpec | None:
    """Build a HarnessSpec for one MBPP record (cached in harnesses/{id}/)."""
    task_id = int(record["task_id"])
    spec_path = SPEC_DIR / str(task_id) / "spec.json"
    if spec_path.exists() and not force:
        return HarnessSpec.load(task_id)

    oracle = _exec_reference(record)
    if oracle is None:
        spec = HarnessSpec(
            task_id=task_id, text=record["text"], fn_candidates=[],
            test_cases=[], parseable=False, mode_hint="none",
            parse_note="reference execution or assert parsing failed",
            test_setup_code=record.get("test_setup_code", ""),
        )
        spec.save()
        return spec

    fn_name = oracle["fn_name"]
    candidates = _name_candidates(fn_name)
    test_cases = []
    arg_kinds: set[str] = set()
    for fn, args, expected, assert_src in oracle["results"]:
        tc = TestCase(fn_name=fn, args=list(args), expected=expected, assert_src=assert_src)
        if not _supported_case(tc):
            continue  # e.g. dict/set results are untranslatable to C
        for a in args:
            arg_kinds.add(_kind_of(a))
        test_cases.append(tc)

    if not test_cases:
        spec = HarnessSpec(
            task_id=task_id, text=record["text"], fn_candidates=candidates,
            test_cases=[], parseable=False, mode_hint="none",
            parse_note="no C-translatable test case (list/2d/mixed/dict kinds only)",
            test_setup_code=record.get("test_setup_code", ""),
        )
        spec.save()
        return spec

    link_kinds = ARG_SUPPORTED
    spec = HarnessSpec(
        task_id=task_id,
        text=record["text"],
        fn_candidates=candidates,
        test_cases=test_cases,
        arg_kinds=sorted(arg_kinds),
        return_kind=_kind_of(test_cases[0].expected) if test_cases else "unknown",
        mode_hint="link" if arg_kinds.issubset(link_kinds) else "cli",
        test_setup_code=record.get("test_setup_code", ""),
    )
    spec.save()
    return spec


def _name_candidates(fn_name: str) -> list[str]:
    """MBPP snake_case -> plausible C names."""
    parts = fn_name.split("_")
    return [
        fn_name,
        "".join(p.capitalize() for p in parts),  # CamelCase
        parts[0] + "".join(p.capitalize() for p in parts[1:]),  # camelCase
        "".join(parts),
    ]


def _kind_of(value) -> str:
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int"
    if isinstance(value, float):
        return "float"
    if isinstance(value, str):
        return "str"
    if isinstance(value, (list, tuple)):
        inner = {_kind_of(x) for x in value}
        if len(inner) == 1:
            elem = inner.pop()
        else:
            elem = "mixed"
        if value and isinstance(value[0], (list, tuple)):
            return f"2d-{elem}"
        return f"{elem}-list"
    return "other"


def build_all(force: bool = False) -> dict[int, HarnessSpec]:
    specs = {}
    for record in load_mbpp():
        s = build_spec(record, force=force)
        if s:
            specs[s.task_id] = s
    return specs


if __name__ == "__main__":
    specs = build_all()
    parseable = sum(1 for s in specs.values() if s.parseable)
    by_mode: dict[str, int] = {}
    for s in specs.values():
        by_mode[s.mode_hint] = by_mode.get(s.mode_hint, 0) + 1
    print(f"specs built: {len(specs)}; parseable: {parseable}; modes: {by_mode}")
    print(f"arg kinds seen: {sorted({k for s in specs.values() for k in s.arg_kinds})}")

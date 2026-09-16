"""Read-only audit of experiment artifacts, independent of experiment execution.

Run ``python -m src.analysis.health_check --all --output-dir /path/to/health``.
Inputs are never repaired or regenerated. Only the selected output directory is
written. Missing evidence is distinct from a successful check. CSVs are UTF-8;
JSON columns preserve structured evidence without executable spreadsheet cells.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import json
import os
import re
import statistics
import tempfile
import time
from collections import Counter, defaultdict
from datetime import datetime, timezone
from pathlib import Path

from .metrics import _PROBLEM_RE, _list_sources
from ..pipeline.comment_inject import (
    CHANNEL_SUFFIXES, STATIC_SUFFIXES, DYNAMIC_SUFFIXES,
    add_comments_to_weak_source, extract_standard_messages,
)

REPO_ROOT = Path(__file__).resolve().parents[2]
VERSION = "1.2"
TOOLS = [s[1:-4] for s in STATIC_SUFFIXES + DYNAMIC_SUFFIXES]
CELL_RE = re.compile(r"^feedback-(static\+dynamic|static|dynamic|none)-r\d+-t[^/]+-p[^/]+$")
ARTIFACT_RE = re.compile(r"^(problem-\d+(?:-s\d+)?)(?:\.c|\.txt|\.(?:gcc|clang|cppcheck|flawfinder|test|asan|fuzz)\.txt)$")
FF_HIT_RE = re.compile(r"^.*?\.c:(\d+):\s*\[(\d+)\]\s*\(([^)]+)\)\s*([^:]+):", re.M)
BLOCK_RE = re.compile(r"(?m)^[ \t]*/\* Possible weaknesses found:\n(?:[ \t]* \* [^\n]*\n)*[ \t]* \*/(?:\n|$)")
ANOMALY_FIELDS = ["model", "cell", "round", "basename", "check", "severity", "relative_path", "evidence", "action"]


def dumps(value) -> str:
    return json.dumps(value, ensure_ascii=False, sort_keys=True)


def normalize_annotations(text: str) -> str:
    """Normalize messages only; preserve all source bytes and block anchors."""
    def replace(match):
        lines = match.group().splitlines(keepends=True)
        messages = sorted(line.rstrip() + "\n" for line in lines[1:-1])
        return lines[0] + "".join(messages) + lines[-1]
    return BLOCK_RE.sub(replace, text)


def annotation_parts(text: str) -> tuple[str, dict[int, list[str]]]:
    """Return source without generated blocks and messages at source line anchors."""
    source, blocks, end, anchor = [], defaultdict(list), 0, 1
    for match in BLOCK_RE.finditer(text):
        plain = text[end:match.start()]
        source.append(plain)
        anchor += plain.count("\n")
        for line in match.group().splitlines()[1:-1]:
            blocks[anchor].append(line.split(" * ", 1)[1].rstrip())
        end = match.end()
    source.append(text[end:])
    return "".join(source), dict(blocks)


def classify_test(text: str | None) -> str:
    if text is None:
        return "absent"
    if not text.strip():
        return "empty"
    if "no harness spec" in text:
        return "no_spec"
    if "no testable interface" in text:
        return "no_interface"
    if "could not compile under sanitizers" in text:
        return "compile_error"
    if re.search(r"test case \d+ failed", text):
        return "failed"
    if re.search(r":0:0:\s*info:\s*all [1-9]\d* test cases passed", text):
        return "passed"
    if "CLI mode exercised" in text:
        return "cli_exercised"
    return "unknown"


def atomic_text(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    fd, tmp = tempfile.mkstemp(prefix="." + path.name, dir=path.parent)
    try:
        with os.fdopen(fd, "w", encoding="utf-8", newline="") as stream:
            stream.write(text)
            stream.flush()
            os.fsync(stream.fileno())
        os.replace(tmp, path)
    finally:
        if os.path.exists(tmp):
            os.unlink(tmp)


def atomic_csv(path: Path, rows: list[dict], fields: list[str] | None = None) -> None:
    import io
    fields = fields or list(dict.fromkeys(k for row in rows for k in row))
    stream = io.StringIO(newline="")
    writer = csv.DictWriter(stream, fieldnames=fields, extrasaction="raise")
    writer.writeheader()
    for row in rows:
        writer.writerow({k: dumps(v) if isinstance(v, (dict, list, tuple)) else v for k, v in row.items()})
    atomic_text(path, stream.getvalue())


def input_inventory(repo: Path) -> dict[str, tuple[int, int]]:
    """Detect concurrent edits, including additions/removals, without reading bodies."""
    result = {}
    roots = [repo / "collected_code_6", repo / "results", repo / "src" / "pipeline", repo / "src" / "dyn", repo / "config", repo / "docs"]
    for root in roots:
        for folder, dirs, names in os.walk(root):
            dirs[:] = sorted(d for d in dirs if d != "__pycache__")
            for name in sorted(names):
                if name == ".DS_Store":
                    continue
                path = os.path.join(folder, name)
                stat = os.stat(path)
                result[os.path.relpath(path, repo)] = (stat.st_size, stat.st_mtime_ns)
    return result


def validate_output(repo: Path, output: Path) -> None:
    """Do not permit output under any audited tree, or over the repository root."""
    repo, output = repo.resolve(), output.resolve()
    for protected in [repo / n for n in ("results", "src", "config", "docs", ".git")] + list(repo.glob("collected_code*")):
        protected = protected.resolve()
        if output == protected or protected in output.parents or output in protected.parents:
            raise ValueError(f"Output overlaps protected input: {protected}")


class CellAudit:
    def __init__(self, repo: Path, root: Path):
        self.repo, self.root = repo, root
        self.model, self.slug = root.parent.name, root.name
        self.anomalies: list[dict] = []
        self.details: list[dict] = []
        self.counts = Counter()
        self.sources: dict[int, dict[str, dict]] = {}
        self.queues: dict[int, set[str]] = {}
        self.annotation_counts = Counter()
        self.manifest = None
        self.tasks = None
        self.samples = self.max_rounds = None
        self.measure = None
        match = CELL_RE.match(self.slug)
        self.feedback = match[1] if match else None
        self.manifest_path = repo / "results" / self.model / (self.slug + ".manifest.json")
        if self.manifest_path.exists():
            raw = self.read(self.manifest_path)
            try:
                data = json.loads(raw)
                c = data["cell"]
                if not isinstance(data["outcomes"], dict):
                    raise ValueError("outcomes must be an object")
                if c["feedback"] not in CHANNEL_SUFFIXES or c["measure"] not in CHANNEL_SUFFIXES:
                    raise ValueError("unknown channel")
                if not isinstance(c["tasks"], list) or any(type(t) is not int or t < 1 for t in c["tasks"]):
                    raise ValueError("tasks must be positive integer IDs")
                if type(c["samples"]) is not int or c["samples"] < 1 or type(c["max_rounds"]) is not int or c["max_rounds"] < 0:
                    raise ValueError("invalid samples/max_rounds")
                if any(not isinstance(v, dict) or v.get("outcome") not in {"clean_at_start", "clean", "not_cleaned", "heal_failed"} or type(v.get("rounds_to_clean")) is not int for v in data["outcomes"].values()):
                    raise ValueError("malformed outcome")
                self.manifest = data
                self.tasks, self.samples, self.max_rounds = set(c["tasks"]), c["samples"], c["max_rounds"]
                self.measure = c["measure"]
                if self.feedback != c["feedback"]:
                    self.issue("config_conflict", "error", 0, "", self.manifest_path, {"slug_feedback": self.feedback, "manifest_feedback": c["feedback"]}, "Confirmar a configuração da execução; roteamento fica não verificável.")
                    self.feedback = None
            except (ValueError, TypeError, KeyError) as exc:
                self.issue("malformed_manifest", "error", 0, "", self.manifest_path, str(exc), "Recuperar manifest válido da execução.")
        else:
            self.issue("missing_manifest", "unknown", 0, "", self.manifest_path, "Completude, medição e resultados finais não verificáveis.", "Recuperar o manifest dessa configuração.")
        if not self.feedback:
            self.issue("unknown_feedback", "unknown", 0, "", root, "Canal não determinado com segurança.", "Confirmar configuração.")

    def issue(self, check, severity, round_no, basename, path, evidence, action):
        self.counts[check] += 1
        self.anomalies.append(dict(model=self.model, cell=self.slug, round=round_no, basename=basename, check=check, severity=severity, relative_path=path.absolute().relative_to(self.repo.absolute()).as_posix(), evidence=dumps(evidence), action=action))

    def read(self, path: Path) -> str | None:
        try:
            # Universal newlines match the original pipeline's text reader.
            return path.read_text(encoding="utf-8")
        except (OSError, UnicodeError) as exc:
            self.issue("unreadable_file", "error", "", path.stem, path, str(exc), "Recuperar o arquivo e repetir a conferência.")
            return None

    def scan_source(self, directory: Path, base: str, round_no: int, observed_tools: set[str]) -> dict:
        path = directory / (base + ".c")
        text = self.read(path) if path.exists() else None
        rec = {"path": path, "text": text, "flags": {}, "errors": {}, "provenance": defaultdict(set), "reports": {}, "test_state": "absent", "ff_hits": 0, "ff_levels": Counter(), "readable": text is not None}
        row = dict(model=self.model, cell=self.slug, round=round_no, basename=base, source_relative_path=path.absolute().relative_to(self.repo.absolute()).as_posix(), c_exists=path.exists(), c_bytes=path.stat().st_size if path.exists() else None, raw_txt_exists=(directory / (base + ".txt")).exists(), feedback=self.feedback, measure=self.measure)
        if text is None or not text:
            self.issue("missing_source" if not path.exists() else "empty_or_unreadable_source", "error", round_no, base, path, "Código ausente, vazio ou ilegível.", "Conferir se o código foi gerado e se todos os arquivos foram copiados.")
        raw_path = directory / (base + ".txt")
        if path.exists() and not raw_path.exists():
            self.issue("missing_raw", "warning", round_no, base, raw_path, "Resposta bruta ausente.", "Recuperar resposta bruta para manter rastreabilidade.")
        elif raw_path.exists() and raw_path.stat().st_size == 0:
            self.issue("empty_raw", "warning", round_no, base, raw_path, "Resposta bruta vazia.", "Conferir extração e cópia dos dados.")
        required = set()
        if self.measure:
            required = {s[1:-4] for s in CHANNEL_SUFFIXES[self.measure] if s in STATIC_SUFFIXES or s == ".test.txt"}
        feedback_tools = {s[1:-4] for s in CHANNEL_SUFFIXES.get(self.feedback, [])}
        for tool in TOOLS:
            report = directory / (base + f".{tool}.txt")
            present = report.exists()
            body = self.read(report) if present else None
            rec["reports"][tool] = present
            row["rpt_" + tool] = present
            if not present and path.exists() and (tool in required or (not self.measure and tool in observed_tools and tool not in {"asan", "fuzz"})):
                check = "missing_report" if self.measure else "report_coverage_gap"
                self.issue(check, "warning", round_no, base, report, {"measure": self.measure, "tool": tool, "expected_from": "manifest" if self.measure else "observed_coverage_only"}, "Conferir se a ferramenta rodou e recuperar o relatório.")
            if present and body is None:
                rec["readable"] = False
            parsed = extract_standard_messages(body or "")
            positive = [m for m in parsed if m["line"] > 0]
            rec["flags"][tool] = bool(positive)
            row["n_find_" + tool] = len(positive)
            if tool in feedback_tools:
                for msg in positive:
                    line, message = msg["line"], msg["message"]
                    rec["errors"].setdefault(line, []).append(message)
                    rec["provenance"][(line, message.rstrip())].add(tool)
                    if not message.strip():
                        self.issue("empty_finding_message", "warning", round_no, base, report, {"line": line, "tool": tool}, "Conferir formato e parser do relatório.")
                    if text is not None and line > len(text.splitlines()):
                        self.issue("finding_line_out_of_range", "warning", round_no, base, report, {"line": line, "source_lines": len(text.splitlines())}, "Conferir de qual arquivo veio o alerta. Essa linha não cabe no código.")
            if body:
                malformed = []
                for line in body.splitlines():
                    tokens = line.split(":")
                    if tool in feedback_tools and len(tokens) >= 5:
                        try:
                            location = int(tokens[1])
                        except ValueError:
                            location = 0
                        if location > 0 and Path(tokens[0]).name != base + ".c":
                            self.issue("foreign_diagnostic_location", "warning", round_no, base, report, {"reported_file": tokens[0], "reported_line": location, "severity": tokens[3].strip(), "message": ":".join(tokens[4:]), "injected_into": str(path)}, "Conferir o arquivo citado: o parser mistura alertas de bibliotecas e do código gerado.")
                    diagnostic = re.match(r"^.*?\.c:([^:]+):([^:]+):\s*(?:error|fatal error|warning|info|note):", line)
                    if diagnostic and (not diagnostic[1].isdigit() or not diagnostic[2].isdigit()):
                        malformed.append(line[:300])
                if malformed:
                    self.issue("malformed_report", "warning", round_no, base, report, malformed[:5], "Recuperar relatório válido; não interpretar como limpo.")
                if tool != "test":
                    failed = [line for line in body.splitlines() if re.search(r":0:0:\s*(?:fatal )?error:|^(?:gcc|clang|cppcheck): (?:fatal )?error:|timed out", line)]
                    if failed:
                        self.issue("tool_execution_error", "warning", round_no, base, report, failed[:3], "Conferir o erro da ferramenta. Sem alerta não significa que ela rodou bem.")
            if tool == "test":
                state = classify_test(body)
                rec["test_state"] = state
                if present and state not in {"passed", "failed"}:
                    self.issue("test_without_verdict", "warning", round_no, base, report, {"state": state, "excerpt": (body or "")[:350]}, "Não contar como aprovado. Informar quantos arquivos tiveram teste com veredito.")
                if state == "failed" and not positive:
                    self.issue("test_failure_unconsumed", "error", round_no, base, report, (body or "")[:350], "Conferir linha de ancoragem: falha registrada mas não encaminhada pelo parser.")
            if tool == "flawfinder" and body:
                hits = list(FF_HIT_RE.finditer(body))
                rec["ff_hits"] = len(hits)
                rec["ff_levels"] = Counter(h[2] for h in hits)
                declared = re.search(r"^Hits = (\d+)", body, re.M)
                if declared and int(declared[1]) != len(hits):
                    self.issue("malformed_flawfinder", "warning", round_no, base, report, {"declared_hits": int(declared[1]), "parsed_headers": len(hits)}, "Conferir relatório incompleto ou formato não suportado.")
                consumed = {(m["line"], m["message"].strip()) for m in positive if m["message"].strip()}
                if hits and not consumed:
                    self.issue("flawfinder_unconsumed", "warning", round_no, base, report, {"lexical_hits": len(hits), "levels": dict(rec["ff_levels"]), "generic_findings": len(positive), "confirmed_defects": False}, "Revisar o parser e medir o impacto antes de repetir o experimento.")
        row.update(test_state=rec["test_state"], flawfinder_lexical_hits=rec["ff_hits"], flawfinder_levels=dict(rec["ff_levels"]), flagged_feedback=bool(rec["errors"]))
        self.details.append(row)
        return rec

    def run(self) -> dict:
        round_dirs = {int(p.name[5:]): p for p in self.root.glob("heal_*") if p.is_dir() and p.name[5:].isdigit()}
        round_dirs.setdefault(0, self.root / "heal_0")
        expected = None
        if self.tasks is not None:
            expected = {f"problem-{task}" + (f"-s{s}" if s > 1 else "") for task in self.tasks for s in range(1, self.samples + 1)}
        observed_tools = set()
        if self.measure is None:
            for n, folder in round_dirs.items():
                directory = folder if n == 0 else folder / "healed"
                if directory.is_dir():
                    for path in directory.iterdir():
                        for tool in TOOLS:
                            if path.name.endswith(f".{tool}.txt"):
                                observed_tools.add(tool)
        for n, folder in sorted(round_dirs.items()):
            if n:
                self.queues[n] = set(_list_sources(folder / "to_be_healed"))
            directory = folder if n == 0 else folder / "healed"
            if n and not directory.is_dir():
                continue
            bases = {m[1] for p in directory.iterdir() if p.is_file() and (m := ARTIFACT_RE.match(p.name))} if directory.is_dir() else set()
            if n == 0 and expected is not None:
                actual = set(_list_sources(directory))
                for base in sorted(actual - expected):
                    self.issue("unexpected_generation", "warning", 0, base, directory / (base + ".c"), "Arquivo fora das tarefas/amostras do manifest atual.", "Identificar os arquivos de validação que ficaram na pasta. Preservar os originais.")
                bases |= expected
            self.sources[n] = {base: self.scan_source(directory, base, n, observed_tools) for base in sorted(bases)}
        if expected is not None:
            present = {b for b, r in self.sources[0].items() if r["path"].exists()}
            generation_missing = len(expected - present)
            generation_extra = len(present - expected)
        else:
            generation_missing = generation_extra = None
        transitions = set(self.queues) | {n + 1 for n in self.sources if self.max_rounds is None or n <= self.max_rounds}
        for n in sorted(transitions):
            self.check_transition(n)
        self.check_outcomes()
        self.check_ledger()
        initial = {b: r for b, r in self.sources.get(0, {}).items() if r["path"].exists()}
        hist = Counter(int(_PROBLEM_RE.match(b)[3] or 1) for b in initial)
        all_records = [r for records in self.sources.values() for r in records.values() if r["path"].exists()]
        test_counts = Counter(r["test_state"] for r in all_records)
        initial_tests = Counter(r["test_state"] for r in initial.values())
        ff_only = sum(bool(r["ff_hits"]) and not any(r["flags"].values()) for r in initial.values())
        summary = dict(model=self.model, cell=self.slug, feedback=self.feedback, measure=self.measure or "unknown", manifest_present=self.manifest is not None, generation_completeness="known" if expected is not None else "unknown", n_expected=len(expected) if expected is not None else None, n_generated=len(initial), generation_missing=generation_missing, generation_extra=generation_extra, sample_histogram=dict(hist), source_versions=len(all_records), annotations_checked=self.annotation_counts["checked"], annotations_match=self.annotation_counts["match"], annotations_mismatch=self.annotation_counts["mismatch"], annotations_unverified=self.annotation_counts["unverified"], source_code_changed=self.counts["source_code_changed"], routing_missing=self.counts["routing_missing"], routing_extra=self.counts["routing_extra"], routing_unverified=self.counts["routing_unverified"], missing_reports=self.counts["missing_report"], coverage_gaps=self.counts["report_coverage_gap"], missing_raw=self.counts["missing_raw"], flawfinder_reports_with_hits=sum(bool(r["ff_hits"]) for r in all_records), initial_flawfinder_only_files=ff_only, test_states_all_rounds=dict(test_counts), test_states_initial=dict(initial_tests), outcome_mismatches=self.counts["outcome_mismatch"], issues=dict(self.counts))
        summary.update(cell_relative_path=self.root.absolute().relative_to(self.repo.absolute()).as_posix(), manifest_relative_path=self.manifest_path.absolute().relative_to(self.repo.absolute()).as_posix())
        self.summary = summary
        self.metrics, self.metric_reasons = self.recompute_metrics(initial)
        return summary

    def check_transition(self, n: int) -> None:
        origin = self.sources.get(n - 1, {})
        target = self.root / f"heal_{n}" / "to_be_healed"
        actual = self.queues.get(n, set())
        if not self.feedback:
            self.annotation_counts["unverified"] += len(actual)
            return
        expected = {b for b, r in origin.items() if r["path"].exists() and r["errors"] and (self.tasks is None or int(_PROBLEM_RE.match(b)[1]) in self.tasks)}
        if n == 1 and self.max_rounds == 0:
            expected = set()
        for base in sorted(expected - actual):
            check = "routing_missing" if self.manifest is not None else "routing_unverified"
            self.issue(check, "warning" if check == "routing_missing" else "unknown", n, base, target / (base + ".c"), {"origin": str(origin[base]["path"]), "feedback": self.feedback, "note": "Diferença do snapshot; pode haver execução incompleta."}, "Conferir continuidade da rodada e versão dos relatórios.")
        for base in sorted(actual - expected):
            self.issue("routing_extra", "warning", n, base, target / (base + ".c"), {"origin_exists": base in origin, "feedback": self.feedback, "note": "Relatórios dinâmicos podem ter sido sobrescritos após a anotação."}, "Conferir o histórico antes de apontar a causa.")
        for base in sorted(actual):
            path = target / (base + ".c")
            rec = origin.get(base)
            actual_text = self.read(path)
            if actual_text == "":
                self.issue("empty_annotation", "error", n, base, path, "Arquivo de cura vazio.", "Recuperar entrada anotada e verificar a origem.")
            if not rec or rec["text"] is None or actual_text is None or not rec["readable"]:
                self.annotation_counts["unverified"] += 1
                self.issue("annotation_unverified", "unknown", n, base, path, "Fonte ou relatório ilegível/ausente.", "Recuperar evidência de origem.")
                continue
            expected_text = add_comments_to_weak_source(rec["text"], rec["errors"])
            self.annotation_counts["checked"] += 1
            if normalize_annotations(expected_text) == normalize_annotations(actual_text):
                self.annotation_counts["match"] += 1
            else:
                self.annotation_counts["mismatch"] += 1
                expected_code, expected_blocks = annotation_parts(expected_text)
                actual_code, actual_blocks = annotation_parts(actual_text)
                changed = expected_code != actual_code
                channels = set()
                missing, extra = {}, {}
                for line in set(expected_blocks) | set(actual_blocks):
                    e, a = Counter(expected_blocks.get(line, [])), Counter(actual_blocks.get(line, []))
                    if e - a:
                        missing[line] = list((e - a).elements())
                        for message in missing[line]:
                            channels |= rec["provenance"].get((line, message), set())
                    if a - e:
                        extra[line] = list((a - e).elements())
                evidence = {"source_changed": changed, "missing_messages": missing, "extra_messages": extra, "diff_channels": sorted(channels), "origin": str(rec["path"]), "cause": "not_established"}
                self.issue("annotation_mismatch", "error" if changed else "warning", n, base, path, evidence, "Comparar código, relatório e comentário. Conferir se houve retomada.")
                if changed:
                    self.issue("source_code_changed", "error", n, base, path, {"origin": str(rec["path"])}, "Conferir truncamento ou alteração de código na entrada de cura.")
        # The final extra queue is a classification artifact, not another heal.
        if self.max_rounds is not None and n > self.max_rounds:
            return
        healed = self.sources.get(n, {})
        for base in sorted(actual):
            if base not in healed or not healed[base]["path"].exists():
                outcome = (self.manifest or {}).get("outcomes", {}).get(base, {})
                known_failure = outcome.get("outcome") == "heal_failed" and outcome.get("rounds_to_clean") == n
                self.issue("recorded_heal_failure" if known_failure else "heal_result_unavailable", "info" if known_failure else "unknown", n, base, self.root / f"heal_{n}" / "healed" / (base + ".c"), {"manifest_outcome": outcome, "execution_complete": self.manifest is not None}, "Conferir a falha e se a rodada terminou.")
        for base in sorted(set(healed) - actual):
            self.issue("healed_without_input", "warning", n, base, healed[base]["path"], "Resultado sem entrada na fila da mesma rodada.", "Conferir resíduos de outra execução ou sincronização incompleta.")

    def check_outcomes(self) -> None:
        if self.manifest is None:
            return
        original = {b for b, r in self.sources.get(0, {}).items() if r["path"].exists()}
        outcomes = self.manifest["outcomes"]
        for base in sorted(original ^ set(outcomes)):
            self.issue("outcome_coverage_mismatch", "warning", 0, base, self.manifest_path, {"source_present": base in original, "outcome_present": base in outcomes}, "Conferir manifest e dados da mesma execução.")
        derived, ever = {}, set()
        for n in range(1, self.max_rounds + 1):
            active = self.queues.get(n, set())
            if not active:
                break
            ever |= active
            next_queue = self.queues.get(n + 1, set())
            for base in active - next_queue:
                record = self.sources.get(n, {}).get(base)
                kind = "clean" if record and record["path"].exists() else "heal_failed"
                derived[base] = {"outcome": kind, "rounds_to_clean": n}
        for base in original:
            derived.setdefault(base, {"outcome": "not_cleaned" if base in ever else "clean_at_start", "rounds_to_clean": self.max_rounds if base in ever else 0})
        for base in sorted(set(derived) & set(outcomes)):
            if derived[base] != outcomes[base]:
                self.issue("outcome_mismatch", "warning", outcomes[base].get("rounds_to_clean", ""), base, self.manifest_path, {"recorded": outcomes[base], "reconstructed_from_artifacts": derived[base], "note": "Reprodução da contabilidade; não certifica ausência de defeitos."}, "Conferir manifest desatualizado ou artefatos incompletos.")

    def check_ledger(self) -> None:
        path = self.manifest_path.with_name(self.slug + ".usage.jsonl")
        self.ledger_counts = Counter()
        if not path.exists():
            return
        body = self.read(path)
        if body is None:
            return
        for line_no, line in enumerate(body.splitlines(), 1):
            if not line.strip():
                continue
            try:
                rec = json.loads(line)
                self.ledger_counts[str(rec["kind"]) + ("_ok" if rec["ok"] else "_failed_attempts")] += 1
            except (ValueError, TypeError, KeyError):
                self.issue("malformed_ledger", "warning", "", "", path, {"line": line_no}, "Recuperar registro de execução; tentativas não equivalem a arquivos faltantes.")

    def recompute_metrics(self, initial: dict) -> tuple[dict, dict]:
        """Reproduce existing definitions from cached reader results, then qualify them.

        No claim of independent validation is made for the legacy definitions.
        Semantic test/flawfinder counts are exported separately in summary.csv.
        """
        n = len(initial)
        by_tool = {t: {b for b, r in initial.items() if r["flags"].get(t)} for t in TOOLS}
        static = set().union(*(by_tool[t] for t in ("gcc", "clang", "cppcheck", "flawfinder")))
        all_flags = set().union(*by_tool.values())
        m = {"n_generated": n}
        reasons = {"n_compilable": "Faltam arquivos .o. Não dá para conferir a compilação nesta cópia.", "compile_rate": "Faltam arquivos .o. Não dá para conferir a compilação nesta cópia."}
        objects = sum((self.root / "heal_0" / (b + ".o")).exists() for b in initial)
        # With a clone, missing objects may mean either failed compilation or
        # missing build artifacts. Only all objects present proves a complete gate.
        m.update(n_compilable=n if n and objects == n else None, compile_rate=1.0 if n and objects == n else None)
        if n and objects == n:
            reasons.clear()
        for tool, bases in by_tool.items():
            m["flagged_" + tool] = len(bases)
        absent = sum(not r["reports"]["test"] for r in initial.values())
        failed = len(by_tool["test"])
        passed = n - absent - failed
        m.update(oracle_absent=absent, oracle_passed=passed, oracle_failed=failed, oracle_pass_rate=round(passed / (n - absent), 4) if n != absent else None, initial_flagged=len(all_flags), initial_defect_rate=round(len(all_flags) / n, 4) if n else None, initial_defect_rate_static_only=round(len(static) / n, 4) if n else None)
        for name in ("flagged_flawfinder", "initial_flagged", "initial_defect_rate", "initial_defect_rate_static_only"):
            reasons[name] = "O parser atual pode ignorar alertas do Flawfinder. A contagem não confirma defeitos reais."
        for name in ("oracle_passed", "oracle_pass_rate"):
            reasons[name] = "A regra antiga pode contar testes sem veredito como aprovados. Ver test_states_initial."
        repair_names = ["clean_at_start", "cleaned", "not_cleaned", "heal_failed", "max_rounds", "mean_rounds_to_clean", "median_rounds_to_clean", "final_clean_rate"]
        m.update({name: None for name in repair_names})
        if self.manifest is not None:
            counts = Counter(v["outcome"] for v in self.manifest["outcomes"].values())
            rounds = [v["rounds_to_clean"] for v in self.manifest["outcomes"].values() if v["outcome"] == "clean"]
            total = counts["clean_at_start"] + counts["clean"] + counts["not_cleaned"]
            m.update(clean_at_start=counts["clean_at_start"], cleaned=counts["clean"], not_cleaned=counts["not_cleaned"], heal_failed=counts["heal_failed"], max_rounds=self.max_rounds, mean_rounds_to_clean=round(statistics.mean(rounds), 3) if rounds else None, median_rounds_to_clean=round(statistics.median(rounds), 3) if rounds else None, final_clean_rate=round((counts["clean_at_start"] + counts["clean"]) / total, 4) if total else None)
        else:
            reasons.update({name: "Manifest ausente ou inválido. Não dá para conferir o resultado." for name in repair_names})
        m["survival_counts"] = {"0": len(all_flags), **{str(k): len(v) for k, v in sorted(self.queues.items()) if v}}
        reasons["survival_counts"] = "Rodada 0 conta todos os relatórios. As seguintes contam a fila de cura: são bases diferentes."
        return m, reasons


def metric_comparison(audit: CellAudit, recorded: dict | None) -> list[dict]:
    rows = []
    for name, value in audit.metrics.items():
        old = (recorded or {}).get(name)
        parsed_old = old
        if old not in (None, ""):
            try:
                parsed_old = json.loads(old)
            except (ValueError, TypeError):
                pass
        else:
            parsed_old = None
        reason = audit.metric_reasons.get(name, "")
        delta = None
        if value is None:
            state = "not_verifiable" if reason else "not_applicable"
        elif recorded is None:
            state = "missing_cell"
        elif name not in recorded:
            state = "missing_metric"
        else:
            state = "match" if parsed_old == value else "different"
            if isinstance(value, (float, int)) and isinstance(parsed_old, (float, int)):
                delta = round(value - parsed_old, 8)
        rows.append(dict(model=audit.model, cell=audit.slug, metric=name, recorded=parsed_old, recomputed=value, delta=delta, comparison=state, validity="legacy_definition_only" if reason and value is not None else state if value is None else "artifact_count", reason=reason, recorded_source_relative_path="results/metrics.csv", cell_relative_path=audit.root.absolute().relative_to(audit.repo.absolute()).as_posix()))
    return rows


def render_report(audits: list[CellAudit], comparisons: list[dict], metadata: dict) -> str:
    from .health_report import render_health_report
    return render_health_report(
        [audit.summary for audit in audits], comparisons,
        [row for audit in audits for row in audit.anomalies], metadata,
    )


def run_audit(repo: Path, output: Path, model: str | None = None, cell: str | None = None) -> dict:
    repo, output = repo.resolve(), output.resolve()
    validate_output(repo, output)
    roots = sorted(p for p in (repo / "collected_code_6").glob("*/*") if p.is_dir() and (model is None or p.parent.name == model) and (cell is None or p.name == cell))
    if not roots:
        raise ValueError("Nenhuma célula corresponde à seleção.")
    started = time.monotonic()
    metadata = dict(version=VERSION, started_at=datetime.now(timezone.utc).isoformat(), repo=str(repo), output=str(output), model=model, cell=cell, selected_cells=[str(p.relative_to(repo)) for p in roots], checker_sha256=hashlib.sha256(Path(__file__).read_bytes()).hexdigest(), status="running")
    metadata["generated_files"] = ["summary.csv", "anomalies.csv", "metrics_comparison.csv", "report.md", "run.json"] + ["cells/" + p.parent.name + "__" + p.name + suffix for p in roots for suffix in (".csv", ".anomalies.csv")]
    print(f"Inventariando entradas; {len(roots)} células selecionadas.", flush=True)
    before = input_inventory(repo)
    metrics_path = repo / "results" / "metrics.csv"
    metrics_bytes = metrics_path.read_bytes() if metrics_path.exists() else b""
    metadata["metrics_sha256_before"] = hashlib.sha256(metrics_bytes).hexdigest()
    recorded = {}
    if metrics_bytes:
        import io
        for row in csv.DictReader(io.StringIO(metrics_bytes.decode("utf-8-sig"))):
            key = (row["model"], row["cell"])
            if key in recorded:
                raise ValueError(f"Duplicated metrics key: {key}")
            recorded[key] = row
    atomic_text(output / "run.json", dumps(metadata) + "\n")
    audits, comparisons = [], []
    for index, root in enumerate(roots, 1):
        audit = CellAudit(repo, root)
        audit.run()
        audits.append(audit)
        comparisons.extend(metric_comparison(audit, recorded.get((audit.model, audit.slug))))
        stem = audit.model + "__" + audit.slug
        atomic_csv(output / "cells" / (stem + ".csv"), audit.details)
        atomic_csv(output / "cells" / (stem + ".anomalies.csv"), audit.anomalies, ANOMALY_FIELDS)
        # Bound memory to one cell's source bodies; the report needs aggregates.
        audit.sources.clear()
        audit.details.clear()
        audit.queues.clear()
        print(f"[{index}/{len(roots)}] {audit.model}/{audit.slug}: {audit.summary['annotations_match']}/{audit.summary['annotations_checked']} anotações reproduzidas", flush=True)
    after = input_inventory(repo)
    changed = sorted(k for k in before.keys() | after.keys() if before.get(k) != after.get(k))
    final_metrics = metrics_path.read_bytes() if metrics_path.exists() else b""
    metadata.update(completed_at=datetime.now(timezone.utc).isoformat(), elapsed_seconds=round(time.monotonic() - started, 3), status="completed" if not changed else "inputs_changed", input_stability="unchanged" if not changed else "changed_during_audit", changed_inputs=changed, inventory_files=len(before), inventory_digest_before=hashlib.sha256(dumps(before).encode()).hexdigest(), inventory_digest_after=hashlib.sha256(dumps(after).encode()).hexdigest(), metrics_sha256_after=hashlib.sha256(final_metrics).hexdigest())
    atomic_csv(output / "summary.csv", [dict(a.summary, ledger_attempts=dict(a.ledger_counts), input_stability=metadata["input_stability"]) for a in audits])
    atomic_csv(output / "anomalies.csv", [r for a in audits for r in a.anomalies], ANOMALY_FIELDS)
    atomic_csv(output / "metrics_comparison.csv", comparisons)
    atomic_text(output / "report.md", render_report(audits, comparisons, metadata))
    atomic_text(output / "run.json", dumps(metadata) + "\n")
    return metadata


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--repo-root", type=Path, default=REPO_ROOT)
    parser.add_argument("--output-dir", type=Path, default=Path("reports/code-health"))
    selection = parser.add_mutually_exclusive_group(required=True)
    selection.add_argument("--all", action="store_true")
    selection.add_argument("--model")
    parser.add_argument("--cell", help="Exact cell slug; requires --model")
    args = parser.parse_args(argv)
    if args.cell and not args.model:
        parser.error("--cell requires --model")
    try:
        result = run_audit(args.repo_root, args.output_dir, args.model, args.cell)
    except (ValueError, OSError) as exc:
        parser.exit(2, f"health_check: {exc}\n")
    print(f"Relatório: {args.output_dir.resolve() / 'report.md'}")
    return 0 if result["status"] == "completed" else 2


if __name__ == "__main__":
    raise SystemExit(main())

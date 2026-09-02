"""Multi-analyzer static analysis gate (revives the v1 4-tool pipeline).

Runs, for every ``.c`` in a directory:
- GCC ``-fanalyzer``          -> .gcc.txt
- Clang static analyzer + Z3  -> .clang.txt
- Cppcheck Premium bughunting -> .cppcheck.txt
- Flawfinder                  -> .flawfinder.txt
- compile gate (GCC ``-c``)   -> .o  (records compilability)

Tool paths/flags come from config/tools.yaml. Any missing tool is skipped
with a warning so the pipeline never hard-fails on tooling.
"""
from __future__ import annotations

import os
import subprocess
from concurrent.futures import ThreadPoolExecutor, as_completed

import yaml
from tqdm import tqdm

REPORT_SUFFIX = ".txt"  # appended to tool report suffix per file


def _load_tools(path: str = "config/tools.yaml") -> dict:
    with open(path) as f:
        return yaml.safe_load(f)["tools"]


def analyze(source_dir: str, tools: list[str] | None = None, compile_gate: bool = True) -> dict:
    """Analyze every .c in source_dir. Returns {tool: file_count}. """
    tools_cfg = _load_tools()
    selected = tools or list(tools_cfg.keys())
    files = [f for f in sorted(os.listdir(source_dir)) if f.endswith(".c")]
    if not files:
        return {}

    results: dict[str, int] = {}
    with ThreadPoolExecutor(max_workers=6) as pool:
        futures = []
        for file in files:
            base = os.path.join(source_dir, file)
            for tool in selected:
                if tool not in tools_cfg:
                    continue
                cfg = tools_cfg[tool]
                suffix = cfg.get("report_suffix", f".{tool}.txt")
                out = base[:-2] + suffix
                if os.path.exists(out):
                    continue  # resumability: keep existing reports
                futures.append(pool.submit(_run_one, base, tool, cfg))
            if compile_gate and "gcc" in selected:
                obj = base[:-2] + ".o"
                if not os.path.exists(obj):
                    futures.append(pool.submit(_compile_gate, base, tools_cfg["gcc"]))
        for fut in tqdm(as_completed(futures), total=len(futures), desc="Static analysis: "):
            tool = fut.result()
            if tool:
                results[tool] = results.get(tool, 0) + 1
    return results


def _run_one(src: str, tool: str, cfg: dict) -> str | None:
    path = cfg["path"]
    if not os.path.exists(path):
        print(f"[warn] {tool} not found at {path}; skipping")
        return None
    flags = list(cfg.get("analyzer_flags", []))
    out = src[:-2] + cfg["report_suffix"]
    cmd = [path] + flags + [src]
    try:
        with open(out, "w") as f:
            subprocess.run(
                cmd, stdout=f, stderr=subprocess.STDOUT, timeout=120, check=False
            )
        return tool
    except subprocess.TimeoutExpired:
        with open(out, "w") as f:
            f.write(f"{src}:0:0: error: {tool} timed out\n")
        return tool
    except Exception as ex:  # noqa: BLE001
        print(f"[warn] {tool} failed on {src}: {ex}")
        return None


def _compile_gate(src: str, cfg: dict) -> str | None:
    path = cfg["path"]
    if not os.path.exists(path):
        return None
    obj = src[:-2] + ".o"
    cmd = [path] + list(cfg.get("compile_flags", ["-c", "-w"])) + [src, "-o", obj]
    try:
        subprocess.run(cmd, capture_output=True, timeout=60, check=False)
        return "compile"
    except Exception:  # noqa: BLE001
        return None


if __name__ == "__main__":
    import sys

    analyze(sys.argv[1])

"""Adapter for Replicate-hosted models (Claude, GPT, Gemini).

Uses the official ``replicate`` Python library. Replicate predictions run
asynchronously; we create + wait and then read ``prediction.metrics`` for
per-call token consumption (``input_token_count`` / ``output_token_count``)
and server-side timing.

Input-parameter names differ per model family (e.g. ``max_tokens`` vs
``max_completion_tokens`` vs ``max_output_tokens``; ``system_prompt`` vs
``system_instruction``), and several Replicate hosts expose NO sampling
parameters at all (claude-fable-5, gpt-5.6-sol). The adapter therefore
fetches each model's input schema once, caches it, and maps our unified
parameter set onto whatever the host actually accepts. Anything the host
does not support (e.g. temperature) is silently dropped and recorded in
``LLMResponse.raw["dropped_params"]`` so the experiment notes it.
"""
from __future__ import annotations

import threading

from .client import LLMResponse
from .retry import retry_call

# our param -> candidate Replicate input names (first match in schema wins)
_MAX_TOKEN_NAMES = ["max_tokens", "max_completion_tokens", "max_output_tokens"]
_SYSTEM_NAMES = ["system_prompt", "system_instruction"]


class ReplicateClient:
    def __init__(self, cfg) -> None:
        import replicate

        self.cfg = cfg
        self.client = replicate.Client(api_token=cfg.api_key)
        self._schema_lock = threading.Lock()
        self._input_props: dict | None = None

    # ---- schema discovery (cached) ----
    def _input_properties(self) -> dict:
        with self._schema_lock:
            if self._input_props is None:
                model = self.client.models.get(self.cfg.model_id)
                version = model.latest_version
                if version is None or not version.openapi_schema:
                    # No schema published: assume the common prompt/system shape.
                    self._input_props = {"prompt": {}, "system_prompt": {},
                                         "max_tokens": {}}
                else:
                    schema = version.openapi_schema
                    self._input_props = (
                        schema.get("components", {})
                        .get("schemas", {})
                        .get("Input", {})
                        .get("properties", {})
                        or {}
                    )
            return self._input_props

    def _clamp_min(self, name: str, value: int) -> int:
        """Respect schema minimums (e.g. claude-fable-5 max_tokens >= 1024)."""
        prop = self._input_properties().get(name)
        if isinstance(prop, dict) and "minimum" in prop:
            return max(int(value), int(prop["minimum"]))
        return value

    # ---- completion ----
    def complete(
        self,
        messages: list[dict],
        *,
        temperature: float = 1.0,
        top_p: float = 1.0,
        max_tokens: int = 4096,
        reasoning: bool = False,
    ) -> LLMResponse:
        props = self._input_properties()

        # Flatten the message list into a single prompt + system prompt
        # (Replicate chat hosts take one prompt, not a message array).
        system_parts = [m["content"] for m in messages if m.get("role") == "system"]
        user_parts = [m["content"] for m in messages if m.get("role") != "system"]
        prompt = "\n\n".join(user_parts)
        system_text = "\n\n".join(system_parts)

        inp: dict = {"prompt": prompt}
        dropped: list[str] = []

        # system prompt: first supported param wins, else prepend to prompt
        system_param = next((n for n in _SYSTEM_NAMES if n in props), None)
        if system_param and system_text:
            inp[system_param] = system_text
        elif system_text:
            inp["prompt"] = system_text + "\n\n" + prompt

        # max tokens: first supported param wins (clamped to schema minimum)
        max_param = next((n for n in _MAX_TOKEN_NAMES if n in props), None)
        if max_param:
            inp[max_param] = self._clamp_min(max_param, max_tokens)

        # sampling params: only when the host exposes them; reasoning
        # variants never send them (hosts reject sampling on thinking paths)
        is_reasoning = bool(self.cfg.reasoning or reasoning)
        for key, value in (("temperature", temperature), ("top_p", top_p)):
            if key not in props or is_reasoning:
                dropped.append(key)
            else:
                inp[key] = value

        # Reasoning controls surface as native Replicate input params
        # (gemini thinking_level; openai reasoning_effort). cfg.extra_body
        # carries the pinned values; only pass what the host accepts.
        for key, value in (self.cfg.extra_body or {}).items():
            if key in props:
                inp[key] = value

        def _call():
            pred = self.client.predictions.create(
                model=self.cfg.model_id, input=inp
            )
            pred.wait()
            if pred.status == "failed":
                raise RuntimeError(
                    f"replicate prediction failed: {pred.error}"
                )
            return pred

        pred = retry_call(_call, provider="replicate")

        output = pred.output
        if isinstance(output, (list, tuple)):
            text = "".join(str(x) for x in output)
        else:
            text = str(output or "")
        if not text.strip():
            raise RuntimeError(
                "empty completion content "
                f"(status={pred.status}); reasoning-only or truncated response"
            )

        metrics = dict(pred.metrics or {})
        # Hosts report tokens under two different key styles: Claude uses
        # input_token_count/output_token_count; OpenAI uses
        # token_input_count/token_output_count. Read either.
        in_tok = int(metrics.get("input_token_count")
                     or metrics.get("token_input_count") or 0)
        out_tok = int(metrics.get("output_token_count")
                      or metrics.get("token_output_count") or 0)
        usage = {
            "prompt_tokens": in_tok,
            "completion_tokens": out_tok,
            "total_tokens": in_tok + out_tok,
            "reasoning_tokens": 0,
        }
        return LLMResponse(
            text=text,
            reasoning=None,
            model=f"{self.cfg.model_id}:{pred.id[:8]}",
            usage=usage,
            raw={
                "prediction_id": pred.id,
                "metrics": metrics,
                "dropped_params": dropped,
                "input_keys": sorted(inp.keys()),
            },
        )

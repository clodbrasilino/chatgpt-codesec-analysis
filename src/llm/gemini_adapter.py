"""Google Gemini adapter with thinking support (google-genai SDK)."""
from __future__ import annotations

from google import genai
from google.genai import types as genai_types

from .client import LLMResponse
from .retry import retry_call


class GeminiClient:
    def __init__(self, cfg) -> None:
        self.cfg = cfg
        self.client = genai.Client(api_key=cfg.api_key)

    def complete(
        self,
        messages: list[dict],
        *,
        temperature: float = 1.0,
        top_p: float = 1.0,
        max_tokens: int = 4096,
        reasoning: bool = False,
    ) -> LLMResponse:
        thinking = (self.cfg.reasoning or reasoning) and not self.cfg.disable_thinking
        # Gemini expects a single user prompt for code tasks; concatenate
        # system + user content like the other providers present it.
        prompt = _flatten(messages)
        gen_config = genai_types.GenerateContentConfig(
            max_output_tokens=max_tokens,
        )
        # Gemini 3.x controls reasoning depth via thinking_level
        # (low / medium / high; verified 2026-09-05, google-genai 2.20.0).
        # The registry pins the level per variant in cfg.extra_body —
        # there is no "off" for Gemini 3.x Pro: base runs "low".
        level = (self.cfg.extra_body or {}).get("thinking_level")
        if thinking or level:
            tc_kwargs: dict = {}
            if level:
                tc_kwargs["thinking_level"] = level
            if thinking:
                tc_kwargs["include_thoughts"] = True
            gen_config.thinking_config = genai_types.ThinkingConfig(**tc_kwargs)
        if not thinking:
            gen_config.temperature = temperature
            gen_config.top_p = top_p

        def _call():
            return self.client.models.generate_content(
                model=self.cfg.model_id,
                contents=prompt,
                config=gen_config,
            )

        resp = retry_call(_call, provider=self.cfg.provider)
        text = resp.text or ""
        reasoning = None
        # Thinking traces are exposed in thought parts when include_thoughts=True.
        if resp.candidates:
            parts = resp.candidates[0].content.parts
            thought_texts = [p.thought for p in parts if getattr(p, "thought", None)]
            if thought_texts:
                reasoning = "\n".join(thought_texts)
        usage = {}
        if resp.usage_metadata:
            usage = {
                "prompt_tokens": resp.usage_metadata.prompt_token_count,
                "completion_tokens": resp.usage_metadata.candidates_token_count,
                "total_tokens": (
                    resp.usage_metadata.prompt_token_count
                    + resp.usage_metadata.candidates_token_count
                ),
            }
        return LLMResponse(
            text=text,
            reasoning=reasoning,
            model=self.cfg.model_id,
            usage=usage,
            raw=resp.model_dump(),
        )


def _flatten(messages: list[dict]) -> str:
    parts = []
    for m in messages:
        content = m.get("content", "")
        if isinstance(content, list):
            content = " ".join(
                c.get("text", "") if isinstance(c, dict) else str(c) for c in content
            )
        if m.get("role") == "system":
            parts.append(f"System: {content}")
        elif m.get("role") == "user":
            parts.append(content)
    return "\n\n".join(parts)

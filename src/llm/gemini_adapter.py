"""Google Gemini adapter with thinking support (google-genai SDK).

Two serving surfaces, selected by environment:

* Vertex AI (Agent Platform) when ``GEMINI_USE_VERTEX=1`` and
  ``GOOGLE_CLOUD_PROJECT`` are both set. Authenticates
  with Application Default Credentials (``gcloud auth application-default
  login``) and bills the project's Cloud billing account, so Google Cloud
  credits apply. There is no fixed requests-per-day cap here.
* Gemini Developer API (AI Studio) otherwise, via ``GEMINI_API_KEY``. Cloud
  credits do NOT pay for this surface, and Tier-1 projects are capped at a few
  hundred requests per day.
"""
from __future__ import annotations

import os

from google import genai
from google.genai import types as genai_types

from .client import LLMResponse
from .retry import retry_call


class GeminiClient:
    def __init__(self, cfg) -> None:
        self.cfg = cfg
        # Explicit opt-in: gcloud and GCE/Cloud Run metadata set
        # GOOGLE_CLOUD_PROJECT on their own, so it alone must not reroute a sweep.
        project = os.getenv("GOOGLE_CLOUD_PROJECT")
        if project and os.getenv("GEMINI_USE_VERTEX", "").lower() in ("1", "true", "yes"):
            self.surface = "vertex"
            self.client = genai.Client(
                vertexai=True,
                project=project,
                location=os.getenv("GOOGLE_CLOUD_LOCATION", "global"),
            )
        else:
            self.surface = "aistudio"
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
        if resp.candidates and resp.candidates[0].content:
            parts = resp.candidates[0].content.parts or []
            # Part.thought is a bool flag; the trace is in Part.text.
            thought_texts = [p.text for p in parts if getattr(p, "thought", False) and p.text]
            if thought_texts:
                reasoning = "\n".join(thought_texts)
        usage = {}
        if resp.usage_metadata:
            um = resp.usage_metadata
            prompt_tokens = um.prompt_token_count or 0
            candidates = um.candidates_token_count or 0
            # Thinking is billed as output. Vertex excludes it from
            # candidates_token_count; the Developer API already includes it.
            thoughts = getattr(um, "thoughts_token_count", 0) or 0
            completion = candidates + thoughts if self.surface == "vertex" else candidates
            usage = {
                "prompt_tokens": prompt_tokens,
                "completion_tokens": completion,
                "reasoning_tokens": thoughts,
                # SDK total also covers cached and tool-use tokens.
                "total_tokens": um.total_token_count or (prompt_tokens + completion),
                "surface": self.surface,
            }
        return LLMResponse(
            text=text,
            reasoning=reasoning,
            # Surface distinguishes the arms: same weights, different serving.
            model=f"{self.cfg.model_id}@{self.surface}",
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

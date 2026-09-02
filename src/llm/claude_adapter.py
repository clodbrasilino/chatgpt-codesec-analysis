"""Anthropic Claude adapter with extended-thinking support."""
from __future__ import annotations

import anthropic

from .client import LLMResponse
from .retry import retry_call


class ClaudeClient:
    def __init__(self, cfg) -> None:
        self.cfg = cfg
        self.client = anthropic.Anthropic(api_key=cfg.api_key)

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
        # NOTE (2026-08-31): Claude 4.6+ / Sonnet 5 / Opus 5 / Fable 5 use
        # ADAPTIVE thinking (effort levels) — the manual budget_tokens toggle
        # below is the legacy API and will need updating once ANTHROPIC_API_KEY
        # arrives and the current SDK's parameter shape can be verified.
        kwargs: dict = {
            "model": self.cfg.model_id,
            "messages": messages,
            "max_tokens": max_tokens,
        }
        if thinking:
            kwargs["thinking"] = {
                "type": "enabled",
                "budget_tokens": min(max_tokens, 4096),
            }
        else:
            kwargs["temperature"] = temperature
            if top_p is not None:
                kwargs["top_p"] = top_p

        def _call():
            return self.client.messages.create(**kwargs)

        resp = retry_call(_call, provider=self.cfg.provider)

        text_parts: list[str] = []
        thinking_parts: list[str] = []
        for block in resp.content:
            if block.type == "text":
                text_parts.append(block.text)
            elif block.type == "thinking":
                thinking_parts.append(block.thinking)
        usage = {
            "prompt_tokens": resp.usage.input_tokens,
            "completion_tokens": resp.usage.output_tokens,
            "total_tokens": resp.usage.input_tokens + resp.usage.output_tokens,
        }
        return LLMResponse(
            text="".join(text_parts),
            reasoning="".join(thinking_parts) if thinking_parts else None,
            model=resp.model,
            usage=usage,
            raw=resp.model_dump(),
        )

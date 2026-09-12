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
        # NOTE (2026-09-13, key-time verification DONE): anthropic SDK 1.2.0
        # REMOVED temperature/top_p from messages.create (Fable 5 = adaptive
        # thinking, sampling params no longer accepted by the API). Base
        # cells send no thinking config -> model-default adaptive behavior,
        # matching the registered base-only entry for claude-fable-5.
        kwargs: dict = {
            "model": self.cfg.model_id,
            "messages": messages,
            "max_tokens": max_tokens,
        }
        if thinking:
            budget = min(max_tokens, 4096)
            if budget >= 1024 and budget < max_tokens:
                kwargs["thinking"] = {"type": "enabled", "budget_tokens": budget}

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

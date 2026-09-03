"""Adapter for the OpenAI-compatible providers.

Covers: OpenAI, DeepSeek, Qwen (DashScope compatible-mode),
Kimi (Moonshot), GLM (Zhipu). All expose the ``/chat/completions``
shape; reasoning variants surface ``reasoning_content`` on the message.
"""
from __future__ import annotations

from openai import OpenAI

from .client import LLMResponse
from .retry import retry_call


class OpenAICompatibleClient:
    def __init__(self, cfg) -> None:
        self.cfg = cfg
        self.client = OpenAI(api_key=cfg.api_key, base_url=cfg.base_url)

    def complete(
        self,
        messages: list[dict],
        *,
        temperature: float = 1.0,
        top_p: float = 1.0,
        max_tokens: int = 4096,
        reasoning: bool = False,
    ) -> LLMResponse:
        kwargs: dict = {"model": self.cfg.model_id, "messages": messages}
        # Provider-specific extra body (e.g. GLM/DeepSeek thinking toggles)
        # applies on BOTH paths: hybrid models need "thinking: disabled" even
        # for their non-reasoning configuration. Must go through the SDK's
        # extra_body= parameter — unknown kwargs raise TypeError.
        if self.cfg.extra_body:
            kwargs["extra_body"] = dict(self.cfg.extra_body)
        if self.cfg.reasoning or reasoning or self.cfg.no_sampling:
            # Reasoning variants across providers reject temperature/top_p
            # (e.g. DeepSeek-R1, o-series). kimi-k3 on DashScope rejects
            # sampling params even on its non-thinking path (no_sampling).
            # o-series needs max_completion_tokens.
            if self.cfg.provider == "openai":
                kwargs["max_completion_tokens"] = max_tokens
            else:
                kwargs["max_tokens"] = max_tokens
        else:
            kwargs.update(
                temperature=temperature,
                top_p=top_p,
                max_tokens=max_tokens,
            )

        def _call():
            return self.client.chat.completions.create(**kwargs)

        resp = retry_call(_call, provider=self.cfg.provider)
        message = resp.choices[0].message
        finish = resp.choices[0].finish_reason
        content = message.content or ""
        if not content.strip():
            # Empty content must never be treated as "clean code" (empty .c
            # files sail through every analyzer). Raise so the retry layers
            # kick in; _safe re-attempts and the batch runner moves on.
            raise RuntimeError(
                f"empty completion content (finish_reason={finish}); "
                "reasoning-only or truncated response"
            )
        reasoning_text = getattr(message, "reasoning_content", None)
        usage = resp.usage.model_dump() if resp.usage else {}
        return LLMResponse(
            text=content,
            reasoning=reasoning_text,
            model=resp.model,
            usage=usage,
            raw=resp.model_dump(),
        )

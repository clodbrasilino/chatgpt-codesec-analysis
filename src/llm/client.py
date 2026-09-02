"""Core LLM client interfaces for the multi-model experiment.

Unified abstraction so the rest of the pipeline is model-agnostic.
Reasoning (deep thinking) is modeled as a *variant selector*: a reasoning
model is a distinct registry entry (e.g. ``deepseek-reasoner`` vs
``deepseek-chat``), which is how the underlying APIs actually expose it.
"""
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Protocol, runtime_checkable


@dataclass
class LLMResponse:
    """A normalized LLM completion."""

    text: str  # final answer (code), fences stripped by caller as needed
    reasoning: str | None = None  # thinking trace, when available
    model: str = ""
    usage: dict = field(default_factory=dict)  # prompt/completion/total tokens
    raw: dict = field(default_factory=dict)  # provider-native response, for audit


@runtime_checkable
class LLMClient(Protocol):
    """Any provider adapter."""

    def complete(
        self,
        messages: list[dict],
        *,
        temperature: float = 1.0,
        top_p: float = 1.0,
        max_tokens: int = 4096,
        reasoning: bool = False,
    ) -> LLMResponse: ...


def system_message(content: str) -> dict:
    return {"role": "system", "content": content}


def user_message(content: str) -> dict:
    return {"role": "user", "content": content}

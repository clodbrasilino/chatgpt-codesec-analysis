"""Model registry: loads config/models.yaml and builds clients."""
from __future__ import annotations

import os
from dataclasses import dataclass, field
from typing import Any

import yaml

from .claude_adapter import ClaudeClient
from .gemini_adapter import GeminiClient
from .openai_compatible import OpenAICompatibleClient
from .retry import set_concurrency


@dataclass
class ModelConfig:
    id: str  # canonical registry id, e.g. "deepseek-chat"
    provider: str  # openai | deepseek | dashscope | moonshot | zhipu | anthropic | gemini
    model_id: str  # actual API model identifier
    api_key_env: str = ""  # env var holding the API key
    base_url: str | None = None  # OpenAI-compatible base URL (chat providers)
    reasoning: bool = False  # True = this entry is the reasoning variant
    disable_thinking: bool = False  # force thinking OFF for a reasoning-capable model
    max_tokens: int = 4096
    default_temp: float = 1.0
    default_top_p: float = 1.0
    concurrency: int = 8
    extra_body: dict[str, Any] = field(default_factory=dict)

    @property
    def api_key(self) -> str:
        key = os.getenv(self.api_key_env, "") if self.api_key_env else ""
        if not key:
            raise RuntimeError(
                f"API key missing: set env var {self.api_key_env!r} for model {self.id}"
            )
        return key


def load_registry(path: str = "config/models.yaml") -> dict[str, ModelConfig]:
    with open(path) as f:
        data = yaml.safe_load(f)
    registry: dict[str, ModelConfig] = {}
    for entry in data["models"]:
        cfg = ModelConfig(**entry)
        registry[cfg.id] = cfg
        set_concurrency(cfg.provider, cfg.concurrency)
    return registry


def get_client(cfg: ModelConfig):
    if cfg.provider in ("anthropic",):
        return ClaudeClient(cfg)
    if cfg.provider in ("gemini",):
        return GeminiClient(cfg)
    if cfg.provider in ("openai", "deepseek", "dashscope", "moonshot", "zhipu"):
        return OpenAICompatibleClient(cfg)
    raise ValueError(f"unknown provider: {cfg.provider}")

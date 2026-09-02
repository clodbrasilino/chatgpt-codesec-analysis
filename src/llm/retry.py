"""Rate limiting, retries, and cost guards shared by all providers."""
from __future__ import annotations

import random
import threading
import time
from typing import Callable, TypeVar

T = TypeVar("T")


class RateLimitError(Exception):
    """Raised after retries are exhausted for a rate-limited call."""


class CostCapExceeded(Exception):
    """Raised when a cell/run would exceed its configured token budget."""


class _ProviderSemaphore:
    """Per-provider concurrency semaphore."""

    def __init__(self) -> None:
        self._locks: dict[str, threading.Semaphore] = {}
        self._guard = threading.Lock()

    def acquire(self, provider: str, concurrency: int) -> None:
        with self._guard:
            if provider not in self._locks:
                self._locks[provider] = threading.Semaphore(concurrency)
        self._locks[provider].acquire()

    def release(self, provider: str) -> None:
        with self._guard:
            sem = self._locks.get(provider)
        if sem is not None:
            sem.release()


_provider_semaphores = _ProviderSemaphore()
_concurrency: dict[str, int] = {"default": 8}


def set_concurrency(provider: str, n: int) -> None:
    _concurrency[provider] = n


def retry_call(
    fn: Callable[[], T],
    *,
    provider: str = "default",
    max_retries: int = 6,
    base_delay: float = 2.0,
    max_delay: float = 60.0,
) -> T:
    """Call ``fn`` with exponential backoff + jitter on transient failures.

    Uses a per-provider semaphore so concurrent threads respect the
    provider's rate limit. Transient failures: rate limits (429), 5xx,
    timeouts, and connection errors.
    """
    sem = _provider_semaphores
    sem.acquire(provider, _concurrency.get(provider, 8))
    try:
        attempt = 0
        while True:
            try:
                return fn()
            except Exception as ex:  # noqa: BLE001 - inspect below
                attempt += 1
                if attempt > max_retries or not _is_transient(ex):
                    raise
                delay = min(max_delay, base_delay * (2 ** (attempt - 1)))
                delay *= 0.5 + random.random()  # jitter
                time.sleep(delay)
    finally:
        sem.release(provider)


def _is_transient(ex: Exception) -> bool:
    msg = str(ex).lower()
    status = getattr(ex, "status_code", None) or getattr(ex, "code", None)
    if status in (429, 500, 502, 503, 504):
        return True
    if status is not None and isinstance(status, int):
        return status >= 500
    return any(
        token in msg
        for token in (
            "rate limit",
            "rate_limit",
            "too many requests",
            "overloaded",
            "timeout",
            "timed out",
            "connection",
            "temporarily unavailable",
            "server error",
            "try again",
            "please retry",
            "429",
            "502",
            "503",
            "504",
        )
    )


class TokenBudget:
    """Simple in-process token budget to stop a run before it overruns."""

    def __init__(self, cap_tokens: int | None = None) -> None:
        self.cap = cap_tokens
        self.used = 0
        self._lock = threading.Lock()

    def charge(self, usage: dict) -> None:
        if not usage:
            return
        total = int(usage.get("total_tokens", 0) or 0)
        with self._lock:
            self.used += total
            if self.cap and self.used > self.cap:
                raise CostCapExceeded(
                    f"token budget exceeded: {self.used} > {self.cap}"
                )

#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod) {
    if (a >= mod - b) {
        return a - (mod - b);
    }
    return a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod) {
    uint64_t res = 0;
    a %= mod;
    b %= mod;
    while (b > 0) {
        if (b & 1U) {
            res = add_mod(res, a, mod);
        }
        a = add_mod(a, a, mod);
        b >>= 1;
    }
    return res;
}

static uint64_t pow_mod(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1U) {
            res = mul_mod(res, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return res;
}

static bool miller_rabin(uint64_t n) {
    static const uint64_t bases[] = {
        2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL
    };

    if (n < 2) {
        return false;
    }
    if (n % 2 == 0) {
        return n == 2;
    }
    if (n % 3 == 0) {
        return n == 3;
    }

    uint64_t d = n - 1;
    int s = 0;
    while ((d & 1U) == 0) {
        d >>= 1;
        ++s;
    }

    for (size_t i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        uint64_t a = bases[i];
        if (a % n == 0) {
            continue;
        }

        uint64_t x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }

        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }

        if (composite) {
            return false;
        }
    }

    return true;
}

static bool is_prime(uint64_t n) {
    if (n < 2) {
        return false;
    }
    if (n % 2 == 0) {
        return n == 2;
    }
    if (n % 3 == 0) {
        return n == 3;
    }
    return miller_rabin(n);
}

static uint64_t nth_newman_shanks_williams_prime(uint32_t n) {
    if (n == 0) {
        return 0;
    }

    uint64_t a = 1;
    uint64_t b = 1;
    uint32_t count = 0;

    while (count < n) {
        if (b > (UINT64_MAX - a) / 2) {
            return 0;
        }

        uint64_t c = 2 * b + a;
        a = b;
        b = c;

        if (is_prime(b)) {
            ++count;
            if (count == n) {
                return b;
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *endptr = NULL;
    unsigned long long input = strtoull(argv[1], &endptr, 10);

    if (errno != 0 || endptr == argv[1] || *endptr != '\0' || input == 0 || input > UINT32_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    uint64_t result = nth_newman_shanks_williams_prime((uint32_t)input);
    if (result == 0) {
        fprintf(stderr, "Result out of supported range\n");
        return EXIT_FAILURE;
    }

    printf("%llu\n", (unsigned long long)result);
    return EXIT_SUCCESS;
}
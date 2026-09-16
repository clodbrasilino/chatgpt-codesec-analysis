#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

static uint64_t power(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) res = (uint64_t)((__uint128_t)res * base % mod);
        base = (uint64_t)((__uint128_t)base * base % mod);
        exp >>= 1;
    }
    return res;
}

static uint64_t gcd(uint64_t a, uint64_t b) {
    while (b != 0) {
        uint64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static uint64_t modInverse(uint64_t n, uint64_t mod) {
    if (gcd(n, mod) != 1) return 0;
    return power(n, mod - 2, mod);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 0
  */

static uint64_t nCrModP(uint64_t n, uint64_t r, uint64_t p) {
    if (p <= 1) return 0;
    if (r > n) return 0;
    if (r > n - r) r = n - r;

    uint64_t res = 1;

    for (uint64_t i = 0; i < r; i++) {
        uint64_t num = (n - i) % p;
        uint64_t den = (i + 1) % p;

        res = (uint64_t)((__uint128_t)res * num % p);

        if (den != 0) {
            uint64_t inv = modInverse(den, p);
            if (inv != 0) {
                res = (uint64_t)((__uint128_t)res * inv % p);
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    return res;
}

int main(void) {
    uint64_t n, r, p;

    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        return 1;
    }

    printf("%" PRIu64 "\n", nCrModP(n, r, p));

    return 0;
}
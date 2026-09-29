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

static uint64_t modInverse(uint64_t n, uint64_t mod) {
    return power(n, mod - 2, mod);
}

uint64_t nCrModP(uint64_t n, uint64_t r, uint64_t p) {
    if (p <= 1) return 0;
    if (r > n) return 0;
    if (r > n - r) r = n - r;
    
    uint64_t numerator = 1;
    uint64_t denominator = 1;
    
    for (uint64_t i = 0; i < r; i++) {
        numerator = (uint64_t)((__uint128_t)numerator * ((n - i) % p) % p);
        denominator = (uint64_t)((__uint128_t)denominator * ((i + 1) % p) % p);
    }
    
    if (denominator == 0) return 0;
    
    return (uint64_t)((__uint128_t)numerator * modInverse(denominator, p) % p);
}

int main(void) {
    uint64_t n, r, p;
    
    if (scanf("%" SCNu64 " %" SCNu64 " %" SCNu64, &n, &r, &p) != 3) {
        return 1;
    }
    
    printf("%" PRIu64 "\n", nCrModP(n, r, p));
    
    return 0;
}
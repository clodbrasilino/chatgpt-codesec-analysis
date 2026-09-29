#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    int64_t result = 0;
    int64_t x = a % mod;
    int64_t y = b % mod;
    
    if (x < 0) x += mod;
    if (y < 0) y += mod;
    
    while (y > 0) {
        if (y & 1) {
            result = (result + x) % mod;
        }
        x = (x + x) % mod;
        y >>= 1;
    }
    
    return result;
}

int64_t power_mod(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    base %= mod;
    if (base < 0) base += mod;
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    
    return result;
}

int64_t mod_inverse(int64_t a, int64_t p) {
    return power_mod(a, p - 2, p);
}

int64_t ncr_mod_p(int64_t n, int64_t r, int64_t p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    
    if (r > n - r) {
        r = n - r;
    }

    int64_t numerator = 1;
    int64_t denominator = 1;

    for (int64_t i = 0; i < r; i++) {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

int main(void) {
    int64_t n, r, p;

    if (scanf("%" SCNd64 " %" SCNd64 " %" SCNd64, &n, &r, &p) != 3) {
        return 1;
    }

    if (p <= 1) {
        return 1;
    }

    printf("%" PRId64 "\n", ncr_mod_p(n, r, p));

    return 0;
}
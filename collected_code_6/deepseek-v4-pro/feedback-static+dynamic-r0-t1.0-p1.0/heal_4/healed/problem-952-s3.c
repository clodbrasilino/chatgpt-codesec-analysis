#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

int64_t mul_mod(int64_t a, int64_t b, int64_t mod) {
    int64_t result = 0;
    int64_t ua;
    int64_t ub;
    
    if (mod <= 0) {
        return 0;
    }
    
    ua = a % mod;
    if (ua < 0) {
        ua += mod;
    }
    ub = b % mod;
    if (ub < 0) {
        ub += mod;
    }
    
    while (ub > 0) {
        if (ub & 1) {
            result = (result + ua) % mod;
        }
        ua = (ua * 2) % mod;
        ub >>= 1;
    }
    return result;
}

int64_t power_mod(int64_t base, int64_t exp, int64_t mod) {
    int64_t result = 1;
    int64_t b;
    
    if (mod <= 0) {
        return 0;
    }
    
    b = base % mod;
    if (b < 0) {
        b += mod;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, b, mod);
        }
        b = mul_mod(b, b, mod);
        exp >>= 1;
    }
    return result;
}

int64_t mod_inverse(int64_t a, int64_t p) {
    int64_t result = 1;
    int64_t base = a % p;
    int64_t exp = p - 2;
    
    if (base < 0) {
        base += p;
    }
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, p);
        }
        base = mul_mod(base, base, p);
        exp >>= 1;
    }
    return result;
}

int64_t ncr_mod_p(int64_t n, int64_t r, int64_t p) {
    int64_t numerator;
    int64_t denominator;
    int64_t i;
    
    if (r > n || r < 0) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    
    if (r > n - r) {
        r = n - r;
    }
    
    numerator = 1;
    denominator = 1;
    
    for (i = 0; i < r; i++) {
        int64_t term1 = (n - i) % p;
        if (term1 < 0) {
            term1 += p;
        }
        int64_t term2 = (i + 1) % p;
        if (term2 < 0) {
            term2 += p;
        }
        numerator = mul_mod(numerator, term1, p);
        denominator = mul_mod(denominator, term2, p);
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
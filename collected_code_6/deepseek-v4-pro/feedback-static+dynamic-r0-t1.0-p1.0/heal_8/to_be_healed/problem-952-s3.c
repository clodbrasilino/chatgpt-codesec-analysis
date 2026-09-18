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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 5095444412972924928 + 4800441378590949377 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000001,time:30699,execs:20066,op:havoc,rep:15)
             * UBSan: signed integer overflow: 7540982587009872000 + 6058586904226856965 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:3753,execs:2497,op:havoc,rep:8)
             */
            result = (result + x);
            if (result >= mod) result -= mod;
        }
        if (x > mod - x) {
            x = x - (mod - x);
        } else {
            x = (x + x);
        }
        if (x >= mod) x -= mod;
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
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

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
        int64_t term1 = (n - i) % p;
        if (term1 < 0) term1 += p;
        numerator = mul_mod(numerator, term1, p);
        
        int64_t term2 = (i + 1) % p;
        if (term2 < 0) term2 += p;
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
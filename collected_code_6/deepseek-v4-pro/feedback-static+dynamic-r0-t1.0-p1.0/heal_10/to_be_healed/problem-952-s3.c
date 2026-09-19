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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8173347561818554368 + -6366401023241617408 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:10526,execs:6988,op:havoc,rep:9)
             * UBSan: signed integer overflow: 3294464004646478649 + 8539818392200282112 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:13471,execs:9035,op:havoc,rep:12)
             * UBSan: signed integer overflow: -2570961465443302412 + -8716392203632508928 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000048,time:47727,execs:37588,op:havoc,rep:4)
             * UBSan: signed integer overflow: 4385801986697535250 + 8090863307535810560 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000025,time:43396,execs:33614,op:havoc,rep:4)
             * UBSan: signed integer overflow: 7975661162230845433 + 9115041328263823352 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000000,time:19095,execs:12893,op:havoc,rep:14)
             */
            result = (result + ua) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7011906707722862592 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000000,time:10526,execs:6988,op:havoc,rep:9)
         * UBSan: signed integer overflow: 9101240000242790400 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000000,time:19095,execs:12893,op:havoc,rep:14)
         * UBSan: signed integer overflow: 8090863307535810560 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000025,time:43396,execs:33614,op:havoc,rep:4)
         * UBSan: signed integer overflow: 4611686018427387904 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000000,time:13471,execs:9035,op:havoc,rep:12)
         * UBSan: signed integer overflow: 7281777777777770496 * 2 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000048,time:47727,execs:37588,op:havoc,rep:4)
         */
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
    int64_t exp = p - 2;
    int64_t base = a % p;
    if (base < 0) base += p;
    
    while (exp > 0) {
        if (exp & 1) {
            result = mul_mod(result, base, p);
        }
        base = mul_mod(base, base, p);
        exp >>= 1;
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

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
        if (term2 == 0) {
            return 0;
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
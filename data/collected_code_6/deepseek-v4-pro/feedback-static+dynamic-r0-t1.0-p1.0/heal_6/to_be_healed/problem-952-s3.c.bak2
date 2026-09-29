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
             * UBSan: signed integer overflow: 2075440033261636314 + 8202194488605540352 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000051,time:55005,execs:17305,op:havoc,rep:1)
             * UBSan: signed integer overflow: 3294464004646478649 + 8539818392200282112 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:2510,execs:1752,op:havoc,rep:3)
             * UBSan: signed integer overflow: 8142508126285856768 + 1152921504606846976 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000029,time:30963,execs:14441,op:havoc,rep:8)
             * UBSan: signed integer overflow: -1044797064101350656 + -8210931927214096384 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000037,time:30641,execs:14237,op:havoc,rep:2)
             */
            result = (result + ua) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: left shift of 8202194488605540352 by 1 places cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000051,time:55005,execs:17305,op:havoc,rep:1)
         * UBSan: left shift of 4611686018427387904 by 1 places cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000001,time:2510,execs:1752,op:havoc,rep:3)
         * UBSan: left shift of 5674535530486824960 by 1 places cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000029,time:30963,execs:14441,op:havoc,rep:8)
         * UBSan: left shift of 5348081335519802880 by 1 places cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000037,time:30641,execs:14237,op:havoc,rep:2)
         */
        ua = (ua << 1) % mod;
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
    return power_mod(a, p - 2, p);
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
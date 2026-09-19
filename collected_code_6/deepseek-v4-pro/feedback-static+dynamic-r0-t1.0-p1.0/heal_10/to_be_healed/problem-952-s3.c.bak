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
             * UBSan: signed integer overflow: 5095444412972924928 + 4800441378590949377 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:2441,execs:1348,op:havoc,rep:1)
             */
            int64_t tmp = result + x;
            if (tmp < result) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -8550858282145677311 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:2441,execs:1348,op:havoc,rep:1)
                 */
                tmp -= mod;
            }
            result = tmp % mod;
            if (result < 0) result += mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7011906707722862592 + 7011906707722862592 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:2441,execs:1348,op:havoc,rep:1)
         */
        int64_t tmp = x + x;
        if (tmp < x) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -4422930658263826432 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:2441,execs:1348,op:havoc,rep:1)
             */
            tmp -= mod;
        }
        x = tmp % mod;
        if (x < 0) x += mod;
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
    
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -3 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000033,time:34047,execs:14493,op:havoc,rep:3)
     */
    if (r > n - r) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -3 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000033,time:34047,execs:14493,op:havoc,rep:3)
         */
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
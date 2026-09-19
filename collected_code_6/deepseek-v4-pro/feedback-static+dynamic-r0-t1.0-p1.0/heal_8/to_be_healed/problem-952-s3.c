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
             * UBSan: signed integer overflow: 9223372036854775807 - -8715136041002991614 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
             * UBSan: signed integer overflow: 9223372036854775807 - -4224521851487329406 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
             * UBSan: signed integer overflow: 9223372036854775807 - -242299629265108990 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
             * UBSan: signed integer overflow: 9223372036854775807 - -7208896787757070586 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
             * UBSan: signed integer overflow: 9223372036854775807 - -4422930658263826430 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
             */
            int64_t max_safe = INT64_MAX - ua;
            if (result > max_safe) {
                /* Possible weaknesses found:
                 * UBSan: signed integer overflow: -1731825341676299738 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
                 * UBSan: signed integer overflow: -3751982156024904930 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
                 * UBSan: signed integer overflow: -6828521572378166043 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
                 * UBSan: signed integer overflow: -3563612923971395835 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
                 * UBSan: signed integer overflow: -4531265925196884242 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
                 */
                result = result - mod;
            }
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -8550858282145677309 + -8845861316527652858 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
             * UBSan: signed integer overflow: -7368085076875898767 + -7208896787757070586 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
             * UBSan: signed integer overflow: -6790470028678135807 + -8715136041002991614 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
             * UBSan: signed integer overflow: -5500464442257320194 + -3876794068241743810 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
             * UBSan: signed integer overflow: -5670116110564327443 + -8449043702974658810 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
             */
            result = result + ua;
            if (result >= mod) {
                result -= mod;
            }
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -8715136041002991614 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
         * UBSan: signed integer overflow: 9223372036854775807 - -4224521851487329406 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
         * UBSan: signed integer overflow: 9223372036854775807 - -3604448393878535294 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
         * UBSan: signed integer overflow: 9223372036854775807 - -242299629265108990 cannot be represented in type 'long long' (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
         * UBSan: signed integer overflow: 9223372036854775807 - -4422930658263826430 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
         */
        int64_t max_safe_ua = INT64_MAX - ua;
        if (ua > max_safe_ua) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -2501321437349936620 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
             * UBSan: signed integer overflow: -4422930658263826430 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
             * UBSan: signed integer overflow: -4224521851487329406 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
             * UBSan: signed integer overflow: -242299629265108990 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
             * UBSan: signed integer overflow: -3604448393878535294 - 9223372036854775807 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
             */
            ua = ua - mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 8981072407589666819 + 8981072407589666819 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000004,sig:06,src:000028,time:52048,execs:34677,op:havoc,rep:14)
         * UBSan: signed integer overflow: 4998850185367446403 + 4998850185367446403 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000001,sig:06,src:000002,time:8763,execs:5796,op:havoc,rep:5)
         * UBSan: signed integer overflow: 4800441378590949379 + 4800441378590949379 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000000,sig:06,src:000002,time:4952,execs:3291,op:havoc,rep:2)
         * UBSan: signed integer overflow: -8715136041002991614 + -8715136041002991614 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000003,sig:06,src:000031,time:50311,execs:33219,op:havoc,rep:5)
         * UBSan: signed integer overflow: 5618923642976240515 + 5618923642976240515 cannot be represented in type 'int64_t' (aka 'long long') (AFL crash: id:000002,sig:06,src:000028,time:25856,execs:17131,op:havoc,rep:1)
         */
        ua = ua + ua;
        if (ua >= mod) {
            ua -= mod;
        }
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
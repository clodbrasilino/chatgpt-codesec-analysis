#include <stdio.h>
#include <stdlib.h>

long long power_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 52498200132 * -16475678310 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:2171,execs:1505,op:havoc,rep:2)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:2669,execs:1837,op:havoc,rep:3)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 43332129681 * 43332129681 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000002,time:2171,execs:1505,op:havoc,rep:2)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000002,time:2669,execs:1837,op:havoc,rep:3)
         */
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long p) {
    return power_mod(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 11, got <no output>
  *  test case 2 failed: expected 1, got <no output>
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -3 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000002,time:42138,execs:23046,op:havoc,rep:2)
     */
    if (r > n - r) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -3 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000002,time:42138,execs:23046,op:havoc,rep:2)
         */
        r = n - r;
    }

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 7 * 9223372036854775806 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000002,time:1095,execs:786,op:havoc,rep:1)
         */
        numerator = (numerator * (n - i)) % p;
        denominator = (denominator * (i + 1)) % p;
    }

    return (numerator * mod_inverse(denominator, p)) % p;
}

int main(void) {
    long long n, r, p;

    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        return 1;
    }

    if (p <= 1) {
        return 1;
    }

    printf("%lld\n", ncr_mod_p(n, r, p));

    return 0;
}
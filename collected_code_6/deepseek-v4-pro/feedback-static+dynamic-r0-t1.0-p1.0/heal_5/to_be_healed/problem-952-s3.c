#include <stdio.h>
#include <stdlib.h>

long long power_mod(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: -96199505766 * 7646849129 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:12885,execs:8775,op:havoc,rep:4)
             * UBSan: signed integer overflow: 3168587776 * 5106558976 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000005,time:26337,execs:17404,op:havoc,rep:2)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 43332128931 * 43332128931 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:12885,execs:8775,op:havoc,rep:4)
         * UBSan: signed integer overflow: 5106558976 * 5106558976 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000005,time:26337,execs:17404,op:havoc,rep:2)
         * UBSan: signed integer overflow: 718625041075929088 * 718625041075929088 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000016,time:22492,execs:15057,op:havoc,rep:1)
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
  *  test case 1 failed: expected 11, got 10
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 9223372036854775807 - -120 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000017,time:19985,execs:13546,op:havoc,rep:2)
     */
    if (r > n - r) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 9223372036854775807 - -120 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000017,time:19985,execs:13546,op:havoc,rep:2)
         */
        r = n - r;
    }

    long long numerator = 1;
    long long denominator = 1;

    for (long long i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 482088250322003520 * 882 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000016,time:22492,execs:15057,op:havoc,rep:1)
         */
        numerator = (numerator * ((n - i) % p)) % p;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1032902008176640000 * 21 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000016,time:22492,execs:15057,op:havoc,rep:1)
         */
        denominator = (denominator * ((i + 1) % p)) % p;
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
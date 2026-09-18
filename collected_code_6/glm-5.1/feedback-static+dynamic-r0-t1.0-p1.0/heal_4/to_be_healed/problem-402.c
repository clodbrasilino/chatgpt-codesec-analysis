#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 5843312253591 * 3119374093003 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:4360,execs:1973,op:havoc,rep:4)
             */
            result = (result * base) % mod;
        }
        exp = exp / 2;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:4360,execs:1973,op:havoc,rep:4)
         */
        base = (base * base) % mod;
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (p == 1) {
        return 0;
    }
    if (n >= p) {
        /* Possible weaknesses found:
         * ASan: FPE (AFL crash: id:000001,sig:06,src:000001,time:1072,execs:587,op:havoc,rep:4)
         * UBSan: division by zero (AFL crash: id:000001,sig:06,src:000001,time:1072,execs:587,op:havoc,rep:4)
         */
        return (ncr_mod_p(n / p, r / p, p) * ncr_mod_p(n % p, r % p, p)) % p;
    }
    r = r < (n - r) ? r : (n - r);
    long long res = 1;
    for (long long i = 1; i <= r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 16916855216925 * 16916855216926 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:4360,execs:1973,op:havoc,rep:4)
         */
        res = (res * (n - r + i)) % p;
        res = (res * mod_exp(i, p - 2, p)) % p;
    }
    return res;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000001,time:876,execs:489,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    while (scanf("%lld %lld %lld", &n, &r, &p) == 3) {
        printf("%lld\n", ncr_mod_p(n, r, p));
    }
    return 0;
}
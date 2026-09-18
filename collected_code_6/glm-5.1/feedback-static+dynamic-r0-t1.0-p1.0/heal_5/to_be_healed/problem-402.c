#include <stdio.h>
#include <stdlib.h>

long long mod_mul(long long a, long long b, long long mod) {
    long long result = 0;
    a = a % mod;
    while (b > 0) {
        if (b % 2 == 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 1098154668215492883 + 8995520821969944576 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:5728,execs:1820,op:havoc,rep:13)
             */
            result = (result + a) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 * 2 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:5728,execs:1820,op:havoc,rep:13)
         */
        a = (a * 2) % mod;
        b = b / 2;
    }
    return result;
}

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = mod_mul(result, base, mod);
        }
        exp = exp / 2;
        base = mod_mul(base, base, mod);
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
        return mod_mul(ncr_mod_p(n / p, r / p, p), ncr_mod_p(n % p, r % p, p), p);
    }
    r = r < (n - r) ? r : (n - r);
    long long res = 1;
    for (long long i = 1; i <= r; i++) {
        res = mod_mul(res, (n - r + i) % p, p);
        res = mod_mul(res, mod_exp(i, p - 2, p), p);
    }
    return res;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000001,sig:06,src:000014,time:46270,execs:18553,op:havoc,rep:3; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    while (scanf("%lld %lld %lld", &n, &r, &p) == 3) {
        if (p <= 0) {
            printf("0\n");
        } else {
            printf("%lld\n", ncr_mod_p(n, r, p));
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long mod_inverse(long long a, long long mod) {
    long long m0 = mod, y = 0, x = 1;
    if (mod == 1) return 0;
    a %= mod;
    if (a < 0) a += mod;
    while (a > 1) {
        long long q = a / mod;
        long long t = mod;
        mod = a % mod;
        a = t;
        t = y;
        y = x - q * y;
        x = t;
        if (mod == 0) return 0;
    }
    if (x < 0) x += m0;
    return x;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 1, got 0
  *  test case 1 failed: expected 11, got 0
  *  test case 0 failed: expected 6, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (r > n - r) {
        r = n - r;
    }

    long long *fact = (long long *)malloc(p * sizeof(long long));
    if (fact == NULL) {
        return 0;
    }

    fact[0] = 1;
    for (long long i = 1; i < p; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }

    long long result = 1;
    long long tn = n, tr = r;
    while (tn > 0 || tr > 0) {
        long long ni = tn % p;
        long long ri = tr % p;
        if (ri > ni) {
            free(fact);
            return 0;
        }
        result = (result * fact[ni]) % p;
        long long inv1 = mod_inverse(fact[ri], p);
        result = (result * inv1) % p;
        long long inv2 = mod_inverse(fact[ni - ri], p);
        result = (result * inv2) % p;
        tn /= p;
        tr /= p;
    }

    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:18516,execs:12743,op:havoc,rep:14; likely memory-safety defect
  */

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
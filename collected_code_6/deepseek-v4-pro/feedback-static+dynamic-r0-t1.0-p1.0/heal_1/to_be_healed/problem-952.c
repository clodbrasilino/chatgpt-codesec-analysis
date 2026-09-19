#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
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
    return mod_pow(a, mod - 2, mod);
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
    if (r > n - r) {
        r = n - r;
    }

    long long *fact = (long long *)malloc((p) * sizeof(long long));
    if (fact == NULL) {
        exit(1);
    }

    fact[0] = 1;
    for (long long i = 1; i < p; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }

    long long result = 1;
    while (n > 0 || r > 0) {
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni) {
            free(fact);
            return 0;
        }
        result = (result * fact[ni]) % p;
        result = (result * mod_inverse(fact[ri], p)) % p;
        result = (result * mod_inverse(fact[ni - ri], p)) % p;
        n /= p;
        r /= p;
    }

    free(fact);
    return result;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:1336,execs:907,op:havoc,rep:10; likely memory-safety defect
  */

int main(void) {
    long long n, r, p;
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        return 1;
    }
    printf("%lld\n", ncr_mod_p(n, r, p));
    return 0;
}
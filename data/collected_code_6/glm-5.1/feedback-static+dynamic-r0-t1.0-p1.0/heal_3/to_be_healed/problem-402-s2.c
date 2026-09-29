#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 25, got <no output>
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (p <= 1) {
        return 0;
    }

    long long c[r + 1];
    for (long long i = 0; i <= r; i++) {
        c[i] = 0;
    }
    c[0] = 1;

    for (long long i = 1; i <= n; i++) {
        long long prev = 1;
        for (long long j = 1; j <= r && j < i; j++) {
            long long temp = c[j];
            c[j] = (c[j] + prev) % p;
            prev = temp;
        }
    }

    return c[r];
}

int main(void) {
    long long n = 10;
    long long r = 2;
    long long p = 10;

    long long result = ncr_mod_p(n, r, p);
    printf("%lld\n", result);

    return 0;
}
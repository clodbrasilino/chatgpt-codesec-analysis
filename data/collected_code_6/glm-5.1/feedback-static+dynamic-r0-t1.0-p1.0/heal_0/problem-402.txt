#include <stdio.h>
#include <stdlib.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

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
    long long *fact = malloc((n + 1) * sizeof(long long));
    if (fact == NULL) {
        exit(EXIT_FAILURE);
    }
    fact[0] = 1;
    for (long long i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }
    long long inv_r = mod_exp(fact[r], p - 2, p);
    long long inv_n_r = mod_exp(fact[n - r], p - 2, p);
    long long result = (fact[n] * inv_r) % p;
    result = (result * inv_n_r) % p;
    free(fact);
    return result;
}

int main(void) {
    long long n = 10;
    long long r = 2;
    long long p = 13;
    long long result = ncr_mod_p(n, r, p);
    printf("%lld\n", result);
    return 0;
}
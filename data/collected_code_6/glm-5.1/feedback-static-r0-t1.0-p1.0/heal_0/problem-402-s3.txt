#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    if (base < 0) base += mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp /= 2;
        base = (base * base) % mod;
    }
    return result;
}

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    if (p == 1) return 0;

    long long *fact = (long long *)malloc((n + 1) * sizeof(long long));
    if (fact == NULL) {
        exit(EXIT_FAILURE);
    }

    fact[0] = 1;
    for (long long i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }

    long long inv_fact_r = mod_pow(fact[r], p - 2, p);
    long long inv_fact_n_r = mod_pow(fact[n - r], p - 2, p);

    long long result = (fact[n] * inv_fact_r) % p;
    result = (result * inv_fact_n_r) % p;

    free(fact);

    return result;
}

int main() {
    long long n = 10;
    long long r = 2;
    long long p = 13;
    long long res = ncr_mod_p(n, r, p);
    printf("%lld\n", res);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

long long mod_pow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = (res * base) % mod;
        }
        exp /= 2;
        base = (base * base) % mod;
    }
    return res;
}

int ncr_mod_p(int n, int r, int p) {
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1;
    }
    if (n >= p) {
        return 0;
    }

    long long *fact = (long long *)malloc((n + 1) * sizeof(long long));
    if (fact == NULL) {
        return -1;
    }

    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (fact[i - 1] % p == 0) {
            fact[i] = 0;
        } else {
            fact[i] = (fact[i - 1] * i) % p;
        }
    }

    long long inv_r = mod_pow(fact[r], p - 2, p);
    long long inv_nr = mod_pow(fact[n - r], p - 2, p);

    long long result = (fact[n] * inv_r) % p;
    result = (result * inv_nr) % p;

    free(fact);

    return (int)result;
}

int main(void) {
    printf("%d\n", ncr_mod_p(4, 2, 7));
    printf("%d\n", ncr_mod_p(10, 2, 13));
    printf("%d\n", ncr_mod_p(5, 0, 3));
    return 0;
}
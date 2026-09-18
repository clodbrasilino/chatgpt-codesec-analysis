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
    if (r > n - r) {
        r = n - r;
    }

    long long *c = (long long *)malloc((r + 1) * sizeof(long long));
    for (long long i = 0; i <= r; i++) {
        c[i] = 0;
    }
    c[0] = 1;

    for (long long i = 1; i <= n; i++) {
        long long limit = (r < i) ? r : i;
        long long prev = 1;
        for (long long j = 1; j <= limit; j++) {
            long long temp = c[j];
            c[j] = (c[j] + prev) % p;
            prev = temp;
        }
    }

    long long res = c[r];
    free(c);
    return res;
}

int main(void) {
    long long test_cases[][3] = {
        {10, 2, 10},
        {5, 2, 100},
        {5, 0, 10},
    };
    /* Possible weaknesses found:
     *  Variable 'expected' can be declared as const array [constVariable]
     */
    long long expected[] = {6, 10, 1};

    for (int i = 0; i < 3; i++) {
        long long n = test_cases[i][0];
        long long r = test_cases[i][1];
        long long p = test_cases[i][2];
        long long result = ncr_mod_p(n, r, p);
        if (result != expected[i]) {
            printf("Test case %d failed: expected %lld, got %lld\n", i, expected[i], result);
        } else {
            printf("Test case %d passed: %lld\n", i, result);
        }
    }

    return 0;
}
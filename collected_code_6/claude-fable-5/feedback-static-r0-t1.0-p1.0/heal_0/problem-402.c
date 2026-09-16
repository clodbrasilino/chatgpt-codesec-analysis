#include <stdio.h>
#include <stdlib.h>

long long power(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

long long mod_inverse(long long a, long long p)
{
    return power(a, p - 2, p);
}

long long ncr_mod_p(long long n, long long r, long long p)
{
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }

    long long *fact = malloc((size_t)(n + 1) * sizeof(long long));
    if (fact == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    fact[0] = 1;
    for (long long i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % p;
    }

    long long result = fact[n];
    result = (result * mod_inverse(fact[r], p)) % p;
    result = (result * mod_inverse(fact[n - r], p)) % p;

    free(fact);
    return result;
}

int main(void)
{
    long long n, r, p;

    printf("Enter n, r and prime p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values: require n >= 0, r >= 0, p > 1\n");
        return EXIT_FAILURE;
    }

    long long answer = ncr_mod_p(n, r, p);
    printf("C(%lld, %lld) %% %lld = %lld\n", n, r, p, answer);

    return EXIT_SUCCESS;
}
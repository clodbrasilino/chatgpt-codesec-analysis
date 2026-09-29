#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned long long ull;

ull mul_mod(ull a, ull b, ull p) {
    ull res = 0;
    a = a % p;
    while (b > 0) {
        if (b & 1)
            res = (res + a) % p;
        a = (a << 1) % p;
        b = b >> 1;
    }
    return res;
}

ull power(ull x, ull y, ull p) {
    ull res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1)
            res = mul_mod(res, x, p);
        y = y >> 1;
        x = mul_mod(x, x, p);
    }
    return res;
}

ull mod_inverse(ull n, ull p) {
    return power(n, p - 2, p);
}

int is_prime(ull n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (ull i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got -1
  */

long long ncr_mod_p(long long n, long long r, long long p) {
    if (r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;
    if (n - r < r)
        r = n - r;

    if (!is_prime((ull)p))
        return -1;

    ull *fact = (ull *)malloc(((size_t)n + 1) * sizeof(ull));
    if (fact == NULL)
        return -1;

    fact[0] = 1;
    ull mod = (ull)p;
    for (long long i = 1; i <= n; i++)
        fact[i] = mul_mod(fact[i - 1], (ull)i, mod);

    ull result = mul_mod(fact[n], mod_inverse(fact[r], mod), mod);
    result = mul_mod(result, mod_inverse(fact[n - r], mod), mod);

    free(fact);
    return (long long)result;
}

int main(void) {
    long long n, r, p;

    printf("Enter n, r, and p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid parameters\n");
        return 1;
    }

    long long result = ncr_mod_p(n, r, p);

    if (result == -1) {
        fprintf(stderr, "Memory allocation failed or p is not prime\n");
        return 1;
    }

    printf("%lldC%lld mod %lld = %lld\n", n, r, p, result);

    return 0;
}
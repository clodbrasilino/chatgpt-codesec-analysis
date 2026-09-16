#include <stdio.h>
#include <stdlib.h>

static long long power(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

static long long mod_inverse(long long a, long long p)
{
    return power(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

static long long ncr_mod_p(long long n, long long r, long long p)
{
    long long numerator;
    long long denominator;
    long long i;

    if (r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }
    if (r > n - r) {
        r = n - r;
    }

    numerator = 1;
    denominator = 1;
    for (i = 0; i < r; i++) {
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    if (denominator == 0) {
        return 0;
    }

    return (numerator * mod_inverse(denominator, p)) % p;
}

int main(void)
{
    long long n;
    long long r;
    long long p;
    long long result;

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter r: ");
    if (scanf("%lld", &r) != 1 || r < 0) {
        fprintf(stderr, "Invalid input for r\n");
        return EXIT_FAILURE;
    }

    printf("Enter prime p: ");
    if (scanf("%lld", &p) != 1 || p < 2) {
        fprintf(stderr, "Invalid input for p\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_p(n, r, p);
    printf("nCr %% p = %lld\n", result);

    return EXIT_SUCCESS;
}
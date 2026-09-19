#include <stdio.h>
#include <stdlib.h>

long long power_mod(long long base, long long exp, long long mod);
long long mod_inverse(long long a, long long p);
long long ncr_small_mod_p(long long n, long long r, long long p);
long long ncr_mod_p(long long n, long long r, long long p);

long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1;

    if (mod <= 0) {
        return -1;
    }

    base = base % mod;
    if (base < 0) {
        base += mod;
    }

    while (exp > 0) {
        if (exp & 1LL) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1LL;
    }

    return result;
}

long long mod_inverse(long long a, long long p)
{
    if (p <= 1) {
        return -1;
    }

    a = a % p;
    if (a < 0) {
        a += p;
    }

    if (a == 0) {
        return -1;
    }

    return power_mod(a, p - 2, p);
}

long long ncr_small_mod_p(long long n, long long r, long long p)
{
    long long numerator = 1;
    long long denominator = 1;
    long long i;
    long long inv;

    if (r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = 0; i < r; i++) {
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    inv = mod_inverse(denominator, p);
    if (inv < 0) {
        return -1;
    }

    return (numerator * inv) % p;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got -1
  */

long long ncr_mod_p(long long n, long long r, long long p)
{
    long long result = 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'ni' can be reduced. [variableScope]
     */
    long long ni;
    /* Possible weaknesses found:
     *  The scope of the variable 'ri' can be reduced. [variableScope]
     */
    long long ri;
    /* Possible weaknesses found:
     *  The scope of the variable 'partial' can be reduced. [variableScope]
     */
    long long partial;

    if (p <= 1 || n < 0 || r < 0) {
        return -1;
    }

    if (r > n) {
        return 0;
    }

    while (n > 0 || r > 0) {
        ni = n % p;
        ri = r % p;

        if (ri > ni) {
            return 0;
        }

        partial = ncr_small_mod_p(ni, ri, p);
        if (partial < 0) {
            return -1;
        }

        result = (result * partial) % p;

        n /= p;
        r /= p;
    }

    return result;
}

int main(void)
{
    long long n;
    long long r;
    long long p;
    long long result;

    printf("Enter n, r, and prime p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values: n and r must be non-negative, p must be a prime greater than 1\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_p(n, r, p);
    if (result < 0) {
        fprintf(stderr, "Computation failed\n");
        return EXIT_FAILURE;
    }

    printf("nCr %% p = %lld\n", result);

    return EXIT_SUCCESS;
}
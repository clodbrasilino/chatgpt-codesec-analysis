#include <stdio.h>
#include <stdlib.h>

static long long mulmod(long long a, long long b, long long mod)
{
    unsigned __int128 res;

    a %= mod;
    b %= mod;
    res = (unsigned __int128)a * (unsigned __int128)b;
    return (long long)(res % (unsigned __int128)mod);
}

static long long power(long long base, long long exp, long long mod)
{
    long long result = 1;

    base = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            result = mulmod(result, base, mod);
        }
        base = mulmod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

static long long mod_inverse(long long a, long long p)
{
    return power(a, p - 2, p);
}

static long long ncr_small(long long n, long long r, long long p)
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
        numerator = mulmod(numerator, (n - i) % p, p);
        denominator = mulmod(denominator, (i + 1) % p, p);
    }

    if (denominator == 0) {
        return 0;
    }

    return mulmod(numerator, mod_inverse(denominator, p), p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got <no output>
  *  test case 0 failed: expected 6, got <no output>
  *  test case 1 failed: expected 25, got <no output>
  */

static long long ncr_mod_p(long long n, long long r, long long p)
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

    if (r > n) {
        return 0;
    }

    while (n > 0 || r > 0) {
        ni = n % p;
        ri = r % p;
        if (ri > ni) {
            return 0;
        }
        result = mulmod(result, ncr_small(ni, ri, p), p);
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
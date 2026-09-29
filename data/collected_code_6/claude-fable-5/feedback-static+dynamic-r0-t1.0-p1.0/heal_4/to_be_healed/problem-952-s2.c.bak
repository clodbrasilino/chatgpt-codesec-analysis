#include <stdio.h>
#include <stdlib.h>

static long long mul_mod(long long a, long long b, long long mod)
{
    return (long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)mod);
}

static long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            result = mul_mod(result, base, mod);
        }
        base = mul_mod(base, base, mod);
        exp >>= 1;
    }
    return result;
}

static long long mod_inverse(long long a, long long p)
{
    return power_mod(a, p - 2, p);
}

static long long ncr_small(long long n, long long r, long long p)
{
    long long numerator;
    long long denominator;
    long long i;

    if (r > n)
    {
        return 0;
    }
    if (r == 0 || r == n)
    {
        return 1 % p;
    }
    if (r > n - r)
    {
        r = n - r;
    }

    numerator = 1;
    denominator = 1;
    for (i = 0; i < r; i++)
    {
        numerator = mul_mod(numerator, (n - i) % p, p);
        denominator = mul_mod(denominator, (i + 1) % p, p);
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

static long long ncr_mod_p(long long n, long long r, long long p)
{
    long long result = 1;

    if (r > n)
    {
        return 0;
    }

    while (n > 0 || r > 0)
    {
        long long ni = n % p;
        long long ri = r % p;
        if (ri > ni)
        {
            return 0;
        }
        result = mul_mod(result, ncr_small(ni, ri, p), p);
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
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
    {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1)
    {
        fprintf(stderr, "Error: n and r must be non-negative, p must be a prime greater than 1\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_p(n, r, p);
    printf("C(%lld, %lld) mod %lld = %lld\n", n, r, p, result);

    return EXIT_SUCCESS;
}
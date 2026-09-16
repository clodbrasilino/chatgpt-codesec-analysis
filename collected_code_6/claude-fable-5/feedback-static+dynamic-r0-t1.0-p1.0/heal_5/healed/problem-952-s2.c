#include <stdio.h>
#include <stdlib.h>

static long long mul_mod(long long a, long long b, long long mod)
{
    return (long long)(((unsigned __int128)a * (unsigned __int128)b) % (unsigned __int128)mod);
}

static long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1 % mod;
    base = base % mod;
    if (base < 0)
    {
        base += mod;
    }
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

static int is_prime(long long p)
{
    long long i;

    if (p < 2)
    {
        return 0;
    }
    if (p % 2 == 0)
    {
        return p == 2;
    }
    for (i = 3; i <= p / i; i += 2)
    {
        if (p % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

static long long ncr_small(long long n, long long r, long long p)
{
    long long numerator;
    long long denominator;
    long long i;

    if (r < 0 || r > n)
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

    numerator = 1 % p;
    denominator = 1 % p;
    for (i = 1; i <= r; i++)
    {
        numerator = mul_mod(numerator, (n - r + i) % p, p);
        denominator = mul_mod(denominator, i % p, p);
    }

    if (denominator == 0)
    {
        return 0;
    }

    return mul_mod(numerator, mod_inverse(denominator, p), p);
}

static long long ncr_mod_p(long long n, long long r, long long p)
{
    long long result = 1 % p;

    if (r < 0 || r > n)
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

    if (!is_prime(p))
    {
        fprintf(stderr, "Error: p must be a prime number\n");
        return EXIT_FAILURE;
    }

    result = ncr_mod_p(n, r, p);
    printf("C(%lld, %lld) mod %lld = %lld\n", n, r, p, result);

    return EXIT_SUCCESS;
}
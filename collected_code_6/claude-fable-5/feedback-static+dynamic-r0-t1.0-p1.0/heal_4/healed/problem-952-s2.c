#include <stdio.h>
#include <stdlib.h>

static long long mul_mod(long long a, long long b, long long mod)
{
    long long result;

    if (mod <= 0)
    {
        return 0;
    }
    a %= mod;
    b %= mod;
    if (a < 0)
    {
        a += mod;
    }
    if (b < 0)
    {
        b += mod;
    }
    result = 0;
    while (b > 0)
    {
        if (b & 1)
        {
            result += a;
            if (result >= mod)
            {
                result -= mod;
            }
        }
        a <<= 1;
        if (a >= mod)
        {
            a -= mod;
        }
        b >>= 1;
    }
    return result;
}

static long long power_mod(long long base, long long exp, long long mod)
{
    long long result;

    if (mod <= 0)
    {
        return 0;
    }
    if (mod == 1)
    {
        return 0;
    }
    result = 1;
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
    a %= p;
    if (a < 0)
    {
        a += p;
    }
    if (a == 0)
    {
        return 0;
    }
    return power_mod(a, p - 2, p);
}

static int is_prime(long long p)
{
    long long i;

    if (p < 2)
    {
        return 0;
    }
    if (p == 2 || p == 3)
    {
        return 1;
    }
    if (p % 2 == 0 || p % 3 == 0)
    {
        return 0;
    }
    for (i = 5; i <= p / i; i += 6)
    {
        if (p % i == 0 || p % (i + 2) == 0)
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
    long long inv;
    long long i;

    if (r < 0 || n < 0)
    {
        return 0;
    }
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

    if (denominator == 0)
    {
        return 0;
    }
    inv = mod_inverse(denominator, p);
    return mul_mod(numerator, inv, p);
}

static long long ncr_mod_p(long long n, long long r, long long p)
{
    long long result;

    if (p <= 1)
    {
        return 0;
    }
    if (r < 0 || n < 0)
    {
        return 0;
    }
    if (r > n)
    {
        return 0;
    }

    result = 1 % p;
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
    printf("%lld\n", result);

    return EXIT_SUCCESS;
}
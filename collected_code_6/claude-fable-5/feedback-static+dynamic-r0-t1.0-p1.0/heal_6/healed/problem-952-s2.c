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

    numerator = 1 % p;
    denominator = 1 % p;
    for (i = 0; i < r; i++)
    {
        long long num = (n - i) % p;
        long long den = (i + 1) % p;

        numerator = mul_mod(numerator, num, p);
        denominator = mul_mod(denominator, den, p);
    }

    inv = mod_inverse(denominator, p);
    return mul_mod(numerator, inv, p);
}

static long long ncr_lucas(long long n, long long r, long long p)
{
    long long result;

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

    printf("Enter n: ");
    if (scanf("%lld", &n) != 1)
    {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    printf("Enter r: ");
    if (scanf("%lld", &r) != 1)
    {
        fprintf(stderr, "Invalid input for r\n");
        return EXIT_FAILURE;
    }

    printf("Enter prime p: ");
    if (scanf("%lld", &p) != 1)
    {
        fprintf(stderr, "Invalid input for p\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0)
    {
        fprintf(stderr, "n and r must be non-negative\n");
        return EXIT_FAILURE;
    }

    if (!is_prime(p))
    {
        fprintf(stderr, "p must be a prime number\n");
        return EXIT_FAILURE;
    }

    printf("C(%lld, %lld) mod %lld = %lld\n", n, r, p, ncr_lucas(n, r, p));

    return EXIT_SUCCESS;
}
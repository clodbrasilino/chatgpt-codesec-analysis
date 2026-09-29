#include <stdio.h>
#include <stdlib.h>

static long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1687,execs:987,op:havoc,rep:16)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:1754,execs:1027,op:havoc,rep:16)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1687,execs:987,op:havoc,rep:16)
         */
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

static long long mod_inverse(long long a, long long p)
{
    return power_mod(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 1 failed: expected 11, got 10
  */

static long long ncr_mod_p(long long n, long long r, long long p)
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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 12000000011 * 12000000010 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:1687,execs:987,op:havoc,rep:16)
         */
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    return (numerator * mod_inverse(denominator, p)) % p;
}
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000002,sig:06,src:000001,time:9927,execs:5788,op:havoc,rep:2; likely memory-safety defect
  */

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
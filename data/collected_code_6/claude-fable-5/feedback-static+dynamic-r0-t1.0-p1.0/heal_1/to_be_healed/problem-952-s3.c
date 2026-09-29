#include <stdio.h>
#include <stdlib.h>

static long long power_mod(long long base, long long exp, long long mod)
{
    long long result = 1;
    long long b = base % mod;

    if (b < 0)
    {
        b += mod;
    }

    while (exp > 0)
    {
        if ((exp & 1LL) == 1LL)
        {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 876488338465357824 * -2936065482068852736 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:4375,execs:2668,op:havoc,rep:5)
             * UBSan: signed integer overflow: 87178291200 * -8061707215783854080 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000018,time:22575,execs:13572,op:havoc,rep:1)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000016,time:36460,execs:21669,op:havoc,rep:4)
             * UBSan: signed integer overflow: -149671162192 * 1009468787432 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:19956,execs:11995,op:havoc,rep:7)
             */
            result = (result * b) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 87178291200 * 87178291200 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:19956,execs:11995,op:havoc,rep:7)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000016,time:36460,execs:21669,op:havoc,rep:4)
         * UBSan: signed integer overflow: 110075314176 * 110075314176 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:4375,execs:2668,op:havoc,rep:5)
         */
        b = (b * b) % mod;
        exp >>= 1;
    }

    return result;
}

static long long mod_inverse(long long a, long long p)
{
    return power_mod(a, p - 2, p);
}

static int ncr_mod_p(long long n, long long r, long long p, long long *out)
{
    long long numerator;
    long long denominator;
    long long i;

    if (out == NULL)
    {
        return -1;
    }

    if (n < 0 || r < 0 || p < 2)
    {
        return -1;
    }

    if (r > n)
    {
        *out = 0;
        return 0;
    }

    if (r > n - r)
    {
        r = n - r;
    }

    numerator = 1;
    denominator = 1;

    for (i = 0; i < r; i++)
    {
        long long term_num = (n - i) % p;
        long long term_den = (i + 1) % p;

        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1341847013778311040 * 180 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000018,time:22575,execs:13572,op:havoc,rep:1)
         */
        numerator = (numerator * term_num) % p;
        denominator = (denominator * term_den) % p;
    }

    if (denominator == 0)
    {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 791164053576 * -495669099672 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000000,time:19956,execs:11995,op:havoc,rep:7)
     */
    *out = (numerator * mod_inverse(denominator, p)) % p;
    return 0;
}

int main(void)
{
    long long n;
    long long r;
    long long p;
    long long result;

    printf("Enter n, r, p: ");

    if (scanf("%lld %lld %lld", &n, &r, &p) != 3)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (ncr_mod_p(n, r, p, &result) != 0)
    {
        fprintf(stderr, "Computation failed: invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("nCr mod p = %lld\n", result);
    return EXIT_SUCCESS;
}
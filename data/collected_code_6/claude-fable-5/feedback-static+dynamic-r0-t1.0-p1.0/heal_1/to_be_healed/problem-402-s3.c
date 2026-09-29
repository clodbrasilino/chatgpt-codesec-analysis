#include <stdio.h>
#include <stdlib.h>

long long power_mod(long long base, long long exp, long long mod);
long long mod_inverse(long long a, long long p);
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
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 37532802560000 * -6885542137856 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4694,execs:2816,op:havoc,rep:4)
             * UBSan: signed integer overflow: 470184984576 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:39853,execs:18539,op:havoc,rep:8)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000001,time:39853,execs:18539,op:havoc,rep:8)
         * UBSan: signed integer overflow: 37532802560000 * 37532802560000 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4694,execs:2816,op:havoc,rep:4)
         */
        base = (base * base) % mod;
        exp >>= 1LL;
    }

    return result;
}

long long mod_inverse(long long a, long long p)
{
    return power_mod(a, p - 2, p);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got -1
  */

long long ncr_mod_p(long long n, long long r, long long p)
{
    long long numerator = 1;
    long long denominator = 1;
    long long i;
    long long inv;

    if (p <= 1 || n < 0 || r < 0) {
        return -1;
    }

    if (r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = 0; i < r; i++) {
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 11081189030400 * 1000008 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000001,time:20133,execs:11437,op:havoc,rep:4)
         */
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    if (denominator == 0) {
        return -1;
    }

    inv = mod_inverse(denominator, p);
    if (inv < 0) {
        return -1;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 32560864000000 * 39622370955264 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:4694,execs:2816,op:havoc,rep:4)
     */
    return (numerator * inv) % p;
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
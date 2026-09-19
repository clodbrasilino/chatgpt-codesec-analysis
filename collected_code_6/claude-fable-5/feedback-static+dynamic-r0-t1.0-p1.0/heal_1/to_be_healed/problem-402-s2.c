#include <stdio.h>
#include <stdlib.h>

static long long power(long long base, long long exp, long long mod)
{
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 65548320768000 * 626071143540017 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000019,time:25795,execs:16282,op:havoc,rep:2)
             * UBSan: signed integer overflow: 362880 * 181883485772840960 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:26179,execs:16528,op:havoc,rep:5)
             * UBSan: signed integer overflow: 13060694016 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000015,time:23996,execs:15154,op:havoc,rep:1)
             */
            result = (result * base) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4294967296 * 4294967296 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000001,time:20337,execs:12920,op:havoc,rep:2)
         * UBSan: signed integer overflow: 626071143540017 * 626071143540017 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000019,time:25795,execs:16282,op:havoc,rep:2)
         * UBSan: signed integer overflow: 131681894400 * 131681894400 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:26179,execs:16528,op:havoc,rep:5)
         * UBSan: signed integer overflow: 2821109907456 * 2821109907456 cannot be represented in type 'long long' (AFL crash: id:000001,sig:06,src:000015,time:23996,execs:15154,op:havoc,rep:1)
         */
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
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1855286959978877040 * 1105 cannot be represented in type 'long long' (AFL crash: id:000003,sig:06,src:000003,time:26179,execs:16528,op:havoc,rep:5)
         */
        numerator = (numerator * ((n - i) % p)) % p;
        denominator = (denominator * ((i + 1) % p)) % p;
    }

    if (denominator == 0) {
        return 0;
    }

    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 980179200 * 314525029577680 cannot be represented in type 'long long' (AFL crash: id:000002,sig:06,src:000019,time:25795,execs:16282,op:havoc,rep:2)
     */
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
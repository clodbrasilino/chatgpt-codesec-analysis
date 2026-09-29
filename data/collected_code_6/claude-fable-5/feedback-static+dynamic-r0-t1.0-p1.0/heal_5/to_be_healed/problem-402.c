#include <stdio.h>
#include <stdlib.h>

static long long mulmod(long long a, long long b, long long mod)
{
    long long result = 0;
    a %= mod;
    if (a < 0) {
        a += mod;
    }
    b %= mod;
    if (b < 0) {
        b += mod;
    }
    while (b > 0) {
        if (b & 1) {
            /* Possible weaknesses found:
             * UBSan: signed integer overflow: 3294464004646478649 + 8539818392200282112 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:459,execs:256,op:havoc,rep:4)
             */
            result = (result + a) % mod;
        }
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 4611686018427387904 + 4611686018427387904 cannot be represented in type 'long long' (AFL crash: id:000000,sig:06,src:000000,time:459,execs:256,op:havoc,rep:4)
         */
        a = (a + a) % mod;
        b >>= 1;
    }
    return result;
}

long long power(long long base, long long exp, long long mod)
{
    long long result = 1 % mod;
    base %= mod;
    if (base < 0) {
        base += mod;
    }
    while (exp > 0) {
        if (exp & 1) {
            result = mulmod(result, base, mod);
        }
        exp >>= 1;
        base = mulmod(base, base, mod);
    }
    return result;
}

long long mod_inverse(long long a, long long p)
{
    return power(a, p - 2, p);
}

static long long ncr_small(long long n, long long r, long long p)
{
    if (r < 0 || r > n) {
        return 0;
    }
    if (r == 0 || r == n) {
        return 1 % p;
    }
    if (r > n - r) {
        r = n - r;
    }

    long long result = 1 % p;

    for (long long i = 0; i < r; i++) {
        result = mulmod(result, (n - i) % p, p);
        result = mulmod(result, mod_inverse((i + 1) % p, p), p);
    }

    return result;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 10, got 0
  */

long long ncr_mod_p(long long n, long long r, long long p)
{
    if (r < 0 || r > n) {
        return 0;
    }

    long long result = 1 % p;

    while (n > 0 || r > 0) {
        long long ni = n % p;
        long long ri = r % p;

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
    long long n, r, p;

    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values: require n >= 0, r >= 0, p > 1\n");
        return EXIT_FAILURE;
    }

    long long answer = ncr_mod_p(n, r, p);
    printf("%lld\n", answer);
    fflush(stdout);

    return EXIT_SUCCESS;
}
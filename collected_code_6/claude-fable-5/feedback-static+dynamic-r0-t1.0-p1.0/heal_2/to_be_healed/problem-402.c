#include <stdio.h>
#include <stdlib.h>

static long long mulmod(long long a, long long b, long long mod)
{
    return (long long)((unsigned __int128)a * (unsigned __int128)b %
                       (unsigned __int128)mod);
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

    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'numerator' and 'denominator'.
     *  Same expression used in consecutive assignments of 'numerator' and 'denominator'. [duplicateAssignExpression]
     */
    long long numerator = 1 % p;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'numerator' and 'denominator'.
     */
    long long denominator = 1 % p;

    for (long long i = 0; i < r; i++) {
        numerator = mulmod(numerator, (n - i) % p, p);
        denominator = mulmod(denominator, (i + 1) % p, p);
    }

    return mulmod(numerator, mod_inverse(denominator, p), p);
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

    printf("Enter n, r and prime p: ");
    if (scanf("%lld %lld %lld", &n, &r, &p) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n < 0 || r < 0 || p <= 1) {
        fprintf(stderr, "Invalid values: require n >= 0, r >= 0, p > 1\n");
        return EXIT_FAILURE;
    }

    long long answer = ncr_mod_p(n, r, p);
    printf("C(%lld, %lld) %% %lld = %lld\n", n, r, p, answer);

    return EXIT_SUCCESS;
}
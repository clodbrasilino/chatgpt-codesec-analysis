#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    return (a >= mod - b) ? a - (mod - b) : a + b;
}

static uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod)
{
    uint64_t result = 0;

    if (mod == 0) {
        return 0;
    }

    a %= mod;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, mod);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, mod);
        }
    }

    return result;
}

static uint64_t pow_mod(uint64_t base, uint64_t exponent, uint64_t mod)
{
    uint64_t result;

    if (mod == 0) {
        return 0;
    }

    result = UINT64_C(1) % mod;
    base %= mod;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = mul_mod(result, base, mod);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = mul_mod(base, base, mod);
        }
    }

    return result;
}

static int is_prime(uint64_t n)
{
    static const uint64_t witnesses[] = {
        UINT64_C(2), UINT64_C(325), UINT64_C(9375),
        UINT64_C(28178), UINT64_C(450775),
        UINT64_C(9780504), UINT64_C(1795265022)
    };
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    uint64_t d;
    unsigned int s = 0;
    size_t i;

    if (n < UINT64_C(2)) {
        return 0;
    }

    for (i = 0; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        if (n == small_primes[i]) {
            return 1;
        }

        if (n % small_primes[i] == 0) {
            return 0;
        }
    }

    d = n - UINT64_C(1);

    while ((d & UINT64_C(1)) == 0) {
        d >>= 1;
        ++s;
    }

    for (i = 0; i < sizeof witnesses / sizeof witnesses[0]; ++i) {
        uint64_t a = witnesses[i] % n;
        uint64_t x;
        unsigned int r;

        if (a == 0) {
            continue;
        }

        x = pow_mod(a, d, n);

        if (x == UINT64_C(1) || x == n - UINT64_C(1)) {
            continue;
        }

        for (r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);

            if (x == n - UINT64_C(1)) {
                break;
            }
        }

        if (r == s) {
            return 0;
        }
    }

    return 1;
}

static uint64_t ncr_digit_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t numerator = UINT64_C(1);
    uint64_t denominator = UINT64_C(1);
    uint64_t i;

    if (p < UINT64_C(2) || r > n) {
        return 0;
    }

    if (r > n - r) {
        r = n - r;
    }

    for (i = UINT64_C(1); i <= r; ++i) {
        numerator = mul_mod(numerator, n - r + i, p);
        denominator = mul_mod(denominator, i, p);
    }

    return mul_mod(numerator,
                   pow_mod(denominator, p - UINT64_C(2), p),
                   p);
}

static uint64_t ncr_mod_prime(uint64_t n, uint64_t r, uint64_t p)
{
    uint64_t result = UINT64_C(1);

    if (p < UINT64_C(2) || r > n) {
        return 0;
    }

    do {
        uint64_t ni = n % p;
        uint64_t ri = r % p;

        if (ri > ni) {
            return 0;
        }

        result = mul_mod(result, ncr_digit_mod_prime(ni, ri, p), p);
        n /= p;
        r /= p;
    } while (n != 0 || r != 0);

    return result;
}

int main(void)
{
    uint64_t n;
    uint64_t r;
    uint64_t p;
    uint64_t result;
    int conversion_count;

    conversion_count = scanf("%" SCNu64 " %" SCNu64 " %" SCNu64,
                             &n, &r, &p);

    if (conversion_count != 3) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!is_prime(p)) {
        fputs("p must be prime\n", stderr);
        return 1;
    }

    result = ncr_mod_prime(n, r, p);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return 1;
    }

    return 0;
}
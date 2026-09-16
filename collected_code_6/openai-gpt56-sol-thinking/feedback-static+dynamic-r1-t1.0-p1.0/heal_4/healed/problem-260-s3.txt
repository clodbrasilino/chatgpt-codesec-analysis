#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    if (a >= modulus - b) {
        return a - (modulus - b);
    }

    return a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = UINT64_C(0);

    a %= modulus;

    while (b != UINT64_C(0)) {
        if ((b & UINT64_C(1)) != UINT64_C(0)) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != UINT64_C(0)) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1);

    base %= modulus;

    while (exponent != UINT64_C(0)) {
        if ((exponent & UINT64_C(1)) != UINT64_C(0)) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1U;

        if (exponent != UINT64_C(0)) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static bool is_prime(uint64_t value)
{
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    static const uint64_t witnesses[] = {
        UINT64_C(2), UINT64_C(325), UINT64_C(9375),
        UINT64_C(28178), UINT64_C(450775), UINT64_C(9780504),
        UINT64_C(1795265022)
    };

    uint64_t d;
    unsigned int power = 0U;
    size_t i;

    if (value < UINT64_C(2)) {
        return false;
    }

    for (i = 0U; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        const uint64_t divisor = small_primes[i];

        if (value == divisor) {
            return true;
        }

        if (value % divisor == UINT64_C(0)) {
            return false;
        }
    }

    d = value - UINT64_C(1);

    while ((d & UINT64_C(1)) == UINT64_C(0)) {
        d >>= 1U;
        ++power;
    }

    for (i = 0U; i < sizeof witnesses / sizeof witnesses[0]; ++i) {
        const uint64_t base = witnesses[i] % value;
        uint64_t x;
        unsigned int round;
        bool composite = true;

        if (base == UINT64_C(0)) {
            continue;
        }

        x = power_mod(base, d, value);

        if (x == UINT64_C(1) || x == value - UINT64_C(1)) {
            continue;
        }

        for (round = 1U; round < power; ++round) {
            x = multiply_mod(x, x, value);

            if (x == value - UINT64_C(1)) {
                composite = false;
                break;
            }

            if (x == UINT64_C(1)) {
                break;
            }
        }

        if (composite) {
            return false;
        }
    }

    return true;
}

bool find_nth_newman_shanks_williams_prime(uintmax_t n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(1);
    uintmax_t found = UINTMAX_C(0);
    unsigned int index = 1U;

    if (n == UINTMAX_C(0) || result == NULL) {
        return false;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / UINT64_C(2)) {
            return false;
        }

        next = UINT64_C(2) * current + previous;
        previous = current;
        current = next;
        ++index;

        if ((index & 1U) != 0U && is_prime(current)) {
            ++found;

            if (found == n) {
                *result = current;
                return true;
            }
        }
    }
}

int main(int argc, char *const argv[])
{
    const char *cursor;
    char *end = NULL;
    uintmax_t n;
    uint64_t prime;

    if (argc != 2) {
        fputs("Usage: nsw_prime <positive integer>\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = argv[1];

    if (*cursor == '\0') {
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        if (*cursor < '0' || *cursor > '9') {
            fputs("Invalid positive integer\n", stderr);
            return EXIT_FAILURE;
        }

        ++cursor;
    }

    errno = 0;
    n = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        n == UINTMAX_C(0)) {
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_newman_shanks_williams_prime(n, &prime)) {
        fputs("The requested prime exceeds the supported 64-bit range\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", prime) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
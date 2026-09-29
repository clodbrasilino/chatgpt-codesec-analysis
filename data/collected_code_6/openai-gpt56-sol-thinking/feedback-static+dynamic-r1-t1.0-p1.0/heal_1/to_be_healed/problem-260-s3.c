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
    uint64_t result = 0U;

    a %= modulus;

    while (b != 0U) {
        if ((b & 1U) != 0U) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1U;

        if (b != 0U) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = 1U;

    base %= modulus;

    while (exponent != 0U) {
        if ((exponent & 1U) != 0U) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1U;

        if (exponent != 0U) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static bool is_prime(uint64_t value)
{
    static const uint64_t small_primes[] = {
        2U, 3U, 5U, 7U, 11U, 13U, 17U, 19U, 23U, 29U, 31U, 37U
    };
    static const uint64_t witnesses[] = {
        2U, 325U, 9375U, 28178U, 450775U, 9780504U, 1795265022U
    };
    /* Possible weaknesses found:
     *  The scope of the variable 'divisor' can be reduced. [variableScope]
     */
    uint64_t divisor;
    uint64_t d;
    unsigned int power = 0U;
    size_t i;

    if (value < 2U) {
        return false;
    }

    for (i = 0U; i < sizeof(small_primes) / sizeof(small_primes[0]); ++i) {
        divisor = small_primes[i];

        if (value == divisor) {
            return true;
        }

        if (value % divisor == 0U) {
            return false;
        }
    }

    d = value - 1U;

    while ((d & 1U) == 0U) {
        d >>= 1U;
        ++power;
    }

    for (i = 0U; i < sizeof(witnesses) / sizeof(witnesses[0]); ++i) {
        uint64_t base = witnesses[i] % value;
        uint64_t x;
        unsigned int round;
        bool composite = true;

        if (base == 0U) {
            continue;
        }

        x = power_mod(base, d, value);

        if (x == 1U || x == value - 1U) {
            continue;
        }

        for (round = 1U; round < power; ++round) {
            x = multiply_mod(x, x, value);

            if (x == value - 1U) {
                composite = false;
                break;
            }

            if (x == 1U) {
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
    uint64_t previous = 1U;
    uint64_t current = 1U;
    uintmax_t found = 0U;
    unsigned int index = 1U;

    if (n == 0U || result == NULL) {
        return false;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / 2U) {
            return false;
        }

        next = (2U * current) + previous;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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

    if (errno == ERANGE || end == argv[1] || *end != '\0' || n == 0U) {
        fputs("Invalid positive integer\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_newman_shanks_williams_prime(n, &prime)) {
        fputs("The requested prime exceeds the supported 64-bit range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", prime) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    return a >= modulus - b ? a - (modulus - b) : a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

    a %= modulus;

    while (b != 0) {
        if ((b & UINT64_C(1)) != 0) {
            result = add_mod(result, a, modulus);
        }

        b >>= 1;

        if (b != 0) {
            a = add_mod(a, a, modulus);
        }
    }

    return result;
}

static uint64_t power_mod(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = UINT64_C(1);

    base %= modulus;

    while (exponent != 0) {
        if ((exponent & UINT64_C(1)) != 0) {
            result = multiply_mod(result, base, modulus);
        }

        exponent >>= 1;

        if (exponent != 0) {
            base = multiply_mod(base, base, modulus);
        }
    }

    return result;
}

static bool is_prime(uint64_t value)
{
    static const uint32_t small_primes[] = {
        2U, 3U, 5U, 7U, 11U, 13U, 17U, 19U, 23U, 29U, 31U, 37U
    };
    static const uint64_t bases[] = {
        UINT64_C(2),
        UINT64_C(325),
        UINT64_C(9375),
        UINT64_C(28178),
        UINT64_C(450775),
        UINT64_C(9780504),
        UINT64_C(1795265022)
    };
    uint64_t odd_part;
    unsigned int power_of_two = 0;
    size_t i;

    if (value < UINT64_C(2)) {
        return false;
    }

    for (i = 0; i < sizeof(small_primes) / sizeof(small_primes[0]); ++i) {
        uint64_t prime = small_primes[i];

        if (value % prime == 0) {
            return value == prime;
        }
    }

    odd_part = value - UINT64_C(1);

    while ((odd_part & UINT64_C(1)) == 0) {
        odd_part >>= 1;
        ++power_of_two;
    }

    for (i = 0; i < sizeof(bases) / sizeof(bases[0]); ++i) {
        uint64_t base = bases[i] % value;
        uint64_t result;
        unsigned int round;
        bool probable_prime = false;

        if (base == 0) {
            continue;
        }

        result = power_mod(base, odd_part, value);

        if (result == UINT64_C(1) || result == value - UINT64_C(1)) {
            continue;
        }

        for (round = 1; round < power_of_two; ++round) {
            result = multiply_mod(result, result, value);

            if (result == value - UINT64_C(1)) {
                probable_prime = true;
                break;
            }

            if (result == UINT64_C(1)) {
                return false;
            }
        }

        if (!probable_prime) {
            return false;
        }
    }

    return true;
}

bool find_nth_newman_shanks_williams_prime(size_t n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(1);
    size_t found = 0;

    if (n == 0 || result == NULL) {
        return false;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / UINT64_C(2)) {
            return false;
        }

        next = current * UINT64_C(2) + previous;

        if (is_prime(next)) {
            ++found;

            if (found == n) {
                *result = next;
                return true;
            }
        }

        previous = current;
        current = next;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        (void)fprintf(stderr, "Usage: %s <positive-index>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        (void)fputs("Invalid index\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        (void)fputs("Invalid index\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_newman_shanks_williams_prime((size_t)parsed, &result)) {
        (void)fputs("Result exceeds the supported integer range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
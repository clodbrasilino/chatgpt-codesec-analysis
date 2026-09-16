#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    NSW_SUCCESS,
    NSW_INVALID_ARGUMENT,
    NSW_OUT_OF_RANGE
} NswStatus;

static uint64_t add_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    if (a >= modulus - b) {
        return a - (modulus - b);
    }

    return a + b;
}

static uint64_t multiply_mod(uint64_t a, uint64_t b, uint64_t modulus)
{
    uint64_t result = 0;

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
    static const uint64_t small_primes[] = {
        UINT64_C(2), UINT64_C(3), UINT64_C(5), UINT64_C(7),
        UINT64_C(11), UINT64_C(13), UINT64_C(17), UINT64_C(19),
        UINT64_C(23), UINT64_C(29), UINT64_C(31), UINT64_C(37)
    };
    static const uint64_t witnesses[] = {
        UINT64_C(2),
        UINT64_C(325),
        UINT64_C(9375),
        UINT64_C(28178),
        UINT64_C(450775),
        UINT64_C(9780504),
        UINT64_C(1795265022)
    };
    uint64_t divisor;
    uint64_t exponent;
    unsigned int power;
    size_t i;

    if (value < UINT64_C(2)) {
        return false;
    }

    for (i = 0; i < sizeof small_primes / sizeof small_primes[0]; ++i) {
        divisor = small_primes[i];

        if (value % divisor == 0) {
            return value == divisor;
        }
    }

    exponent = value - UINT64_C(1);
    power = 0;

    while ((exponent & UINT64_C(1)) == 0) {
        exponent >>= 1;
        ++power;
    }

    for (i = 0; i < sizeof witnesses / sizeof witnesses[0]; ++i) {
        uint64_t base = witnesses[i] % value;
        uint64_t result;
        unsigned int round;

        if (base == 0) {
            continue;
        }

        result = power_mod(base, exponent, value);

        if (result == UINT64_C(1) || result == value - UINT64_C(1)) {
            continue;
        }

        for (round = 1; round < power; ++round) {
            result = multiply_mod(result, result, value);

            if (result == value - UINT64_C(1)) {
                break;
            }
        }

        if (round == power) {
            return false;
        }
    }

    return true;
}

NswStatus find_nth_newman_shanks_williams_prime(size_t n, uint64_t *result)
{
    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(1);
    size_t count = 0;

    if (n == 0 || result == NULL) {
        return NSW_INVALID_ARGUMENT;
    }

    for (;;) {
        uint64_t next;

        if (current > (UINT64_MAX - previous) / UINT64_C(2)) {
            return NSW_OUT_OF_RANGE;
        }

        next = UINT64_C(2) * current + previous;
        previous = current;
        current = next;

        if (is_prime(current)) {
            ++count;

            if (count == n) {
                *result = current;
                return NSW_SUCCESS;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    uintmax_t requested;
    uint64_t result;
    char *end;
    NswStatus status;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <positive-index>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (argv[1][0] == '\0' || argv[1][0] == '-') {
        if (fprintf(stderr, "Invalid index\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    requested = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        requested == 0 || requested > SIZE_MAX) {
        if (fprintf(stderr, "Invalid index\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    status = find_nth_newman_shanks_williams_prime((size_t)requested, &result);

    if (status == NSW_OUT_OF_RANGE) {
        if (fprintf(stderr, "Result exceeds the supported integer range\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (status != NSW_SUCCESS) {
        if (fprintf(stderr, "Unable to compute the requested prime\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
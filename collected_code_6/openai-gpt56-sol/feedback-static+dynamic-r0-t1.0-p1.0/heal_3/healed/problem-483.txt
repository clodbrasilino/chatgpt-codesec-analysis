#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t exponent_in_factorial(uint64_t n, uint64_t prime)
{
    uint64_t exponent = 0;

    while (n != 0) {
        n /= prime;
        exponent += n;
    }

    return exponent;
}

static uint64_t minimum_n_for_prime_power(uint64_t prime, uint32_t exponent)
{
    uint64_t low = 1;
    uint64_t high;

    if (exponent > UINT64_MAX / prime) {
        high = UINT64_MAX;
    } else {
        high = prime * (uint64_t)exponent;
    }

    while (low < high) {
        uint64_t middle = low + (high - low) / 2;

        if (exponent_in_factorial(middle, prime) >= exponent) {
            high = middle;
        } else {
            low = middle + 1;
        }
    }

    return low;
}

static uint64_t first_factorial_divisible_by(uint64_t x)
{
    uint64_t result = 1;
    uint64_t remaining = x;

    for (uint64_t divisor = 2; divisor <= remaining / divisor; ++divisor) {
        if (remaining % divisor == 0) {
            uint32_t exponent = 0;

            do {
                remaining /= divisor;
                ++exponent;
            } while (remaining % divisor == 0);

            uint64_t candidate =
                minimum_n_for_prime_power(divisor, exponent);

            if (candidate > result) {
                result = candidate;
            }
        }
    }

    if (remaining > 1) {
        uint64_t candidate = minimum_n_for_prime_power(remaining, 1);

        if (candidate > result) {
            result = candidate;
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t parsed;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s x\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed == 0 ||
        parsed > UINT64_MAX) {
        fprintf(stderr,
                "x must be an integer in the range [1, %" PRIu64 "]\n",
                UINT64_MAX);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n",
           first_factorial_divisible_by((uint64_t)parsed));

    return EXIT_SUCCESS;
}
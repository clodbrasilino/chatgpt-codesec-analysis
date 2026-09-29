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

static uint64_t minimum_factorial_for_prime_power(uint64_t prime,
                                                   uint32_t exponent)
{
    uint64_t low = 1;
    uint64_t high;

    if (exponent == 0) {
        return 1;
    }

    if (prime > UINT64_MAX / (uint64_t)exponent) {
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
 /* Possible weaknesses found:
  *  test case 2 failed: expected 4, got 5
  */

static uint64_t first_factorial_divisible_by(uint64_t value)
{
    uint64_t result = 1;
    uint64_t remaining = value;

    if (value <= 1) {
        return 1;
    }

    for (uint64_t divisor = 2;
         divisor <= remaining / divisor;
         divisor += (divisor == 2) ? 1 : 2) {
        if (remaining % divisor == 0) {
            uint32_t exponent = 0;

            do {
                remaining /= divisor;
                ++exponent;
            } while (remaining % divisor == 0);

            uint64_t candidate =
                minimum_factorial_for_prime_power(divisor, exponent);

            if (candidate > result) {
                result = candidate;
            }
        }
    }

    if (remaining > 1) {
        uint64_t candidate =
            minimum_factorial_for_prime_power(remaining, 1);

        if (candidate > result) {
            result = candidate;
        }
    }

    return result;
}

int main(int argc, char *argv[])
{
    char *end;
    uintmax_t input;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        input == 0 ||
        input > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n",
           first_factorial_divisible_by((uint64_t)input));

    return EXIT_SUCCESS;
}
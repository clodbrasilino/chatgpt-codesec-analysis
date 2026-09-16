#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t exponent_in_factorial(uint64_t n, uint64_t prime)
{
    uint64_t exponent = 0;

    while (n >= prime) {
        n /= prime;
        exponent += n;
    }

    return exponent;
}

static uint64_t minimum_factorial_for_prime_power(uint64_t prime,
                                                   uint32_t exponent)
{
    uint64_t low = 1;
    uint64_t high = prime * (uint64_t)exponent;

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
    uint32_t exponent = 0;

    if (value <= 1) {
        return 1;
    }

    while ((remaining & UINT64_C(1)) == 0) {
        remaining >>= 1;
        ++exponent;
    }

    if (exponent != 0) {
        result = minimum_factorial_for_prime_power(UINT64_C(2), exponent);
    }

    for (uint64_t divisor = 3;
         divisor <= remaining / divisor;
         divisor += 2) {
        if (remaining % divisor == 0) {
            uint64_t candidate;

            exponent = 0;

            do {
                remaining /= divisor;
                ++exponent;
            } while (remaining % divisor == 0);

            candidate = minimum_factorial_for_prime_power(divisor, exponent);

            if (candidate > result) {
                result = candidate;
            }
        }
    }

    if (remaining > 1 && remaining > result) {
        result = remaining;
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

    if (argv[1][0] == '-' || argv[1][0] == '\0') {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        input == 0 ||
        input > UINT64_MAX) {
        fputs("Invalid positive integer.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n",
           first_factorial_divisible_by((uint64_t)input));

    return EXIT_SUCCESS;
}
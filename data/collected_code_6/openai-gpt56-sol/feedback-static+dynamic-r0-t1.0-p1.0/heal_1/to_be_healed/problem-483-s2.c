#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t exponent_in_factorial(uint64_t n, uint64_t p)
{
    uint64_t exponent = 0;

    while (n > 0) {
        n /= p;
        exponent += n;
    }

    return exponent;
}

static uint64_t minimum_n_for_prime_power(uint64_t p, uint64_t exponent)
{
    uint64_t low = 1;
    uint64_t high = p * exponent;

    while (low < high) {
        uint64_t mid = low + (high - low) / 2;

        if (exponent_in_factorial(mid, p) >= exponent) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }

    return low;
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected 4, got 5
  */

static uint64_t first_factorial_divisible_by(uint64_t x)
{
    uint64_t answer = 1;
    uint64_t remaining = x;

    for (uint64_t p = 2; p <= remaining / p; ++p) {
        if (remaining % p == 0) {
            uint64_t exponent = 0;

            do {
                remaining /= p;
                ++exponent;
            } while (remaining % p == 0);

            uint64_t candidate = minimum_n_for_prime_power(p, exponent);
            if (candidate > answer) {
                answer = candidate;
            }
        }
    }

    if (remaining > 1 && remaining > answer) {
        answer = remaining;
    }

    return answer;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        parsed == 0 || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result = first_factorial_divisible_by((uint64_t)parsed);
    printf("%" PRIu64 "\n", result);

    return EXIT_SUCCESS;
}
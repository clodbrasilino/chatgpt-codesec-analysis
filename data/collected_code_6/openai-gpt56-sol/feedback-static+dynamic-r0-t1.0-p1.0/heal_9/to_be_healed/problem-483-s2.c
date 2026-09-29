#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t exponent_in_factorial(uint64_t n, uint64_t p)
{
    uint64_t exponent = 0;

    while (n >= p) {
        n /= p;
        exponent += n;
    }

    return exponent;
}

static uint64_t minimum_n_for_prime_power(uint64_t p, uint64_t exponent)
{
    uint64_t low = 1;
    uint64_t high = p;

    while (exponent_in_factorial(high, p) < exponent) {
        if (high > UINT64_MAX / 2) {
            high = UINT64_MAX;
            break;
        }
        high *= 2;
    }

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
    if (x == 1) {
        return 1;
    }

    uint64_t answer = 1;
    uint64_t remaining = x;

    for (uint64_t p = 2; p <= remaining / p;) {
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

        if (p == 2) {
            p = 3;
        } else {
            p += 2;
        }
    }

    if (remaining > 1 && remaining > answer) {
        answer = remaining;
    }

    return answer;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <positive integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE ||
        end == argv[1] ||
        *end != '\0' ||
        argv[1][0] == '-' ||
        parsed == 0 ||
        parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid positive integer\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n",
           first_factorial_divisible_by((uint64_t)parsed));

    return EXIT_SUCCESS;
}
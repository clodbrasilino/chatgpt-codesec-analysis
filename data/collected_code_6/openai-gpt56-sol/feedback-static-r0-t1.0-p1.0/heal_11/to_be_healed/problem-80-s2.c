#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_uint64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int tetrahedral_number(uint64_t n, uint64_t *result)
{
    uint64_t factors[3];

    if (result == NULL || n > UINT64_MAX - UINT64_C(2)) {
        return 0;
    }

    factors[0] = n;
    factors[1] = n + UINT64_C(1);
    factors[2] = n + UINT64_C(2);

    for (uint64_t divisor = UINT64_C(2);
         divisor <= UINT64_C(3);
         ++divisor) {
        uint64_t remaining = divisor;

        for (size_t i = 0; i < sizeof factors / sizeof factors[0]; ++i) {
            uint64_t common;

            if (remaining == UINT64_C(1)) {
                break;
            }

            common = gcd_uint64(factors[i], remaining);
            factors[i] /= common;
            remaining /= common;
        }

        if (remaining != UINT64_C(1)) {
            return 0;
        }
    }

    if (factors[0] != 0 &&
        factors[1] > UINT64_MAX / factors[0]) {
        return 0;
    }

    uint64_t partial = factors[0] * factors[1];

    if (factors[2] != 0 &&
        partial > UINT64_MAX / factors[2]) {
        return 0;
    }

    *result = partial * factors[2];
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    const char *input;
    char *end;
    uintmax_t parsed;
    uint64_t result;

    if (argc != 2) {
        fputs("Usage: program n\n", stderr);
        return EXIT_FAILURE;
    }

    input = argv[1];

    if (input == NULL || input[0] == '\0' || input[0] == '-') {
        fputs("Invalid nonnegative integer\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE ||
        end == input ||
        end == NULL ||
        *end != '\0' ||
        parsed > UINT64_MAX) {
        fputs("Invalid nonnegative integer\n", stderr);
        return EXIT_FAILURE;
    }

    result = 0;

    if (!tetrahedral_number((uint64_t)parsed, &result)) {
        fputs("Result is outside the uint64_t range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
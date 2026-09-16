#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int delannoy_number(unsigned int n, uint64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    uint64_t previous = UINT64_C(1);
    uint64_t current = UINT64_C(3);

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (unsigned int k = 1U; k < n; ++k) {
        const uint64_t k64 = (uint64_t)k;
        const uint64_t multiplier = UINT64_C(2) * k64 + UINT64_C(1);

        if (current > UINT64_MAX / multiplier ||
            previous > UINT64_MAX / k64) {
            return 0;
        }

        const uint64_t left = multiplier * current;
        const uint64_t right = k64 * previous;

        if (left < right) {
            return 0;
        }

        const uint64_t numerator = left - right;
        const uint64_t divisor = k64 + UINT64_C(1);

        if (numerator % divisor != UINT64_C(0)) {
            return 0;
        }

        previous = current;
        current = numerator / divisor;
    }

    *result = current;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    const unsigned long parsed = strtoul(argv[1], &end, 10);

    if (errno != 0 ||
        end == argv[1] ||
        *end != '\0' ||
        parsed > UINT_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result = UINT64_C(0);

    if (!delannoy_number((unsigned int)parsed, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
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

    uint64_t previous = 1;
    uint64_t current = 3;

    if (n == 0U) {
        *result = previous;
        return 1;
    }

    for (unsigned int k = 1U; k < n; ++k) {
        uint64_t multiplier = 2U * (uint64_t)k + 1U;

        if (current > UINT64_MAX / multiplier ||
            previous > UINT64_MAX / k) {
            return 0;
        }

        uint64_t first_term = multiplier * current;
        uint64_t second_term = (uint64_t)k * previous;

        if (first_term < second_term) {
            return 0;
        }

        uint64_t numerator = first_term - second_term;
        uint64_t divisor = (uint64_t)k + 1U;

        if (numerator % divisor != 0U) {
            return 0;
        }

        uint64_t next = numerator / divisor;
        previous = current;
        current = next;
    }

    *result = current;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    char *end = NULL;
    unsigned long parsed = strtoul(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || parsed > UINT_MAX) {
        fprintf(stderr, "Invalid nonnegative integer\n");
        return EXIT_FAILURE;
    }

    uint64_t result;

    if (!delannoy_number((unsigned int)parsed, &result)) {
        fprintf(stderr, "Result exceeds uint64_t range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
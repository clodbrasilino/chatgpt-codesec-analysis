#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int rectangular_number(uint64_t n, uint64_t *result)
{
    if (result == NULL || n == UINT64_MAX) {
        return 0;
    }

    if ((n & 1U) == 0U) {
        const uint64_t half = n / 2U;

        if (half != 0U && n + 1U > UINT64_MAX / half) {
            return 0;
        }

        *result = half * (n + 1U);
    } else {
        const uint64_t half = (n + 1U) / 2U;

        if (n != 0U && half > UINT64_MAX / n) {
            return 0;
        }

        *result = n * half;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t input;
    uint64_t result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <nonnegative integer>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtoumax(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || input > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!rectangular_number((uint64_t)input, &result)) {
        fprintf(stderr, "Result is out of range\n");
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
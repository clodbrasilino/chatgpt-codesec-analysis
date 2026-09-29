#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    if (result == NULL || n > 92681U) {
        return 0;
    }

    uint64_t sum = n * (n + 1U) / 2U;
    uint64_t sum_of_squares = n * (n + 1U) * (2U * n + 1U) / 6U;

    *result = sum * sum - sum_of_squares;
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *end = NULL;
    uintmax_t parsed = strtoumax(argv[1], &end, 10);

    if (argv[1][0] == '\0' || end == NULL || *end != '\0' || parsed > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t result = 0U;

    if (!calculate_difference((uint64_t)parsed, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
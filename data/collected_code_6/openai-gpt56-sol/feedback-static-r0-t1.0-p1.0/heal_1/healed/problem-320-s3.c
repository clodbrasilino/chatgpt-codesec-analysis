#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    uint64_t sum;
    uint64_t sum_of_squares;

    if (result == NULL || n > UINT64_C(77935)) {
        return 0;
    }

    sum = n * (n + UINT64_C(1)) / UINT64_C(2);
    sum_of_squares =
        n * (n + UINT64_C(1)) * (UINT64_C(2) * n + UINT64_C(1)) /
        UINT64_C(6);

    *result = sum * sum - sum_of_squares;
    return 1;
}

int main(void)
{
    char input[128];
    char *end;
    uintmax_t value;
    uint64_t difference;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT64_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference((uint64_t)value, &difference)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
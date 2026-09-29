#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        uint64_t value;
        uint64_t power;

        if (i > UINT64_MAX / UINT64_C(2)) {
            return 0;
        }

        value = i * UINT64_C(2);
        power = value;

        for (unsigned int exponent = 1; exponent < 5; ++exponent) {
            if (power > UINT64_MAX / value) {
                return 0;
            }

            power *= value;
        }

        if (sum > UINT64_MAX - power) {
            return 0;
        }

        sum += power;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t parsed;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_even((uint64_t)parsed, &result)) {
        free(input);
        fputs("Arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}
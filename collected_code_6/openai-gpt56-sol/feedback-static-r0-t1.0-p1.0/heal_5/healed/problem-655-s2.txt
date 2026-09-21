#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_fifth_powers(uint64_t n, uint64_t *result)
{
    const uint64_t maximum_n = 1388;
    __uint128_t sum = 0;

    if (result == NULL || n > maximum_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        __uint128_t value = i;
        sum += value * value * value * value * value;
    }

    if (sum > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)sum;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    uintmax_t value;
    uint64_t result;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 || input[length - 1] != '\n') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' || end[1] != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sum_of_fifth_powers((uint64_t)value, &result) != 0) {
        free(input);
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
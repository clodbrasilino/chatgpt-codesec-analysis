#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers(uint64_t n, uint64_t *result)
{
    __uint128_t value;
    __uint128_t square;

    if (result == NULL) {
        return -1;
    }

    value = (__uint128_t)n * ((__uint128_t)n + 1);
    square = 2 * (__uint128_t)n * n + 2 * (__uint128_t)n - 1;
    value = value * square / 12;

    if (value > UINT64_MAX) {
        return -1;
    }

    *result = (uint64_t)value;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t parsed;
    uint64_t sum;

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
    parsed = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (sum_fifth_powers((uint64_t)parsed, &sum) != 0) {
        fputs("Result out of range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
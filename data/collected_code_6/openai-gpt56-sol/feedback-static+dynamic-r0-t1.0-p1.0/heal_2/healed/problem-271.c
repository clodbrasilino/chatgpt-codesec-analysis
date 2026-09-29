#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_fifth_powers_even(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(9103);
    __uint128_t sum = 0;

    if (result == NULL || n > max_n) {
        return -1;
    }

    for (uint64_t i = 1; i <= n; ++i) {
        const __uint128_t value = (__uint128_t)2 * i;
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
    uintmax_t parsed;
    uint64_t sum;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (sum_fifth_powers_even((uint64_t)parsed, &sum) != 0) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
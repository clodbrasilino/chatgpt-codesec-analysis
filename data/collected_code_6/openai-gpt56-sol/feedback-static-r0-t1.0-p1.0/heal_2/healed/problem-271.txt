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
        const __uint128_t square = value * value;
        sum += square * square * value;
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
    char *start;
    char *number_end;
    uintmax_t value;
    uint64_t sum;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(start, &number_end, 10);

    if (errno == ERANGE || number_end == start || value > UINT64_MAX) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*number_end)) {
        ++number_end;
    }

    if (*number_end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (sum_fifth_powers_even((uint64_t)value, &sum) != 0) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int sum_fourth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return -1;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth_power;

        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return -1;
        }

        odd = UINT64_C(2) * i + UINT64_C(1);

        if (odd > UINT64_MAX / odd) {
            return -1;
        }

        square = odd * odd;

        if (square > UINT64_MAX / square) {
            return -1;
        }

        fourth_power = square * square;

        if (sum > UINT64_MAX - fourth_power) {
            return -1;
        }

        sum += fourth_power;
    }

    *result = sum;
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

    if (sum_fourth_powers_of_odds((uint64_t)value, &sum) != 0) {
        fputs("Result exceeds the supported integer range\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
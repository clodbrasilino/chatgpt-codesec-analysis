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

static int read_value(uint64_t *result)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    uintmax_t value;

    if (result == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *result = (uint64_t)value;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t difference;

    if (!read_value(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(value, &difference)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
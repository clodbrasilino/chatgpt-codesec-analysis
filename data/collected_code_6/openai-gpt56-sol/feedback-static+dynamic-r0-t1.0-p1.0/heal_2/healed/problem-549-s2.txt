#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int multiply_uint64(uint64_t a, uint64_t b, uint64_t *result)
{
    if (result == NULL || (a != 0 && b > UINT64_MAX / a)) {
        return 0;
    }

    *result = a * b;
    return 1;
}

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd;
        uint64_t square;
        uint64_t fourth;
        uint64_t fifth;

        if (i > (UINT64_MAX - UINT64_C(1)) / UINT64_C(2)) {
            return 0;
        }

        odd = UINT64_C(2) * i + UINT64_C(1);

        if (!multiply_uint64(odd, odd, &square) ||
            !multiply_uint64(square, square, &fourth) ||
            !multiply_uint64(fourth, odd, &fifth)) {
            return 0;
        }

        if (fifth > UINT64_MAX - sum) {
            return 0;
        }

        sum += fifth;
    }

    *result = sum;
    return 1;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    if (length > 0 && line[length - 1] != '\n' && !feof(stdin)) {
        free(line);
        return 0;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (!read_uint64(&n)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_fifth_powers_of_odds(n, &sum)) {
        fputs("Result exceeds the supported range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", sum);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_size_value(size_t *value)
{
    int character;
    size_t result = 0;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return 0;
        }
    } while (character == ' ' || character == '\t' ||
             character == '\n' || character == '\r' ||
             character == '\f' || character == '\v');

    if (character == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character < '0' || character > '9') {
        return 0;
    }

    do {
        size_t digit = (size_t)(character - '0');

        if (result > (SIZE_MAX - digit) / 10) {
            return 0;
        }

        result = result * 10 + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (ferror(stdin)) {
            return 0;
        }
    } else if (character != ' ' && character != '\t' &&
               character != '\n' && character != '\r' &&
               character != '\f' && character != '\v') {
        return 0;
    }

    *value = result;
    return 1;
}

static int read_int64_value(int64_t *value)
{
    int character;
    int negative = 0;
    uint64_t result = 0;
    uint64_t limit;

    if (value == NULL) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character == EOF) {
            return 0;
        }
    } while (character == ' ' || character == '\t' ||
             character == '\n' || character == '\r' ||
             character == '\f' || character == '\v');

    if (character == '-' || character == '+') {
        negative = character == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character < '0' || character > '9') {
        return 0;
    }

    limit = negative
                ? (uint64_t)INT64_MAX + UINT64_C(1)
                : (uint64_t)INT64_MAX;

    do {
        uint64_t digit = (uint64_t)(character - '0');

        if (result > (limit - digit) / UINT64_C(10)) {
            return 0;
        }

        result = result * UINT64_C(10) + digit;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character >= '0' && character <= '9');

    if (character == EOF) {
        if (ferror(stdin)) {
            return 0;
        }
    } else if (character != ' ' && character != '\t' &&
               character != '\n' && character != '\r' &&
               character != '\f' && character != '\v') {
        return 0;
    }

    if (negative) {
        if (result == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)result;
        }
    } else {
        *value = (int64_t)result;
    }

    return 1;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

static int find_minimum_tuple_difference(const Tuple *tuples,
                                         size_t count,
                                         uint64_t *minimum)
{
    uint64_t result;

    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    result = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < result) {
            result = difference;
        }
    }

    *minimum = result;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    uint64_t minimum;

    if (!read_size_value(&count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64_value(&tuples[i].first) ||
            !read_int64_value(&tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_tuple_difference(tuples, count, &minimum)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
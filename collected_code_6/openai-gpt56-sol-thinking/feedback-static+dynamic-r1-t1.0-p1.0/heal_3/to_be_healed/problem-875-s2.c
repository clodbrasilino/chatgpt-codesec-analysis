#include <ctype.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool read_nonspace(int *character)
{
    if (character == NULL) {
        return false;
    }

    int current;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        current = fgetc(stdin);
    } while (current != EOF && isspace((unsigned char)current));

    if (current == EOF) {
        return false;
    }

    *character = current;
    return true;
}

static bool read_size(size_t *value)
{
    if (value == NULL) {
        return false;
    }

    int character;

    if (!read_nonspace(&character) || character == '-') {
        return false;
    }

    if (character == '+') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    size_t result = 0;
    bool has_digit = false;

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character < '0' || character > '9') {
            return false;
        }

        size_t digit = (size_t)(character - '0');

        if (result > (SIZE_MAX - digit) / 10) {
            return false;
        }

        result = result * 10 + digit;
        has_digit = true;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    if (!has_digit) {
        return false;
    }

    *value = result;
    return true;
}

static bool read_int64(int64_t *value)
{
    if (value == NULL) {
        return false;
    }

    int character;

    if (!read_nonspace(&character)) {
        return false;
    }

    bool negative = false;

    if (character == '-' || character == '+') {
        negative = character == '-';
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    uint64_t limit = negative
        ? (uint64_t)INT64_MAX + UINT64_C(1)
        : (uint64_t)INT64_MAX;
    uint64_t magnitude = 0;
    bool has_digit = false;

    while (character != EOF &&
           !isspace((unsigned char)character)) {
        if (character < '0' || character > '9') {
            return false;
        }

        uint64_t digit = (uint64_t)(character - '0');

        if (magnitude > (limit - digit) / UINT64_C(10)) {
            return false;
        }

        magnitude = magnitude * UINT64_C(10) + digit;
        has_digit = true;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return false;
    }

    if (!has_digit) {
        return false;
    }

    if (negative) {
        if (magnitude == (uint64_t)INT64_MAX + UINT64_C(1)) {
            *value = INT64_MIN;
        } else {
            *value = -(int64_t)magnitude;
        }
    } else {
        *value = (int64_t)magnitude;
    }

    return true;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    if (first >= second) {
        return (uint64_t)first - (uint64_t)second;
    }

    return (uint64_t)second - (uint64_t)first;
}

static bool find_minimum_tuple_difference(
    const Tuple *tuples,
    size_t count,
    uint64_t *minimum_difference)
{
    if (tuples == NULL || count == 0 || minimum_difference == NULL) {
        return false;
    }

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *minimum_difference = minimum;
    return true;
}

int main(void)
{
    size_t count;

    if (!read_size(&count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));

    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(&tuples[i].first) ||
            !read_int64(&tuples[i].second)) {
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    uint64_t minimum_difference;

    if (!find_minimum_tuple_difference(
            tuples, count, &minimum_difference)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
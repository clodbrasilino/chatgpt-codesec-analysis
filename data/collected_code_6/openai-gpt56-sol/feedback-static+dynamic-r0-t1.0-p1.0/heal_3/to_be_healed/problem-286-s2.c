#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <ctype.h>
#include <errno.h>

static int64_t max_i64(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int checked_add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL ||
        (b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_positive_i64_u64(int64_t value, uint64_t multiplier,
                                        int64_t *result)
{
    if (result == NULL || value < 0 ||
        multiplier > (uint64_t)INT64_MAX ||
        (value != 0 && multiplier > (uint64_t)INT64_MAX / (uint64_t)value)) {
        return 0;
    }

    *result = value * (int64_t)multiplier;
    return 1;
}

static int read_token(char **token)
{
    char *buffer;
    size_t capacity = 32;
    size_t length = 0;
    int c;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    } while (c != EOF && isspace((unsigned char)c));

    if (c == EOF) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while (c != EOF && !isspace((unsigned char)c)) {
        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        c = fgetc(stdin);
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int parse_uintmax_token(uintmax_t *value)
{
    char *buffer;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' || buffer[0] == '-' || buffer[0] == '+') {
        free(buffer);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0') {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = parsed;
    return 1;
}

static int read_size_value(size_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax_token(&parsed) ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_u64_value(uint64_t *value)
{
    uintmax_t parsed;

    if (value == NULL || !parse_uintmax_token(&parsed) ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int read_i64_value(int64_t *value)
{
    char *buffer;
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    free(buffer);
    *value = (int64_t)parsed;
    return 1;
}

static int only_trailing_whitespace(void)
{
    int c;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)c)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

static int maximum_repeated_subarray_sum(const int64_t *array, size_t length,
                                         uint64_t repetitions,
                                         int64_t *result)
{
    int64_t total = 0;
    int64_t prefix = 0;
    int64_t best_prefix = INT64_MIN;
    int64_t suffix = 0;
    int64_t best_suffix = INT64_MIN;
    int64_t current;
    int64_t best;
    int64_t bridge;

    if (array == NULL || result == NULL || length == 0 || repetitions == 0) {
        return 0;
    }

    current = array[0];
    best = array[0];

    for (size_t i = 0; i < length; ++i) {
        int64_t extended;

        if (!checked_add_i64(total, array[i], &total) ||
            !checked_add_i64(prefix, array[i], &prefix)) {
            return 0;
        }

        best_prefix = max_i64(best_prefix, prefix);

        if (i > 0) {
            if (!checked_add_i64(current, array[i], &extended)) {
                return 0;
            }

            current = max_i64(array[i], extended);
            best = max_i64(best, current);
        }
    }

    for (size_t i = length; i-- > 0;) {
        if (!checked_add_i64(suffix, array[i], &suffix)) {
            return 0;
        }

        best_suffix = max_i64(best_suffix, suffix);
    }

    if (repetitions == 1) {
        *result = best;
        return 1;
    }

    if (!checked_add_i64(best_suffix, best_prefix, &bridge)) {
        return 0;
    }

    if (total > 0 && repetitions > 2) {
        int64_t middle;

        if (!checked_mul_positive_i64_u64(total, repetitions - 2, &middle) ||
            !checked_add_i64(bridge, middle, &bridge)) {
            return 0;
        }
    }

    *result = max_i64(best, bridge);
    return 1;
}

int main(void)
{
    size_t length;
    uint64_t repetitions;
    int64_t *array;
    int64_t result;

    if (!read_size_value(&length) ||
        !read_u64_value(&repetitions) ||
        length == 0 ||
        repetitions == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_i64_value(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!only_trailing_whitespace()) {
        fputs("Invalid input\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (!maximum_repeated_subarray_sum(array, length, repetitions, &result)) {
        fputs("Unable to compute result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}
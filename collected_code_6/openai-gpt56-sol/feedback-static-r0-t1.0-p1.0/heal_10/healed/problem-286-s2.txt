#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 4096U

static int64_t max_i64(int64_t a, int64_t b)
{
    return a > b ? a : b;
}

static int checked_add_i64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static int checked_mul_nonnegative_i64_u64(int64_t value,
                                           uint64_t multiplier,
                                           int64_t *result)
{
    if (result == NULL || value < 0) {
        return 0;
    }

    if (value == 0 || multiplier == 0) {
        *result = 0;
        return 1;
    }

    if (multiplier > (uint64_t)INT64_MAX ||
        value > INT64_MAX / (int64_t)multiplier) {
        return 0;
    }

    *result = value * (int64_t)multiplier;
    return 1;
}

static int maximum_repeated_subarray_sum(const int64_t *array,
                                         size_t length,
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

    for (size_t i = length; i > 0; --i) {
        if (!checked_add_i64(suffix, array[i - 1], &suffix)) {
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

        if (!checked_mul_nonnegative_i64_u64(total, repetitions - 2, &middle) ||
            !checked_add_i64(bridge, middle, &bridge)) {
            return 0;
        }
    }

    *result = max_i64(best, bridge);
    return 1;
}

static int read_token(FILE *stream, char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        return 0;
    }

    buffer[0] = '\0';

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF) {
            return 0;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    for (;;) {
        if (length >= capacity - 1) {
            while ((ch = fgetc(stream)) != EOF &&
                   !isspace((unsigned char)ch)) {
            }

            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;

        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) {
                buffer[0] = '\0';
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_u64(const char *text, uint64_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int parse_i64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        isspace((unsigned char)text[0])) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < (intmax_t)INT64_MIN || parsed > (intmax_t)INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    const size_t token_capacity = (size_t)MAX_TOKEN_LENGTH + 1U;
    char *token = NULL;
    int64_t *array = NULL;
    size_t length = 0;
    uint64_t repetitions = 0;
    int64_t result;
    int status = EXIT_FAILURE;

    token = malloc(token_capacity);
    if (token == NULL) {
        perror("malloc");
        goto cleanup;
    }

    if (!read_token(stdin, token, token_capacity) ||
        !parse_size(token, &length)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (!read_token(stdin, token, token_capacity) ||
        !parse_u64(token, &repetitions) ||
        length == 0 ||
        repetitions == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        perror("malloc");
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_token(stdin, token, token_capacity) ||
            !parse_i64(token, &array[i])) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (!maximum_repeated_subarray_sum(array, length, repetitions, &result)) {
        fputs("Unable to compute result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        perror("printf");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    free(token);
    return status;
}
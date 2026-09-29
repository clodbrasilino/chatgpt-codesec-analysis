#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

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

        if (i != 0) {
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

static int discard_token_remainder(int ch)
{
    while (ch != EOF && !isspace((unsigned char)ch)) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    return ch == EOF && ferror(stdin) ? 0 : 1;
}

static int read_token(char *buffer, size_t capacity)
{
    size_t length = 0;
    int ch;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= capacity - 1) {
            buffer[0] = '\0';
            if (!discard_token_remainder(ch)) {
                return 0;
            }
            return 0;
        }

        buffer[length++] = (char)ch;
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        buffer[0] = '\0';
        return 0;
    }

    buffer[length] = '\0';
    return 1;
}

static int parse_size(const char *text, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || isspace((unsigned char)*text)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_u64(const char *text, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        *text == '-' || isspace((unsigned char)*text)) {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    return 1;
}

static int parse_i64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' ||
        isspace((unsigned char)*text)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(void)
{
    enum { TOKEN_CAPACITY = 128 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char token[TOKEN_CAPACITY];
    size_t length;
    uint64_t repetitions;
    int64_t *array = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_token(token, sizeof(token)) ||
        !parse_size(token, &length) ||
        !read_token(token, sizeof(token)) ||
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
        if (!read_token(token, sizeof(token)) ||
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
    return status;
}
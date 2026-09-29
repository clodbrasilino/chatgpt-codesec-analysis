#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int parse_size(const char *text, size_t *value)
{
    char *end;
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

static int parse_i64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || text[0] == '\0' ||
        isspace((unsigned char)text[0])) {
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

static int read_token(FILE *stream, char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (stream == NULL || token == NULL) {
        return 0;
    }

    *token = NULL;

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            return 0;
        }
    } while (isspace((unsigned char)ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int add_i64(int64_t a, int64_t b, int64_t *result)
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

static int max_sum_no_three_consecutive(const int64_t *values,
                                        size_t count,
                                        int64_t *result)
{
    int64_t previous[3] = {0, 0, 0};
    int64_t current[3];

    if (result == NULL || (values == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        current[0] = previous[0];

        if (previous[1] > current[0]) {
            current[0] = previous[1];
        }

        if (previous[2] > current[0]) {
            current[0] = previous[2];
        }

        if (!add_i64(previous[0], values[i], &current[1]) ||
            !add_i64(previous[1], values[i], &current[2])) {
            return 0;
        }

        previous[0] = current[0];
        previous[1] = current[1];
        previous[2] = current[2];
    }

    *result = previous[0];

    if (previous[1] > *result) {
        *result = previous[1];
    }

    if (previous[2] > *result) {
        *result = previous[2];
    }

    return 1;
}

int main(void)
{
    char *token = NULL;
    size_t count;
    int64_t *values = NULL;
    int64_t result;
    int status = EXIT_FAILURE;

    if (!read_token(stdin, &token) || !parse_size(token, &count)) {
        fputs("Invalid element count\n", stderr);
        goto cleanup;
    }

    free(token);
    token = NULL;

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        goto cleanup;
    }

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(stdin, &token) ||
            !parse_i64(token, &values[i])) {
            fputs("Invalid element\n", stderr);
            goto cleanup;
        }

        free(token);
        token = NULL;
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to calculate the result\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(token);
    free(values);
    return status;
}
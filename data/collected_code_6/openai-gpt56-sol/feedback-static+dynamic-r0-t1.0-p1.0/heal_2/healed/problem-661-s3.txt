#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int parse_size(const char *text, size_t *value)
{
    char *end = NULL;
    uintmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0' || *text == '-') {
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
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
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

static int read_token(char *buffer, size_t size)
{
    int ch;
    size_t length = 0;
    int truncated = 0;

    if (buffer == NULL || size < 2) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length < size - 1) {
            buffer[length++] = (char)ch;
        } else {
            truncated = 1;
        }

        ch = fgetc(stdin);
    }

    buffer[length] = '\0';

    if (ferror(stdin)) {
        return 0;
    }

    return !truncated;
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
    size_t count;
    int64_t *values = NULL;
    int64_t result;
    char *token = malloc(128);

    if (token == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    if (!read_token(token, 128) || !parse_size(token, &count)) {
        fputs("Invalid element count\n", stderr);
        free(token);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input is too large\n", stderr);
        free(token);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            perror("malloc");
            free(token);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(token, 128) || !parse_i64(token, &values[i])) {
            fputs("Invalid element\n", stderr);
            free(values);
            free(token);
            return EXIT_FAILURE;
        }
    }

    if (!max_sum_no_three_consecutive(values, count, &result)) {
        fputs("Unable to calculate the result\n", stderr);
        free(values);
        free(token);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(values);
        free(token);
        return EXIT_FAILURE;
    }

    free(values);
    free(token);
    return EXIT_SUCCESS;
}
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int32_t first;
    int32_t second;
} Tuple;

enum {
    TOKEN_CAPACITY = 64
};

static bool read_token(char **output)
{
    char *buffer;
    size_t length = 0;
    bool too_long = false;
    int ch;

    if (output == NULL) {
        return false;
    }

    *output = NULL;

    buffer = malloc(TOKEN_CAPACITY);
    if (buffer == NULL) {
        return false;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        free(buffer);
        return false;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length < TOKEN_CAPACITY - 1) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
    }

    if (ferror(stdin) || too_long) {
        free(buffer);
        return false;
    }

    buffer[length] = '\0';
    *output = buffer;
    return true;
}

static bool read_size_value(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    if (buffer[0] == '-') {
        free(buffer);
        return false;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed <= SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(buffer);
    return valid;
}

static bool read_int32_value(int32_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    bool valid;

    if (value == NULL || !read_token(&buffer)) {
        return false;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= INT32_MIN &&
            parsed <= INT32_MAX;

    if (valid) {
        *value = (int32_t)parsed;
    }

    free(buffer);
    return valid;
}

static bool find_maximum_product(const Tuple *tuples, size_t count,
                                 int64_t *maximum)
{
    if (tuples == NULL || maximum == NULL || count == 0) {
        return false;
    }

    *maximum = (int64_t)tuples[0].first * (int64_t)tuples[0].second;

    for (size_t i = 1; i < count; ++i) {
        int64_t product =
            (int64_t)tuples[i].first * (int64_t)tuples[i].second;

        if (product > *maximum) {
            *maximum = product;
        }
    }

    return true;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    int64_t maximum;

    if (!read_size_value(&count) ||
        count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32_value(&tuples[i].first) ||
            !read_int32_value(&tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_maximum_product(tuples, count, &maximum)) {
        fputs("Unable to find maximum product\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", maximum) < 0) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);
    return EXIT_SUCCESS;
}
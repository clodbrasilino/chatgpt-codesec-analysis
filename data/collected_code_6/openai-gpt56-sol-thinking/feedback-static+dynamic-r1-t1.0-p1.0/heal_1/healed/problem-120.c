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

static bool read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    bool too_long = false;

    if (buffer == NULL || capacity < 2) {
        return false;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return false;
    }

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            too_long = true;
        }

        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    if (too_long) {
        return false;
    }

    buffer[length] = '\0';
    return true;
}

static bool read_count(size_t *count)
{
    char token[128];
    char *end;
    uintmax_t value;

    if (count == NULL || !read_token(token, sizeof(token)) || token[0] == '-') {
        return false;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        value == 0 || value > SIZE_MAX) {
        return false;
    }

    *count = (size_t)value;
    return true;
}

static bool read_int32(int32_t *value)
{
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(token, sizeof(token))) {
        return false;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT32_MIN || parsed > INT32_MAX) {
        return false;
    }

    *value = (int32_t)parsed;
    return true;
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

    if (!read_count(&count) || count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int32(&tuples[i].first) ||
            !read_int32(&tuples[i].second)) {
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
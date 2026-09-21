#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <ctype.h>
#include <errno.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_token(char *buffer, size_t capacity)
{
    int character;
    size_t length = 0;
    int valid = 1;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        character = fgetc(stdin);
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return 0;
    }

    while (character != EOF && !isspace((unsigned char)character)) {
        if (character == '\0') {
            valid = 0;
        } else if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            valid = 0;
        }

        character = fgetc(stdin);
    }

    if (character == EOF && ferror(stdin)) {
        return 0;
    }

    buffer[length] = '\0';
    return valid && length != 0;
}

static int read_size(size_t *value)
{
    char buffer[64];
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer)) ||
        buffer[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(int64_t *value)
{
    char buffer[64];
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || !read_token(buffer, sizeof(buffer))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
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
    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    uint64_t result =
        absolute_difference(tuples[0].first, tuples[0].second);

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
    uint64_t minimum;
    Tuple *tuples;

    if (!read_size(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
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
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int read_token(FILE *stream, char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;
    int valid = 1;

    if (stream == NULL || buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = fgetc(stream);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (ch == '\0') {
            valid = 0;
        } else if (length + 1 < capacity) {
            buffer[length++] = (char)ch;
        } else {
            valid = 0;
        }

        ch = fgetc(stream);
    } while (ch != EOF && !isspace((unsigned char)ch));

    buffer[length] = '\0';
    return valid;
}

static int read_size(FILE *stream, size_t *value)
{
    char token[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token))) {
        return 0;
    }

    if (token[0] == '\0' || token[0] == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' || parsed > SIZE_MAX) {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(FILE *stream, int64_t *value)
{
    char token[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || !read_token(stream, token, sizeof(token))) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    return a >= b
        ? (uint64_t)a - (uint64_t)b
        : (uint64_t)b - (uint64_t)a;
}

static int find_minimum_pair_difference(const Tuple *tuples, size_t count,
                                        uint64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    *minimum = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < *minimum) {
            *minimum = difference;
        }
    }

    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples;
    uint64_t minimum;

    if (!read_size(stdin, &count) || count == 0) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_int64(stdin, &tuples[i].first) ||
            !read_int64(stdin, &tuples[i].second)) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (!find_minimum_pair_difference(tuples, count, &minimum)) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", minimum);
    free(tuples);

    return EXIT_SUCCESS;
}
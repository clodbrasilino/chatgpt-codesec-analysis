#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    return a >= b ? (uint64_t)a - (uint64_t)b
                  : (uint64_t)b - (uint64_t)a;
}

static int find_minimum_difference(const Tuple *tuples, size_t count,
                                   uint64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0U) {
        return -1;
    }

    *minimum = absolute_difference(tuples[0].first, tuples[0].second);

    for (size_t i = 1U; i < count; ++i) {
        uint64_t current =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (current < *minimum) {
            *minimum = current;
        }
    }

    return 0;
}

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0U;
    int overflow = 0;

    if (buffer == NULL || capacity < 2U) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
        if (ch == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)ch));

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length + 1U < capacity) {
            buffer[length++] = (char)ch;
        } else {
            overflow = 1;
        }

        ch = fgetc(stdin);
    }

    if (ch == EOF && ferror(stdin)) {
        return -1;
    }

    buffer[length] = '\0';
    return overflow ? -1 : 0;
}

static int read_size(size_t *value)
{
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0 ||
        buffer[0] == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed > SIZE_MAX) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value)
{
    char buffer[128];
    char *end;
    intmax_t parsed;

    if (value == NULL || read_token(buffer, sizeof(buffer)) != 0) {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    uint64_t minimum;
    int result = EXIT_FAILURE;

    if (read_size(&count) != 0 || count == 0U ||
        count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_int64(&tuples[i].first) != 0 ||
            read_int64(&tuples[i].second) != 0) {
            goto cleanup;
        }
    }

    if (find_minimum_difference(tuples, count, &minimum) != 0) {
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", minimum) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return result;
}
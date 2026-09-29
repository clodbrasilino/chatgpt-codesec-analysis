#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static bool read_token(char *buffer, size_t capacity)
{
    if (buffer == NULL || capacity < 2) {
        return false;
    }

    int character;

    do {
        character = getchar();
    } while (character != EOF && isspace((unsigned char)character));

    if (character == EOF) {
        return false;
    }

    size_t length = 0;
    bool valid = true;

    do {
        if (length + 1 < capacity) {
            buffer[length++] = (char)character;
        } else {
            valid = false;
        }

        character = getchar();
    } while (character != EOF && !isspace((unsigned char)character));

    buffer[length] = '\0';
    return valid;
}

static bool read_size(size_t *value)
{
    if (value == NULL) {
        return false;
    }

    char token[sizeof(uintmax_t) * CHAR_BIT + 3];

    if (!read_token(token, sizeof(token)) || token[0] == '-') {
        return false;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed > SIZE_MAX) {
        return false;
    }

    *value = (size_t)parsed;
    return true;
}

static bool read_int64(int64_t *value)
{
    if (value == NULL) {
        return false;
    }

    char token[sizeof(uintmax_t) * CHAR_BIT + 3];

    if (!read_token(token, sizeof(token))) {
        return false;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return false;
    }

    *value = (int64_t)parsed;
    return true;
}

static uint64_t absolute_difference(int64_t first, int64_t second)
{
    return first >= second
        ? (uint64_t)first - (uint64_t)second
        : (uint64_t)second - (uint64_t)first;
}

static bool find_minimum_tuple_difference(
    const Tuple *tuples,
    size_t count,
    uint64_t *minimum_difference)
{
    if (tuples == NULL || count == 0 || minimum_difference == NULL) {
        return false;
    }

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference =
            absolute_difference(tuples[i].first, tuples[i].second);

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *minimum_difference = minimum;
    return true;
}

int main(void)
{
    size_t count;

    if (!read_size(&count) || count == 0 ||
        count > SIZE_MAX / sizeof(Tuple)) {
        return EXIT_FAILURE;
    }

    Tuple *tuples = malloc(count * sizeof(*tuples));

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

    uint64_t minimum_difference;

    if (!find_minimum_tuple_difference(
            tuples, count, &minimum_difference)) {
        free(tuples);
        return EXIT_FAILURE;
    }

    free(tuples);

    if (printf("%" PRIu64 "\n", minimum_difference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
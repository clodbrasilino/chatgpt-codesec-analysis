#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static uint64_t absolute_difference(int64_t a, int64_t b)
{
    return a >= b
        ? (uint64_t)a - (uint64_t)b
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

static int discard_line(void)
{
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == EOF && ferror(stdin) ? -1 : 0;
}

static int read_line(char *buffer, size_t size)
{
    size_t length;

    if (buffer == NULL || size < 2U || size > (size_t)INT_MAX) {
        return -1;
    }

    if (fgets(buffer, (int)size, stdin) == NULL) {
        return -1;
    }

    length = strlen(buffer);

    if (length > 0U && buffer[length - 1U] == '\n') {
        buffer[length - 1U] = '\0';
        return 0;
    }

    if (feof(stdin)) {
        return 0;
    }

    if (discard_line() != 0) {
        return -1;
    }

    return -1;
}

static int only_whitespace(const char *text)
{
    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (!isspace((unsigned char)*text)) {
            return 0;
        }
        ++text;
    }

    return 1;
}

static int parse_count(const char *text, size_t *count)
{
    char *end;
    uintmax_t value;

    if (text == NULL || count == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    if (*text == '\0' || *text == '-' || *text == '+') {
        return -1;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (end == text || errno == ERANGE || value == 0U ||
        value > SIZE_MAX || !only_whitespace(end)) {
        return -1;
    }

    *count = (size_t)value;
    return 0;
}

static int parse_tuple(const char *text, Tuple *tuple)
{
    char *end;
    intmax_t first;
    intmax_t second;

    if (text == NULL || tuple == NULL) {
        return -1;
    }

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    errno = 0;
    first = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE ||
        first < INT64_MIN || first > INT64_MAX) {
        return -1;
    }

    text = end;

    while (isspace((unsigned char)*text)) {
        ++text;
    }

    errno = 0;
    second = strtoimax(text, &end, 10);

    if (end == text || errno == ERANGE ||
        second < INT64_MIN || second > INT64_MAX ||
        !only_whitespace(end)) {
        return -1;
    }

    tuple->first = (int64_t)first;
    tuple->second = (int64_t)second;
    return 0;
}

int main(void)
{
    char line[256];
    size_t count;
    Tuple *tuples = NULL;
    uint64_t minimum;
    int result = EXIT_FAILURE;

    if (read_line(line, sizeof line) != 0 ||
        parse_count(line, &count) != 0 ||
        count > SIZE_MAX / sizeof(*tuples)) {
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (read_line(line, sizeof line) != 0 ||
            parse_tuple(line, &tuples[i]) != 0) {
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
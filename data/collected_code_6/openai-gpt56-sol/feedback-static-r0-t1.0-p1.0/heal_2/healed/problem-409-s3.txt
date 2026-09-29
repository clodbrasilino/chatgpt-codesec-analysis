#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t first;
    int64_t second;
} Tuple;

static int multiply_checked(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((a == -1 && b == INT64_MIN) ||
        (b == -1 && a == INT64_MIN)) {
        return 0;
    }

    if (a > 0) {
        if ((b > 0 && a > INT64_MAX / b) ||
            (b < 0 && b < INT64_MIN / a)) {
            return 0;
        }
    } else if (a < 0) {
        if ((b > 0 && a < INT64_MIN / b) ||
            (b < 0 && a < INT64_MAX / b)) {
            return 0;
        }
    }

    *result = a * b;
    return 1;
}

static int minimum_tuple_product(const Tuple *tuples, size_t count,
                                 int64_t *minimum)
{
    if (tuples == NULL || minimum == NULL || count == 0) {
        return 0;
    }

    if (!multiply_checked(tuples[0].first, tuples[0].second, minimum)) {
        return 0;
    }

    for (size_t i = 1; i < count; ++i) {
        int64_t product;

        if (!multiply_checked(tuples[i].first, tuples[i].second, &product)) {
            return 0;
        }

        if (product < *minimum) {
            *minimum = product;
        }
    }

    return 1;
}

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return 0;
    }

    for (size_t i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            return 1;
        }
    }

    if (feof(stdin)) {
        return 1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return 0;
}

static int parse_count(const char *line, size_t *count)
{
    char *end;
    uintmax_t value;

    if (line == NULL || count == NULL) {
        return 0;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value == 0 ||
        value > SIZE_MAX / sizeof(Tuple)) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *count = (size_t)value;
    return 1;
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *cursor = end;
    return 1;
}

static int parse_tuple(const char *line, Tuple *tuple)
{
    const char *cursor = line;

    if (line == NULL || tuple == NULL ||
        !parse_int64(&cursor, &tuple->first) ||
        !parse_int64(&cursor, &tuple->second)) {
        return 0;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\r' || *cursor == '\n' ||
           *cursor == '\v' || *cursor == '\f') {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    char line[256];
    size_t count;
    Tuple *tuples = NULL;
    int64_t minimum;
    int status = EXIT_FAILURE;

    if (!read_line(line, sizeof(line)) || !parse_count(line, &count)) {
        fprintf(stderr, "Invalid tuple count\n");
        return EXIT_FAILURE;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed: errno=%d\n", errno);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_line(line, sizeof(line)) ||
            !parse_tuple(line, &tuples[i])) {
            fprintf(stderr, "Invalid tuple input\n");
            goto cleanup;
        }
    }

    if (!minimum_tuple_product(tuples, count, &minimum)) {
        fprintf(stderr, "Unable to calculate product safely\n");
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        fprintf(stderr, "Output error\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(tuples);
    return status;
}
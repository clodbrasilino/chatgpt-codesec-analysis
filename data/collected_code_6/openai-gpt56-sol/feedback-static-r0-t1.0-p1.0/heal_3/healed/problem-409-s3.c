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

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *new_line = malloc(initial_capacity);

        if (new_line == NULL) {
            return 0;
        }

        free(*line);
        *line = new_line;
        *capacity = initial_capacity;
    }

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            (*line)[length] = '\0';
            return 1;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ferror(stdin) || length == 0) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' ||
           ch == '\n' || ch == '\v' || ch == '\f';
}

static int parse_count(const char *line, size_t *count)
{
    const char *cursor;
    char *end;
    uintmax_t value;

    if (line == NULL || count == NULL) {
        return 0;
    }

    cursor = line;
    while (is_space_character(*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        return 0;
    }

    errno = 0;
    value = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || value == 0 ||
        value > SIZE_MAX / sizeof(Tuple)) {
        return 0;
    }

    while (is_space_character(*end)) {
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

    while (is_space_character(**cursor)) {
        ++*cursor;
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

    while (is_space_character(*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    char *line = NULL;
    size_t line_capacity = 0;
    size_t count;
    Tuple *tuples = NULL;
    int64_t minimum;
    int status = EXIT_FAILURE;

    if (!read_line(&line, &line_capacity) ||
        !parse_count(line, &count)) {
        fprintf(stderr, "Invalid tuple count\n");
        goto cleanup;
    }

    tuples = malloc(count * sizeof(*tuples));
    if (tuples == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_line(&line, &line_capacity) ||
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
    free(line);
    return status;
}
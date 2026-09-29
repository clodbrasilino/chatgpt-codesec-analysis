#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        const size_t initial_capacity = 128;
        char *buffer = malloc(initial_capacity);

        if (buffer == NULL) {
            return -1;
        }

        free(*line);
        *line = buffer;
        *capacity = initial_capacity;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF || ch == '\n') {
            break;
        }

        if (length >= *capacity - 1) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0)) {
        return -1;
    }

    (*line)[length] = '\0';
    return 0;
}

static int has_valid_ending(const char *end)
{
    if (end == NULL) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    return *end == '\0';
}

static int read_size(size_t *value, char **line, size_t *capacity)
{
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    if (read_line(line, capacity) != 0) {
        return -1;
    }

    start = *line;
    while (*start == ' ' || *start == '\t' || *start == '\r') {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX / sizeof(int64_t) ||
        !has_valid_ending(end)) {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

static int read_int64(int64_t *value, char **line, size_t *capacity)
{
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    if (read_line(line, capacity) != 0) {
        return -1;
    }

    start = *line;
    while (*start == ' ' || *start == '\t' || *start == '\r') {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !has_valid_ending(end)) {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int find_operations(int64_t *values, size_t count,
                           uint64_t *operations)
{
    int64_t median;
    uint64_t total = 0;

    if (values == NULL || operations == NULL || count == 0) {
        return -1;
    }

    qsort(values, count, sizeof(*values), compare_int64);
    median = values[count / 2];

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference;

        if (values[i] >= median) {
            difference = (uint64_t)values[i] - (uint64_t)median;
        } else {
            difference = (uint64_t)median - (uint64_t)values[i];
        }

        if (total > UINT64_MAX - difference) {
            return -1;
        }

        total += difference;
    }

    *operations = total;
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t count;
    uint64_t operations;
    int64_t *values;

    if (read_size(&count, &line, &capacity) != 0) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    values = malloc(count * sizeof(*values));
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_int64(&values[i], &line, &capacity) != 0) {
            fputs("Invalid input\n", stderr);
            free(values);
            free(line);
            return EXIT_FAILURE;
        }
    }

    free(line);

    if (find_operations(values, count, &operations) != 0) {
        fputs("Unable to calculate operations\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", operations) < 0) {
        fputs("Output error\n", stderr);
        free(values);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}
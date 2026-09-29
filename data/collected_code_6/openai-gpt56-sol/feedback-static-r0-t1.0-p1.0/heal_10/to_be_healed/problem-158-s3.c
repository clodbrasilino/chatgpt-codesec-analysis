#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <stddef.h>
#include <errno.h>
#include <ctype.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        char *buffer = malloc(128);

        if (buffer == NULL) {
            return -1;
        }

        free(*line);
        *line = buffer;
        *capacity = 128;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == *capacity - 1) {
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

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return 0;
}

static int parse_int64(const char *line, int64_t *value)
{
    const char *start;
    char *end;
    intmax_t parsed;

    if (line == NULL || value == NULL) {
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (int64_t)parsed;
    return 0;
}

static int parse_count(const char *line, size_t *count)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (line == NULL || count == NULL) {
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || parsed == 0 ||
        parsed > SIZE_MAX / sizeof(int64_t)) {
        return -1;
    }

    *count = (size_t)parsed;
    return 0;
}

static uint64_t absolute_difference(int64_t lhs, int64_t rhs)
{
    uint64_t a = (uint64_t)lhs;
    uint64_t b = (uint64_t)rhs;

    return lhs >= rhs ? a - b : b - a;
}

static int find_operations(int64_t *values, size_t count,
                           uint64_t *operations)
{
    uint64_t total = 0;
    int64_t target;

    if (values == NULL || operations == NULL || count == 0) {
        return -1;
    }

    qsort(values, count, sizeof *values, compare_int64);
    target = values[count / 2];

    for (size_t i = 0; i < count; ++i) {
        uint64_t difference = absolute_difference(values[i], target);

        if (difference > UINT64_MAX - total) {
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
    int64_t *values = NULL;
    uint64_t operations;
    int status = EXIT_FAILURE;

    if (read_line(stdin, &line, &capacity) != 0 ||
        parse_count(line, &count) != 0) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    values = malloc(count * sizeof *values);
    if (values == NULL) {
        fputs("Memory allocation failed\n", stderr);
        goto cleanup;
    }

    for (size_t i = 0; i < count; ++i) {
        if (read_line(stdin, &line, &capacity) != 0 ||
            parse_int64(line, &values[i]) != 0) {
            fputs("Invalid input\n", stderr);
            goto cleanup;
        }
    }

    if (find_operations(values, count, &operations) != 0) {
        fputs("Unable to calculate operations\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIu64 "\n", operations) < 0) {
        fputs("Output error\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(values);
    free(line);
    return status;
}
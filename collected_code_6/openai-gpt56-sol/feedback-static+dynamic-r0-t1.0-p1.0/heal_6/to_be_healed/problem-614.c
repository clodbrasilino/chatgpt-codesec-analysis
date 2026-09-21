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

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;
    int ch;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return 0;
        }
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF) {
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

        if (ch == '\n') {
            break;
        }
    }

    if (length == 0 && ch == EOF) {
        return 0;
    }

    (*line)[length] = '\0';
    return 1;
}

static void skip_space(const char **cursor)
{
    while (**cursor != '\0' &&
           isspace((unsigned char)**cursor)) {
        ++*cursor;
    }
}

static int read_size(size_t *value, char **line, size_t *capacity)
{
    const char *cursor;
    char *end;
    uintmax_t parsed;

    if (value == NULL || !read_line(line, capacity)) {
        return 0;
    }

    cursor = *line;
    skip_space(&cursor);

    if (*cursor == '\0' || *cursor == '-' || *cursor == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE || parsed > SIZE_MAX) {
        return 0;
    }

    cursor = end;
    skip_space(&cursor);

    if (*cursor != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int parse_int64(const char **cursor, int64_t *value)
{
    char *end;
    intmax_t parsed;

    skip_space(cursor);

    if (**cursor == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (int64_t)parsed;
    return 1;
}

static int read_tuple(Tuple *tuple, char **line, size_t *capacity)
{
    const char *cursor;
    int64_t first;
    int64_t second;

    if (tuple == NULL || !read_line(line, capacity)) {
        return 0;
    }

    cursor = *line;

    if (!parse_int64(&cursor, &first) ||
        !parse_int64(&cursor, &second)) {
        return 0;
    }

    skip_space(&cursor);

    if (*cursor != '\0') {
        return 0;
    }

    tuple->first = first;
    tuple->second = second;
    return 1;
}

static int add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return 0;
    }

    *result = left + right;
    return 1;
}

static int cumulative_sum(const Tuple *tuples, size_t count, int64_t *result)
{
    int64_t sum = 0;

    if (result == NULL || (tuples == NULL && count != 0)) {
        return 0;
    }

    for (size_t i = 0; i < count; ++i) {
        if (!add_int64(sum, tuples[i].first, &sum) ||
            !add_int64(sum, tuples[i].second, &sum)) {
            return 0;
        }
    }

    *result = sum;
    return 1;
}

int main(void)
{
    size_t count;
    Tuple *tuples = NULL;
    char *line = NULL;
    size_t capacity = 0;
    int64_t sum;
    int status = EXIT_FAILURE;

    if (!read_size(&count, &line, &capacity)) {
        goto cleanup;
    }

    if (count > SIZE_MAX / sizeof(*tuples)) {
        goto cleanup;
    }

    if (count != 0) {
        tuples = malloc(count * sizeof(*tuples));
        if (tuples == NULL) {
            goto cleanup;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_tuple(&tuples[i], &line, &capacity)) {
            goto cleanup;
        }
    }

    if (!cumulative_sum(tuples, count, &sum)) {
        goto cleanup;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(line);
    free(tuples);
    return status;
}
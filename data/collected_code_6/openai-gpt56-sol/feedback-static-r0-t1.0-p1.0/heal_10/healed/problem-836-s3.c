#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(FILE *stream, char **line, size_t *capacity)
{
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity < 2) {
        char *buffer = malloc(64);

        if (buffer == NULL) {
            return 0;
        }

        free(*line);
        *line = buffer;
        *capacity = 64;
    }

    for (;;) {
        if (length + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2) {
                if (length > SIZE_MAX - 2) {
                    return 0;
                }

                size_t required = length + 2;
                char *buffer = realloc(*line, required);

                if (buffer == NULL) {
                    return 0;
                }

                *line = buffer;
                *capacity = required;
            } else {
                size_t new_capacity = *capacity * 2;
                char *buffer = realloc(*line, new_capacity);

                if (buffer == NULL) {
                    return 0;
                }

                *line = buffer;
                *capacity = new_capacity;
            }
        }

        int ch = getc(stream);

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        (*line)[length++] = (char)(unsigned char)ch;
    }

    if (length > 0 && (*line)[length - 1] == '\r') {
        --length;
    }

    (*line)[length] = '\0';
    return 1;
}

static int read_size(FILE *stream, char **line, size_t *capacity,
                     size_t *value)
{
    if (value == NULL || !read_line(stream, line, capacity)) {
        return 0;
    }

    char *cursor = *line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-' || *cursor == '\0') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor || parsed > SIZE_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

static int read_int64(FILE *stream, char **line, size_t *capacity,
                      int64_t *value)
{
    if (value == NULL || !read_line(stream, line, capacity)) {
        return 0;
    }

    char *cursor = *line;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

static int add_int64(int64_t a, int64_t b, int64_t *result)
{
    if (result == NULL) {
        return 0;
    }

    if ((b > 0 && a > INT64_MAX - b) ||
        (b < 0 && a < INT64_MIN - b)) {
        return 0;
    }

    *result = a + b;
    return 1;
}

static size_t max_sum_subarray_length(const int64_t *array, size_t length)
{
    if (array == NULL || length == 0) {
        return 0;
    }

    int64_t current_sum = array[0];
    int64_t maximum_sum = array[0];
    size_t current_start = 0;
    size_t best_length = 1;

    for (size_t i = 1; i < length; ++i) {
        int64_t extended_sum;

        if (current_sum < 0) {
            current_sum = array[i];
            current_start = i;
        } else if (!add_int64(current_sum, array[i], &extended_sum)) {
            if (array[i] > 0) {
                current_sum = INT64_MAX;
            } else {
                current_sum = array[i];
                current_start = i;
            }
        } else {
            current_sum = extended_sum;
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum && current_length > best_length)) {
            maximum_sum = current_sum;
            best_length = current_length;
        }
    }

    return best_length;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int64_t *array = NULL;
    int status = EXIT_FAILURE;

    if (!read_size(stdin, &line, &capacity, &length) ||
        length == 0 ||
        length > SIZE_MAX / sizeof(*array)) {
        goto cleanup;
    }

    array = malloc(length * sizeof(*array));

    if (array == NULL) {
        goto cleanup;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(stdin, &line, &capacity, &array[i])) {
            goto cleanup;
        }
    }

    size_t result = max_sum_subarray_length(array, length);

    if (printf("%zu\n", result) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(array);
    free(line);
    return status;
}
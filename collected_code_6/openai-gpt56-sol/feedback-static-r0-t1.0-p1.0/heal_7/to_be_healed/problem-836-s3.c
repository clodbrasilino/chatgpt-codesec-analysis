#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return 0;
    }

    if (*line == NULL || *capacity == 0) {
        *capacity = 64;
        *line = malloc(*capacity);
        if (*line == NULL) {
            return 0;
        }
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length + 1 >= *capacity) {
            if (*capacity > SIZE_MAX / 2) {
                return 0;
            }

            size_t new_capacity = *capacity * 2;
            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return 0;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 1;
}

static int read_size(char **line, size_t *capacity, size_t *value)
{
    if (value == NULL || !read_line(line, capacity)) {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    uintmax_t parsed = strtoumax(*line, &end, 10);

    if (errno == ERANGE || end == *line || parsed > SIZE_MAX) {
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

static int read_int64(char **line, size_t *capacity, int64_t *value)
{
    if (value == NULL || !read_line(line, capacity)) {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    intmax_t parsed = strtoimax(*line, &end, 10);

    if (errno == ERANGE || end == *line ||
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

static int add_overflows_int64(int64_t a, int64_t b)
{
    return (b > 0 && a > INT64_MAX - b) ||
           (b < 0 && a < INT64_MIN - b);
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
        if (current_sum < 0 ||
            add_overflows_int64(current_sum, array[i])) {
            current_sum = array[i];
            current_start = i;
        } else {
            current_sum += array[i];
        }

        size_t current_length = i - current_start + 1;

        if (current_sum > maximum_sum ||
            (current_sum == maximum_sum &&
             current_length > best_length)) {
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

    if (!read_size(&line, &capacity, &length) ||
        length == 0 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        free(line);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof *array);
    if (array == NULL) {
        free(line);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&line, &capacity, &array[i])) {
            free(array);
            free(line);
            return EXIT_FAILURE;
        }
    }

    size_t result = max_sum_subarray_length(array, length);

    free(array);
    free(line);

    if (printf("%zu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
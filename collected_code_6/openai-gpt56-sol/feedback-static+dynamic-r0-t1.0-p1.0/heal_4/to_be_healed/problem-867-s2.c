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
    int ch;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2U) {
        char *new_line;
        size_t new_capacity = 64U;

        new_line = realloc(*line, new_capacity);
        if (new_line == NULL) {
            return -1;
        }

        *line = new_line;
        *capacity = new_capacity;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            return -1;
        }

        if (length + 1U >= *capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF) {
        if (ferror(stdin) || length == 0U) {
            return -1;
        }
    }

    (*line)[length] = '\0';
    return 0;
}

static int only_trailing_whitespace(const char *text)
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

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    size_t capacity = 0U;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX ||
        !only_trailing_whitespace(end)) {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    size_t capacity = 0U;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX ||
        !only_trailing_whitespace(end)) {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int minimum_number_to_make_sum_even(
    const int64_t array[],
    size_t length,
    int64_t *result)
{
    unsigned int parity = 0U;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        parity ^= (unsigned int)((uint64_t)array[i] & UINT64_C(1));
    }

    *result = (int64_t)parity;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t minimum;

    if (read_size(&length) != 0) {
        fputs("Invalid array length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0U) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Memory allocation failed.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element.\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (minimum_number_to_make_sum_even(array, length, &minimum) != 0) {
        fputs("Unable to compute the result.\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", minimum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
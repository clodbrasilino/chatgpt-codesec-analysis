#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define MAX_INPUT_LINE 4096U
#define MAX_ARRAY_LENGTH 1000000U

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n') {
        if (ch == EOF) {
            return ferror(stdin) ? -1 : 0;
        }
    }

    return 0;
}

static int read_line(char **buffer)
{
    char *line;
    char *newline;
    size_t capacity = (size_t)MAX_INPUT_LINE + 2U;
    size_t length;

    if (buffer == NULL || capacity > (size_t)INT_MAX) {
        return -1;
    }

    *buffer = NULL;

    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    if (fgets(line, (int)capacity, stdin) == NULL) {
        free(line);
        return -1;
    }

    newline = strchr(line, '\n');
    if (newline != NULL) {
        *newline = '\0';
        *buffer = line;
        return 0;
    }

    length = strlen(line);

    if (length > (size_t)MAX_INPUT_LINE) {
        if (discard_line() != 0) {
            free(line);
            return -1;
        }

        free(line);
        return -1;
    }

    if (feof(stdin)) {
        *buffer = line;
        return 0;
    }

    if (discard_line() != 0) {
        free(line);
        return -1;
    }

    free(line);
    return -1;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    intmax_t parsed;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (int64_t)parsed;
    free(line);
    return 0;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL || read_line(&line) != 0) {
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX || parsed > MAX_ARRAY_LENGTH) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = (size_t)parsed;
    free(line);
    return 0;
}

static int checked_add_int64(int64_t left, int64_t right, int64_t *result)
{
    if (result == NULL) {
        return -1;
    }

    if ((right > 0 && left > INT64_MAX - right) ||
        (right < 0 && left < INT64_MIN - right)) {
        return -1;
    }

    *result = left + right;
    return 0;
}

static int max_increasing_subsequence_sum(const int64_t *array,
                                          size_t length,
                                          int64_t *result)
{
    int64_t *sums;
    int64_t maximum;

    if (array == NULL || result == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*sums)) {
        return -1;
    }

    sums = malloc(length * sizeof(*sums));
    if (sums == NULL) {
        return -1;
    }

    maximum = array[0];

    for (size_t i = 0; i < length; ++i) {
        sums[i] = array[i];

        for (size_t j = 0; j < i; ++j) {
            int64_t candidate;

            if (array[j] >= array[i]) {
                continue;
            }

            if (checked_add_int64(sums[j], array[i], &candidate) != 0) {
                free(sums);
                return -1;
            }

            if (candidate > sums[i]) {
                sums[i] = candidate;
            }
        }

        if (sums[i] > maximum) {
            maximum = sums[i];
        }
    }

    free(sums);
    *result = maximum;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t result;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Unable to allocate array\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (max_increasing_subsequence_sum(array, length, &result) != 0) {
        fputs("Unable to compute the result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", result) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
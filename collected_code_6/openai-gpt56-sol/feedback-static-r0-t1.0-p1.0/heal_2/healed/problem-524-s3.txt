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

    if (*line == NULL || *capacity == 0) {
        *capacity = 128;
        *line = malloc(*capacity);
        if (*line == NULL) {
            *capacity = 0;
            return -1;
        }
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length == SIZE_MAX - 1) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;

            if (*capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = *capacity * 2;
            }

            if (new_capacity <= length + 1) {
                return -1;
            }

            char *new_line = realloc(*line, new_capacity);
            if (new_line == NULL) {
                return -1;
            }

            *line = new_line;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        return -1;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
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

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (int64_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
}

static int read_size(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
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

    if (*start == '\0' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed == 0 || parsed > SIZE_MAX) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = (size_t)parsed;
    status = 0;

cleanup:
    free(line);
    return status;
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

            if ((array[i] > 0 && sums[j] > INT64_MAX - array[i]) ||
                (array[i] < 0 && sums[j] < INT64_MIN - array[i])) {
                free(sums);
                return -1;
            }

            candidate = sums[j] + array[i];
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
        fprintf(stderr, "Invalid array length\n");
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fprintf(stderr, "Array is too large\n");
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fprintf(stderr, "Invalid array element\n");
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (max_increasing_subsequence_sum(array, length, &result) != 0) {
        fprintf(stderr, "Unable to compute the result\n");
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    free(array);
    return EXIT_SUCCESS;
}
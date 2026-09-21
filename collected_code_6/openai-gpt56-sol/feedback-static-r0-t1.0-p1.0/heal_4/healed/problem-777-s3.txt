#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_line(char **line, size_t *capacity)
{
    size_t length = 0;

    if (line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        char *new_line = malloc(128);

        if (new_line == NULL) {
            return -1;
        }

        free(*line);
        *line = new_line;
        *capacity = 128;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                return -1;
            }
            break;
        }

        if (length > SIZE_MAX - 2) {
            return -1;
        }

        if (length + 1 >= *capacity) {
            size_t new_capacity;
            char *new_line;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            if (new_capacity <= length + 1) {
                new_capacity = length + 2;
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

    (*line)[length] = '\0';
    return 0;
}

static int only_whitespace(const char *text)
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
    char *end = NULL;
    size_t capacity = 0;
    uintmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (errno != ERANGE &&
        end != line &&
        parsed != 0 &&
        parsed <= SIZE_MAX / sizeof(int64_t) &&
        only_whitespace(end)) {
        *value = (size_t)parsed;
        status = 0;
    }

    free(line);
    return status;
}

static int read_int64(int64_t *value)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    intmax_t parsed;
    int status = -1;

    if (value == NULL || read_line(&line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(line, &end, 10);

    if (errno != ERANGE &&
        end != line &&
        parsed >= INT64_MIN &&
        parsed <= INT64_MAX &&
        only_whitespace(end)) {
        *value = (int64_t)parsed;
        status = 0;
    }

    free(line);
    return status;
}

static int sum_non_repeated(const int64_t *array, size_t length, int64_t *sum)
{
    int64_t *copy;
    int64_t result = 0;
    size_t i = 0;

    if (array == NULL || sum == NULL || length == 0 ||
        length > SIZE_MAX / sizeof(*copy)) {
        return -1;
    }

    copy = malloc(length * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    memcpy(copy, array, length * sizeof(*copy));
    qsort(copy, length, sizeof(*copy), compare_int64);

    while (i < length) {
        size_t j = i + 1;

        while (j < length && copy[j] == copy[i]) {
            ++j;
        }

        if (j == i + 1) {
            if ((copy[i] > 0 && result > INT64_MAX - copy[i]) ||
                (copy[i] < 0 && result < INT64_MIN - copy[i])) {
                free(copy);
                return -1;
            }

            result += copy[i];
        }

        i = j;
    }

    free(copy);
    *sum = result;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t sum;

    if (read_size(&length) != 0) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof(*array));
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_int64(&array[i]) != 0) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (sum_non_repeated(array, length, &sum) != 0) {
        fputs("Unable to calculate sum\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    if (printf("%" PRId64 "\n", sum) < 0) {
        free(array);
        return EXIT_FAILURE;
    }

    free(array);
    return EXIT_SUCCESS;
}
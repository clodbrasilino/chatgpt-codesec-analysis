#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <stddef.h>
#include <limits.h>

static int compare_int64(const void *lhs, const void *rhs)
{
    const int64_t a = *(const int64_t *)lhs;
    const int64_t b = *(const int64_t *)rhs;

    return (a > b) - (a < b);
}

static int read_token(char **token)
{
    size_t length = 0;
    size_t capacity = 32;
    char *buffer;
    int c;

    if (token == NULL) {
        return -1;
    }

    *token = NULL;

    do {
        c = fgetc(stdin);
        if (c == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)c));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        if (isspace((unsigned char)c)) {
            break;
        }

        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)c;

        c = fgetc(stdin);
        if (c == EOF) {
            if (ferror(stdin)) {
                free(buffer);
                return -1;
            }
            break;
        }
    }

    buffer[length] = '\0';
    *token = buffer;
    return 0;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0' || buffer[0] == '+' || buffer[0] == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed == 0 || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;

    if (value == NULL || read_token(&buffer) != 0) {
        return -1;
    }

    if (buffer[0] == '\0') {
        free(buffer);
        return -1;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    if (errno == ERANGE || end == buffer || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int sum_non_repeated(int64_t *array, size_t length, int64_t *sum)
{
    int64_t result = 0;
    size_t i = 0;

    if (array == NULL || sum == NULL || length == 0) {
        return -1;
    }

    qsort(array, length, sizeof(*array), compare_int64);

    while (i < length) {
        size_t j = i + 1;

        while (j < length && array[j] == array[i]) {
            ++j;
        }

        if (j == i + 1) {
            if ((array[i] > 0 && result > INT64_MAX - array[i]) ||
                (array[i] < 0 && result < INT64_MIN - array[i])) {
                return -1;
            }

            result += array[i];
        }

        i = j;
    }

    *sum = result;
    return 0;
}

int main(void)
{
    size_t length;
    int64_t *array;
    int64_t sum;

    if (read_size(&length) != 0 ||
        length > SIZE_MAX / sizeof(*array)) {
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
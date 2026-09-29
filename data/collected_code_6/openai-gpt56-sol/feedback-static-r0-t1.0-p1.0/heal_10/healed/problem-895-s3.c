#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int checked_add_int64(int64_t a, int64_t b, int64_t *result)
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

static int max_non_adjacent_sum(const int64_t array[], size_t length,
                                int64_t *result)
{
    int64_t include = 0;
    int64_t exclude = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        int64_t next_include;
        int64_t next_exclude;

        if (!checked_add_int64(exclude, array[i], &next_include)) {
            return 0;
        }

        next_exclude = include > exclude ? include : exclude;
        include = next_include;
        exclude = next_exclude;
    }

    *result = include > exclude ? include : exclude;
    return 1;
}

static int grow_buffer(char **buffer, size_t *capacity)
{
    size_t new_capacity;
    char *new_buffer;

    if (buffer == NULL || capacity == NULL || *buffer == NULL ||
        *capacity == 0) {
        return 0;
    }

    if (*capacity > SIZE_MAX / 2) {
        return 0;
    }

    new_capacity = *capacity * 2;
    new_buffer = realloc(*buffer, new_capacity);
    if (new_buffer == NULL) {
        return 0;
    }

    *buffer = new_buffer;
    *capacity = new_capacity;
    return 1;
}

static int read_token(char **token)
{
    size_t capacity = 32;
    size_t length = 0;
    char *buffer;
    int ch;

    if (token == NULL) {
        return 0;
    }

    *token = NULL;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            return 0;
        }

        if (!isspace((unsigned char)ch)) {
            break;
        }
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length + 1 >= capacity) {
            if (!grow_buffer(&buffer, &capacity)) {
                free(buffer);
                return 0;
            }
        }

        buffer[length++] = (char)ch;

        ch = fgetc(stdin);
        if (ch == EOF || isspace((unsigned char)ch)) {
            break;
        }
    }

    if (ch == EOF && ferror(stdin)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *token = buffer;
    return 1;
}

static int read_size(size_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    uintmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    if (buffer[0] == '\0' ||
        buffer[0] == '-' ||
        !isdigit((unsigned char)buffer[0])) {
        free(buffer);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed <= (uintmax_t)SIZE_MAX;

    if (valid) {
        *value = (size_t)parsed;
    }

    free(buffer);
    return valid;
}

static int read_int64(int64_t *value)
{
    char *buffer = NULL;
    char *end = NULL;
    intmax_t parsed;
    int valid;

    if (value == NULL || !read_token(&buffer)) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(buffer, &end, 10);

    valid = errno != ERANGE &&
            end != buffer &&
            *end == '\0' &&
            parsed >= INT64_MIN &&
            parsed <= INT64_MAX;

    if (valid) {
        *value = (int64_t)parsed;
    }

    free(buffer);
    return valid;
}

int main(void)
{
    size_t length;
    int64_t *array = NULL;
    int64_t result;

    if (!read_size(&length)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > SIZE_MAX / sizeof(*array)) {
        fputs("Array is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (length != 0) {
        array = malloc(length * sizeof(*array));
        if (array == NULL) {
            fputs("Unable to allocate array\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid array element\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    if (!max_non_adjacent_sum(array, length, &result)) {
        fputs("Unable to calculate the maximum sum\n", stderr);
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
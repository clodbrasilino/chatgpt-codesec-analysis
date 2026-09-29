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

static int read_line(char **line)
{
    if (line == NULL) {
        return -1;
    }

    *line = NULL;

    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return -1;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (start == end || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 0;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return -1;
    }

    char *buffer = NULL;

    if (read_line(&buffer) != 0) {
        return -1;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return -1;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > SIZE_MAX) {
        free(buffer);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return -1;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 0;
}

static int find_minimum_difference(int64_t *array, size_t length,
                                   uint64_t *result)
{
    if (array == NULL || result == NULL || length < 2) {
        return -1;
    }

    qsort(array, length, sizeof *array, compare_int64);

    uint64_t minimum = UINT64_MAX;

    for (size_t i = 1; i < length; ++i) {
        uint64_t difference =
            (uint64_t)array[i] - (uint64_t)array[i - 1];

        if (difference < minimum) {
            minimum = difference;
        }
    }

    *result = minimum;
    return 0;
}

int main(void)
{
    size_t length = 0;

    if (read_size(&length) != 0 || length < 2 ||
        length > SIZE_MAX / sizeof(int64_t)) {
        fputs("Invalid array length\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof *array);

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

    uint64_t minimum_difference = 0;

    if (find_minimum_difference(array, length, &minimum_difference) != 0) {
        fputs("Unable to calculate minimum difference\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", minimum_difference);

    free(array);
    return EXIT_SUCCESS;
}
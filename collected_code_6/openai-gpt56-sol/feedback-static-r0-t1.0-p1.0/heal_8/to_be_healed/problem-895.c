#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

static int read_line(char **line)
{
    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_capacity = capacity * 2;
            char *new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_int64(int64_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = NULL;

    if (!read_line(&buffer)) {
        return 0;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    char *end = NULL;
    intmax_t parsed = strtoimax(start, &end, 10);

    if (end == start || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (int64_t)parsed;
    free(buffer);
    return 1;
}

static int read_size(size_t *value)
{
    if (value == NULL) {
        return 0;
    }

    char *buffer = NULL;

    if (!read_line(&buffer)) {
        return 0;
    }

    char *start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(buffer);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed == 0 ||
        parsed > SIZE_MAX ||
        parsed > SIZE_MAX / sizeof(int64_t)) {
        free(buffer);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = (size_t)parsed;
    free(buffer);
    return 1;
}

static int max_non_adjacent_sum(const int64_t *array, size_t length,
                                int64_t *result)
{
    if (array == NULL || result == NULL || length == 0) {
        return 0;
    }

    int64_t previous_two = 0;
    int64_t previous_one = array[0] > 0 ? array[0] : 0;

    for (size_t i = 1; i < length; ++i) {
        int64_t include;

        if (array[i] > 0 && previous_two > INT64_MAX - array[i]) {
            return 0;
        }

        if (array[i] < 0 && previous_two < INT64_MIN - array[i]) {
            return 0;
        }

        include = previous_two + array[i];

        int64_t current = include > previous_one
                              ? include
                              : previous_one;

        previous_two = previous_one;
        previous_one = current;
    }

    *result = previous_one;
    return 1;
}

int main(void)
{
    size_t length = 0;

    if (!read_size(&length)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    int64_t *array = malloc(length * sizeof(*array));

    if (array == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (!read_int64(&array[i])) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    int64_t result = 0;

    if (!max_non_adjacent_sum(array, length, &result)) {
        fputs("Unable to calculate result\n", stderr);
        free(array);
        return EXIT_FAILURE;
    }

    free(array);

    if (printf("%" PRId64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
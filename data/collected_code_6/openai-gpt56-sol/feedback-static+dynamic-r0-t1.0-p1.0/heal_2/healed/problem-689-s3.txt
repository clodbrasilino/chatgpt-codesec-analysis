#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>

static int minimum_jumps(const size_t array[], size_t length, size_t *result)
{
    size_t jumps = 0;
    size_t current_end = 0;
    size_t farthest = 0;

    if (array == NULL || result == NULL || length == 0) {
        return -1;
    }

    if (length == 1) {
        *result = 0;
        return 0;
    }

    for (size_t i = 0; i < length - 1; ++i) {
        size_t reach;

        if (array[i] > SIZE_MAX - i) {
            reach = SIZE_MAX;
        } else {
            reach = i + array[i];
        }

        if (reach > farthest) {
            farthest = reach;
        }

        if (i == current_end) {
            if (farthest <= i) {
                return 1;
            }

            ++jumps;
            current_end = farthest;

            if (current_end >= length - 1) {
                *result = jumps;
                return 0;
            }
        }
    }

    return 1;
}

static int read_size_value(size_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    uintmax_t parsed;

    if (value == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > SIZE_MAX) {
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

int main(void)
{
    size_t length;
    size_t *array;
    size_t result;
    int status;

    if (read_size_value(&length) != 0 ||
        length == 0 ||
        length > SIZE_MAX / sizeof *array) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    array = malloc(length * sizeof *array);
    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_size_value(&array[i]) != 0) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }
    }

    status = minimum_jumps(array, length, &result);
    free(array);

    if (status < 0) {
        fputs("Invalid arguments\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
        return EXIT_SUCCESS;
    }

    printf("%zu\n", result);
    return EXIT_SUCCESS;
}
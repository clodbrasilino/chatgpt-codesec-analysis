#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int read_uintmax(uintmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;
    char *start;
    char *end;

    if (value == NULL) {
        return -1;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity;
            char *new_line;

            if (capacity == 0) {
                new_capacity = 64;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(line);
                    return -1;
                }
                new_capacity = capacity * 2;
            }

            if (new_capacity <= length ||
                new_capacity > SIZE_MAX / sizeof(*line)) {
                free(line);
                return -1;
            }

            new_line = realloc(line, new_capacity * sizeof(*line));
            if (new_line == NULL) {
                free(line);
                return -1;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)character;
    }

    if (character == EOF && length == 0) {
        free(line);
        return -1;
    }

    if (length == capacity) {
        char *new_line;

        if (capacity == SIZE_MAX) {
            free(line);
            return -1;
        }

        new_line = realloc(line, (capacity + 1) * sizeof(*line));
        if (new_line == NULL) {
            free(line);
            return -1;
        }

        line = new_line;
        capacity++;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(line);
        return -1;
    }

    errno = 0;
    *value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE) {
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

    free(line);
    return 0;
}

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

    if (array[0] == 0) {
        return 1;
    }

    for (size_t i = 0; i < length - 1; ++i) {
        size_t reach = array[i] > SIZE_MAX - i
                     ? SIZE_MAX
                     : i + array[i];

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

int main(void)
{
    uintmax_t input;
    size_t length;
    size_t *array;
    size_t result;
    int status;

    if (read_uintmax(&input) != 0 ||
        input == 0 ||
        input > SIZE_MAX ||
        input > SIZE_MAX / sizeof(*array)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = (size_t)input;
    array = malloc(length * sizeof(*array));

    if (array == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; ++i) {
        if (read_uintmax(&input) != 0 || input > SIZE_MAX) {
            fputs("Invalid input\n", stderr);
            free(array);
            return EXIT_FAILURE;
        }

        array[i] = (size_t)input;
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
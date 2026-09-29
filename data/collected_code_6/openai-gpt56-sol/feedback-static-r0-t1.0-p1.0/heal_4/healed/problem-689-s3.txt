#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>

static int read_uintmax(uintmax_t *value)
{
    char buffer[256];
    char *start;
    char *end;
    size_t length;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] != '\0') {
        return -1;
    } else if (length == sizeof buffer - 1) {
        int character = getchar();

        if (character != '\n' && character != EOF) {
            while ((character = getchar()) != '\n' && character != EOF) {
            }
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return -1;
    }

    errno = 0;
    *value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
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

    for (size_t i = 0; i < length - 1; ++i) {
        size_t reach;

        if (i > farthest) {
            return 1;
        }

        reach = array[i] > SIZE_MAX - i ? SIZE_MAX : i + array[i];

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
        input > SIZE_MAX / sizeof *array) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    length = (size_t)input;
    array = malloc(length * sizeof *array);

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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>

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
        size_t reach = array[i] > SIZE_MAX - i ? SIZE_MAX : i + array[i];

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t parsed;

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || parsed > SIZE_MAX) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = (size_t)parsed;
    return 0;
}

int main(void)
{
    size_t length;
    size_t *array;
    size_t result;
    int status;

    if (read_size_value(&length) != 0 || length == 0 ||
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
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool are_reverse_strings(const char *first, const char *second)
{
    size_t first_length;
    size_t second_length;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    for (size_t i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const char *const strings[],
                                size_t count,
                                uintmax_t *result)
{
    uintmax_t pairs = 0;

    if (result == NULL || (count != 0 && strings == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (are_reverse_strings(strings[i], strings[j])) {
                if (pairs == UINTMAX_MAX) {
                    return false;
                }
                ++pairs;
            }
        }
    }

    *result = pairs;
    return true;
}

int main(int argc, char *const argv[])
{
    const char **strings = NULL;
    size_t count = 0;
    uintmax_t pairs;
    int status = EXIT_FAILURE;

    if (argc > 1) {
        count = (size_t)(argc - 1);

        if (count > SIZE_MAX / sizeof(*strings)) {
            fputs("Too many input strings.\n", stderr);
            return EXIT_FAILURE;
        }

        strings = malloc(count * sizeof(*strings));
        if (strings == NULL) {
            fputs("Failed to allocate input string array.\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < count; ++i) {
            strings[i] = argv[i + 1];
        }
    }

    if (!count_reverse_pairs(strings, count, &pairs)) {
        fputs("Failed to count reverse string pairs.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", pairs) < 0) {
        fputs("Failed to write the result.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(strings);
    return status;
}
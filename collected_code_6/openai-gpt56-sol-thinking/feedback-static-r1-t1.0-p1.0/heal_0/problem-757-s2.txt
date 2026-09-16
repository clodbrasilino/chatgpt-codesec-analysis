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
    size_t i;

    if (first == NULL || second == NULL) {
        return false;
    }

    first_length = strlen(first);
    second_length = strlen(second);

    if (first_length != second_length) {
        return false;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(char *strings[], size_t count, uintmax_t *result)
{
    size_t i;
    size_t j;
    uintmax_t pairs = 0;

    if (result == NULL || (count > 0 && strings == NULL)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }

        for (j = i + 1; j < count; ++j) {
            if (strings[j] == NULL) {
                return false;
            }

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

int main(int argc, char *argv[])
{
    char **strings = NULL;
    size_t count = 0;
    uintmax_t pairs = 0;

    if (argc > 1) {
        strings = &argv[1];
        count = (size_t)(argc - 1);
    }

    if (!count_reverse_pairs(strings, count, &pairs)) {
        fputs("Failed to count reverse string pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", pairs) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
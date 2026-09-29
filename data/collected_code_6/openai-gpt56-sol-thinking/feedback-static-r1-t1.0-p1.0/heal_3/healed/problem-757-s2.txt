#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

static bool are_reverse_strings(const string_view *first,
                                const string_view *second)
{
    if (first == NULL || second == NULL ||
        first->data == NULL || second->data == NULL) {
        return false;
    }

    if (first->length != second->length) {
        return false;
    }

    for (size_t i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[first->length - i - 1]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const string_view strings[],
                                size_t count,
                                uintmax_t *result)
{
    if (result == NULL || (count > 0 && strings == NULL)) {
        return false;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i].data == NULL) {
            return false;
        }
    }

    uintmax_t pairs = 0;

    for (size_t i = 0; i < count; ++i) {
        for (size_t j = i + 1; j < count; ++j) {
            if (are_reverse_strings(&strings[i], &strings[j])) {
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
    string_view *strings = NULL;
    size_t count = 0;
    uintmax_t pairs = 0;

    if (argc > 1) {
        count = (size_t)(argc - 1);

        if (count > SIZE_MAX / sizeof(*strings)) {
            fputs("Too many strings.\n", stderr);
            return EXIT_FAILURE;
        }

        strings = malloc(count * sizeof(*strings));
        if (strings == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        for (size_t i = 0; i < count; ++i) {
            const char *const argument = argv[i + 1];

            if (argument == NULL) {
                free(strings);
                fputs("Invalid string argument.\n", stderr);
                return EXIT_FAILURE;
            }

            strings[i].data = argument;
            strings[i].length = strlen(argument);
        }
    }

    if (!count_reverse_pairs(strings, count, &pairs)) {
        free(strings);
        fputs("Failed to count reverse string pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIuMAX "\n", pairs) < 0) {
        free(strings);
        return EXIT_FAILURE;
    }

    free(strings);
    return EXIT_SUCCESS;
}
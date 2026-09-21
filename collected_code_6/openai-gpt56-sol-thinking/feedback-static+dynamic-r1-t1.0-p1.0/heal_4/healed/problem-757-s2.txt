#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct string_view {
    const char *data;
    size_t length;
};

static bool are_reverse_strings(const struct string_view *first,
                                const struct string_view *second)
{
    size_t i;

    if (first == NULL || second == NULL ||
        first->data == NULL || second->data == NULL ||
        first->length != second->length) {
        return false;
    }

    for (i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[first->length - i - 1]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const struct string_view *strings,
                                size_t count,
                                uintmax_t *result)
{
    size_t i;
    size_t j;
    uintmax_t pairs = 0;

    if (result == NULL || (count != 0 && strings == NULL)) {
        return false;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i].data == NULL) {
            return false;
        }
    }

    for (i = 0; i < count; ++i) {
        for (j = i + 1; j < count; ++j) {
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

int main(int argc, char ** const argv)
{
    struct string_view *strings = NULL;
    size_t count = 0;
    size_t i;
    uintmax_t pairs = 0;
    int status = EXIT_FAILURE;

    if (argc < 0 || argv == NULL) {
        fputs("Invalid command-line arguments.\n", stderr);
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        uintmax_t argument_count = (uintmax_t)(argc - 1);

        if (argument_count > (uintmax_t)(SIZE_MAX / sizeof(*strings))) {
            fputs("Too many strings.\n", stderr);
            return EXIT_FAILURE;
        }

        count = (size_t)argument_count;
        strings = malloc(count * sizeof(*strings));

        if (strings == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        for (i = 0; i < count; ++i) {
            const char *argument = argv[i + 1];

            if (argument == NULL) {
                fputs("Invalid command-line argument.\n", stderr);
                goto cleanup;
            }

            strings[i].data = argument;
            strings[i].length = strlen(argument);
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
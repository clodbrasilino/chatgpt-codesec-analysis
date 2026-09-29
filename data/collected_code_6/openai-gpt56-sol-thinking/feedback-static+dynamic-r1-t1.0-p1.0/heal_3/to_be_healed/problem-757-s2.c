#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct string_view {
    const char *data;
    size_t length;
};

static size_t argv_string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

static bool are_reverse_strings(const struct string_view *first,
                                const struct string_view *second)
{
    size_t i;

    if (first == NULL || second == NULL ||
        first->data == NULL || second->data == NULL) {
        return false;
    }

    if (first->length != second->length) {
        return false;
    }

    for (i = 0; i < first->length; ++i) {
        if (first->data[i] != second->data[first->length - i - 1]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const struct string_view strings[],
                                size_t count,
                                uintmax_t *result)
{
    size_t i;
    size_t j;
    uintmax_t pairs = 0;

    if (result == NULL || (count > 0 && strings == NULL)) {
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    struct string_view *strings = NULL;
    size_t count = 0;
    size_t i;
    uintmax_t pairs = 0;
    int status = EXIT_FAILURE;

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

        for (i = 0; i < count; ++i) {
            if (argv[i + 1] == NULL) {
                fputs("Invalid command-line argument.\n", stderr);
                goto cleanup;
            }

            strings[i].data = argv[i + 1];
            strings[i].length = argv_string_length(argv[i + 1]);
        }
    }

    if (!count_reverse_pairs(strings, count, &pairs)) {
        fputs("Failed to count reverse string pairs.\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", pairs) < 0) {
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(strings);
    return status;
}
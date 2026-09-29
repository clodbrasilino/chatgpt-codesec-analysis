#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *data;
    size_t length;
} string_view;

static size_t argument_length(const char *argument)
{
    size_t length = 0U;

    while (argument[length] != '\0') {
        ++length;
    }

    return length;
}

static bool are_reverses(const string_view *left, const string_view *right)
{
    if (left == NULL || right == NULL ||
        left->data == NULL || right->data == NULL ||
        left->length != right->length) {
        return false;
    }

    for (size_t i = 0U; i < left->length; ++i) {
        if (left->data[i] != right->data[left->length - i - 1U]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const string_view strings[],
                                size_t string_count,
                                size_t *pair_count)
{
    size_t count = 0U;

    if (pair_count == NULL ||
        (strings == NULL && string_count != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < string_count; ++i) {
        if (strings[i].data == NULL) {
            return false;
        }

        for (size_t j = i + 1U; j < string_count; ++j) {
            if (strings[j].data == NULL) {
                return false;
            }

            if (are_reverses(&strings[i], &strings[j])) {
                if (count == SIZE_MAX) {
                    return false;
                }

                ++count;
            }
        }
    }

    *pair_count = count;
    return true;
}

int main(int argc, char *argv[])
{
    string_view *strings;
    size_t string_count;
    size_t pair_count;

    if (argc <= 1) {
        return printf("0\n") < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    string_count = (size_t)(argc - 1);

    if (string_count > SIZE_MAX / sizeof(*strings)) {
        return EXIT_FAILURE;
    }

    strings = malloc(string_count * sizeof(*strings));
    if (strings == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < string_count; ++i) {
        if (argv[i + 1U] == NULL) {
            free(strings);
            return EXIT_FAILURE;
        }

        strings[i].data = argv[i + 1U];
        strings[i].length = argument_length(argv[i + 1U]);
    }

    if (!count_reverse_pairs(strings, string_count, &pair_count)) {
        free(strings);
        return EXIT_FAILURE;
    }

    free(strings);

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
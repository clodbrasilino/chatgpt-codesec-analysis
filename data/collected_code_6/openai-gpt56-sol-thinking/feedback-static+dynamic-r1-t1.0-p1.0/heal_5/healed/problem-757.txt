#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct string_view {
    const char *data;
    size_t length;
};

static bool make_string_view(const char *string, struct string_view *view)
{
    size_t length = 0U;

    if (string == NULL || view == NULL) {
        return false;
    }

    while (string[length] != '\0') {
        if (length == SIZE_MAX - 1U) {
            return false;
        }

        ++length;
    }

    view->data = string;
    view->length = length;
    return true;
}

static bool are_reverses(const struct string_view *left,
                         const struct string_view *right)
{
    if (left == NULL || right == NULL ||
        left->data == NULL || right->data == NULL) {
        return false;
    }

    if (left->length != right->length) {
        return false;
    }

    for (size_t i = 0U; i < left->length; ++i) {
        if (left->data[i] != right->data[left->length - i - 1U]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(const struct string_view *strings,
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

int main(int argc, char **argv)
{
    struct string_view *strings;
    size_t string_count;
    size_t pair_count;
    int result = EXIT_FAILURE;

    if (argv == NULL || argc < 0) {
        return EXIT_FAILURE;
    }

    if (argc <= 1) {
        return printf("0\n") < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if ((uintmax_t)(argc - 1) > (uintmax_t)SIZE_MAX) {
        return EXIT_FAILURE;
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
        if (!make_string_view(argv[i + 1U], &strings[i])) {
            goto cleanup;
        }
    }

    if (!count_reverse_pairs(strings, string_count, &pair_count)) {
        goto cleanup;
    }

    if (printf("%zu\n", pair_count) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(strings);
    return result;
}
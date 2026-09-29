#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool are_reverses(const char *left, const char *right)
{
    size_t left_length;
    size_t right_length;

    if (left == NULL || right == NULL) {
        return false;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    left_length = strlen(left);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right_length = strlen(right);

    if (left_length != right_length) {
        return false;
    }

    for (size_t i = 0U; i < left_length; ++i) {
        if (left[i] != right[left_length - i - 1U]) {
            return false;
        }
    }

    return true;
}

static bool count_reverse_pairs(char *const *strings,
                                size_t string_count,
                                size_t *pair_count)
{
    size_t count = 0U;

    if (pair_count == NULL ||
        (strings == NULL && string_count != 0U)) {
        return false;
    }

    for (size_t i = 0U; i < string_count; ++i) {
        if (strings[i] == NULL) {
            return false;
        }
    }

    for (size_t i = 0U; i < string_count; ++i) {
        for (size_t j = i + 1U; j < string_count; ++j) {
            if (are_reverses(strings[i], strings[j])) {
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
    size_t string_count;
    size_t pair_count;

    if (argc <= 1) {
        return printf("0\n") < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (argv == NULL) {
        return EXIT_FAILURE;
    }

    if ((uintmax_t)(argc - 1) > (uintmax_t)SIZE_MAX) {
        return EXIT_FAILURE;
    }

    string_count = (size_t)(argc - 1);

    if (!count_reverse_pairs(argv + 1, string_count, &pair_count)) {
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
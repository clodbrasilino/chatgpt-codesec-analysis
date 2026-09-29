#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int are_reverses(const char *first, const char *second)
{
    size_t length;

    if (first == NULL || second == NULL) {
        return 0;
    }

    length = strlen(first);

    if (length != strlen(second)) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (first[i] != second[length - i - 1]) {
            return 0;
        }
    }

    return 1;
}

static int count_reverse_pairs(const char *const strings[],
                               size_t count,
                               size_t *result)
{
    size_t pairs = 0;

    if (strings == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        for (size_t j = i + 1; j < count; ++j) {
            if (strings[j] == NULL) {
                return -1;
            }

            if (are_reverses(strings[i], strings[j])) {
                if (pairs == SIZE_MAX) {
                    return -1;
                }
                ++pairs;
            }
        }
    }

    *result = pairs;
    return 0;
}

int main(void)
{
    static const char *const strings[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "level",
        "level",
        "world"
    };
    const size_t count = sizeof strings / sizeof strings[0];
    size_t pair_count;

    if (count_reverse_pairs(strings, count, &pair_count) != 0) {
        fputs("Failed to count reverse-string pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
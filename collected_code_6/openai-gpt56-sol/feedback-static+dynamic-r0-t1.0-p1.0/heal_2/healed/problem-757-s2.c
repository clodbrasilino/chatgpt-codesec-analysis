#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int are_reverses(const char *first,
                        size_t first_length,
                        const char *second,
                        size_t second_length)
{
    size_t i;

    if (first == NULL || second == NULL || first_length != second_length) {
        return 0;
    }

    for (i = 0; i < first_length; ++i) {
        if (first[i] != second[first_length - i - 1]) {
            return 0;
        }
    }

    return 1;
}

static int count_reverse_pairs(const char *const strings[],
                               const size_t lengths[],
                               size_t count,
                               size_t *result)
{
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (result == NULL ||
        (count != 0 && (strings == NULL || lengths == NULL))) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        for (j = i + 1; j < count; ++j) {
            if (strings[j] == NULL) {
                return -1;
            }

            if (are_reverses(strings[i], lengths[i],
                             strings[j], lengths[j])) {
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
    static const char string_0[] = "abc";
    static const char string_1[] = "cba";
    static const char string_2[] = "hello";
    static const char string_3[] = "olleh";
    static const char string_4[] = "level";
    static const char string_5[] = "level";
    static const char string_6[] = "world";

    const char *const strings[] = {
        string_0,
        string_1,
        string_2,
        string_3,
        string_4,
        string_5,
        string_6
    };

    const size_t lengths[] = {
        sizeof string_0 - 1,
        sizeof string_1 - 1,
        sizeof string_2 - 1,
        sizeof string_3 - 1,
        sizeof string_4 - 1,
        sizeof string_5 - 1,
        sizeof string_6 - 1
    };

    const size_t count = sizeof strings / sizeof strings[0];
    size_t pair_count = 0;

    if (count_reverse_pairs(strings, lengths, count, &pair_count) != 0) {
        fputs("Failed to count reverse-string pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pair_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
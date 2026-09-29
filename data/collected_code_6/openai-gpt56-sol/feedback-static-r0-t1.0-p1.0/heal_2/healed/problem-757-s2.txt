#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int are_reverses(const char *first, size_t first_length,
                        const char *second, size_t second_length)
{
    if (first == NULL || second == NULL || first_length != second_length) {
        return 0;
    }

    for (size_t i = 0; i < first_length; ++i) {
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

    if (strings == NULL || lengths == NULL || result == NULL) {
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
    static const char s0[] = "abc";
    static const char s1[] = "cba";
    static const char s2[] = "hello";
    static const char s3[] = "olleh";
    static const char s4[] = "level";
    static const char s5[] = "level";
    static const char s6[] = "world";

    static const char *const strings[] = {
        s0, s1, s2, s3, s4, s5, s6
    };

    static const size_t lengths[] = {
        sizeof s0 - 1,
        sizeof s1 - 1,
        sizeof s2 - 1,
        sizeof s3 - 1,
        sizeof s4 - 1,
        sizeof s5 - 1,
        sizeof s6 - 1
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
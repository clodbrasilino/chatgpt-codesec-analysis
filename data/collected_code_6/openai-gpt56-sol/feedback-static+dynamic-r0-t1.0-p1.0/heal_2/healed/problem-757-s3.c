#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int are_reverses(const char *first, size_t first_len,
                        const char *second, size_t second_len)
{
    size_t i;

    if (first == NULL || second == NULL || first_len != second_len) {
        return 0;
    }

    for (i = 0; i < first_len; ++i) {
        if (first[i] != second[first_len - i - 1U]) {
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
        (count != 0U && (strings == NULL || lengths == NULL))) {
        return -1;
    }

    for (i = 0; i < count; ++i) {
        if (strings[i] == NULL) {
            return -1;
        }

        for (j = i + 1U; j < count; ++j) {
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
    static const char *const strings[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "abc",
        "level"
    };
    static const size_t lengths[] = {
        sizeof("abc") - 1U,
        sizeof("cba") - 1U,
        sizeof("hello") - 1U,
        sizeof("olleh") - 1U,
        sizeof("abc") - 1U,
        sizeof("level") - 1U
    };
    const size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t pairs = 0;

    if (count != sizeof(lengths) / sizeof(lengths[0])) {
        return EXIT_FAILURE;
    }

    if (count_reverse_pairs(strings, lengths, count, &pairs) != 0) {
        fputs("Failed to count reverse-string pairs.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", pairs) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
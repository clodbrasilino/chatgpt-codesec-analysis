#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

static int is_reverse_pair(const char *first, const char *second)
{
    size_t first_len;
    size_t second_len;
    size_t i;

    if (first == NULL || second == NULL) {
        return 0;
    }

    first_len = strlen(first);
    second_len = strlen(second);

    if (first_len != second_len) {
        return 0;
    }

    for (i = 0; i < first_len; i++) {
        if (first[i] != second[second_len - 1U - i]) {
            return 0;
        }
    }

    return 1;
}

size_t count_reverse_string_pairs(const char *const strings[], size_t count)
{
    size_t pairs;
    size_t i;
    size_t j;

    if (strings == NULL) {
        return 0U;
    }

    pairs = 0U;

    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (j = i + 1U; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse_pair(strings[i], strings[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *const words[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "xyz",
        "zyx",
        "world",
        "abc"
    };
    const size_t word_count = sizeof(words) / sizeof(words[0]);
    size_t pairs;

    pairs = count_reverse_string_pairs(words, word_count);

    if (printf("Number of reverse string pairs: %zu\n", pairs) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define MAX_STRING_LENGTH 4096U

static size_t bounded_strlen(const char *s, size_t max_len)
{
    size_t len;

    len = 0U;
    while (len < max_len && s[len] != '\0') {
        len++;
    }

    return len;
}

static int is_reverse_pair(const char *first, const char *second)
{
    size_t first_len;
    size_t second_len;
    size_t i;

    if (first == NULL || second == NULL) {
        return 0;
    }

    first_len = bounded_strlen(first, MAX_STRING_LENGTH);
    second_len = bounded_strlen(second, MAX_STRING_LENGTH);

    if (first_len >= MAX_STRING_LENGTH || second_len >= MAX_STRING_LENGTH) {
        return 0;
    }

    if (first_len != second_len) {
        return 0;
    }

    for (i = 0U; i < first_len; i++) {
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

    for (i = 0U; i < count; i++) {
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
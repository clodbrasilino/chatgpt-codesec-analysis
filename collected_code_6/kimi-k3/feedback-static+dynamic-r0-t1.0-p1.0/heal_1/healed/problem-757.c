#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_reverse_pair(const char *s1, const char *s2, size_t len1, size_t len2)
{
    size_t i;

    if (s1 == NULL || s2 == NULL) {
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

size_t count_reverse_pairs(const char *list[], size_t count)
{
    size_t i;
    size_t j;
    size_t pairs;
    size_t *lengths;

    if (list == NULL || count == 0) {
        return 0;
    }

    lengths = malloc(count * sizeof(size_t));
    if (lengths == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (list[i] != NULL) {
            lengths[i] = strnlen(list[i], 4096);
        } else {
            lengths[i] = 0;
        }
    }

    pairs = 0;

    for (i = 0; i < count; i++) {
        if (list[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < count; j++) {
            if (list[j] == NULL) {
                continue;
            }
            if (is_reverse_pair(list[i], list[j], lengths[i], lengths[j])) {
                pairs++;
            }
        }
    }

    free(lengths);
    return pairs;
}

int main(void)
{
    const char *list[] = {
        "abc",
        "cba",
        "hello",
        "olleh",
        "xyz",
        "abc",
        "cba",
        NULL
    };
    size_t count;
    size_t result;

    count = sizeof(list) / sizeof(list[0]) - 1;
    result = count_reverse_pairs(list, count);

    printf("Number of reverse string pairs: %zu\n", result);

    return 0;
}
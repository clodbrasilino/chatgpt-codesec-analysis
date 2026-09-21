#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 4096

static int bounded_length(const char *s, size_t *len_out)
{
    size_t len;

    len = 0;
    while (len < MAX_STRING_LENGTH) {
        if (s[len] == '\0') {
            *len_out = len;
            return 1;
        }
        len++;
    }
    return 0;
}

static int is_reverse(const char *str1, const char *str2)
{
    size_t len1;
    size_t len2;
    size_t i;

    if (str1 == NULL || str2 == NULL) {
        return 0;
    }

    if (!bounded_length(str1, &len1) || !bounded_length(str2, &len2)) {
        return 0;
    }

    if (len1 != len2) {
        return 0;
    }

    for (i = 0; i < len1; i++) {
        if (str1[i] != str2[len1 - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int count_reverse_pairs(const char *list[], size_t count)
{
    int pairs;
    size_t i;
    size_t j;

    if (list == NULL) {
        return 0;
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
            if (is_reverse(list[i], list[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *words[] = {"code", "edoc", "abc", "cba", "hello", "olleh", "test"};
    size_t count;
    int result;

    count = sizeof(words) / sizeof(words[0]);
    result = count_reverse_pairs(words, count);

    printf("Number of reverse string pairs: %d\n", result);

    return EXIT_SUCCESS;
}
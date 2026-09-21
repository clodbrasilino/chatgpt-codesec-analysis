#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_STRING_LEN 4096

static size_t bounded_strlen(const char *s, size_t maxlen)
{
    size_t len = 0;

    if (s == NULL) {
        return 0;
    }

    while (len < maxlen && s[len] != '\0') {
        len++;
    }

    return len;
}

static bool is_reverse(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;

    if (s1 == NULL || s2 == NULL) {
        return false;
    }

    len1 = bounded_strlen(s1, MAX_STRING_LEN);
    len2 = bounded_strlen(s2, MAX_STRING_LEN);

    if (len1 != len2) {
        return false;
    }

    for (i = 0; i < len1; i++) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return false;
        }
    }

    return true;
}

size_t count_reverse_pairs(const char * const strings[], size_t count)
{
    size_t pairs = 0;
    size_t i;
    size_t j;

    if (strings == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (j = i + 1; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse(strings[i], strings[j])) {
                pairs++;
            }
        }
    }

    return pairs;
}

int main(void)
{
    const char *strings[] = {
        "abc",
        "xyz",
        "cba",
        "hello",
        "zyx",
        "olleh",
        "world"
    };
    size_t count = sizeof(strings) / sizeof(strings[0]);
    size_t result = count_reverse_pairs(strings, count);

    printf("Number of reverse pairs: %zu\n", result);

    return 0;
}
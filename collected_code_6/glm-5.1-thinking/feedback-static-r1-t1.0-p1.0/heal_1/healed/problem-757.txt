#include <stdio.h>
#include <string.h>

int is_reverse(const char *s1, const char *s2, size_t maxlen) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }
    size_t len1 = strnlen(s1, maxlen);
    size_t len2 = strnlen(s2, maxlen);
    if (len1 == maxlen || len2 == maxlen) {
        return 0;
    }
    if (len1 != len2) {
        return 0;
    }
    for (size_t i = 0; i < len1; i++) {
        if (s1[i] != s2[len1 - 1 - i]) {
            return 0;
        }
    }
    return 1;
}

size_t count_reverse_pairs(char **strings, size_t count, size_t maxlen) {
    if (strings == NULL || count == 0) {
        return 0;
    }
    size_t pairs = 0;
    for (size_t i = 0; i < count; i++) {
        if (strings[i] == NULL) {
            continue;
        }
        for (size_t j = i + 1; j < count; j++) {
            if (strings[j] == NULL) {
                continue;
            }
            if (is_reverse(strings[i], strings[j], maxlen)) {
                pairs++;
            }
        }
    }
    return pairs;
}

int main(void) {
    char *list[] = {"abc", "cba", "hello", "olleh", "world", "test", "tset", "abc"};
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t result = count_reverse_pairs(list, count, 1024);
    printf("%zu\n", result);
    return 0;
}
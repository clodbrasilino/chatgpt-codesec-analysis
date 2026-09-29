#include <stdio.h>

int is_reverse(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) {
        return 0;
    }
    const char *p1 = s1;
    const char *p2 = s2;
    while (*p2) {
        p2++;
    }
    while (p2 > s2) {
        p2--;
        if (*p1 != *p2) {
            return 0;
        }
        p1++;
    }
    return *p1 == '\0';
}

size_t count_reverse_pairs(char **strings, size_t count) {
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
            if (is_reverse(strings[i], strings[j])) {
                pairs++;
            }
        }
    }
    return pairs;
}

int main(void) {
    char *list[] = {"abc", "cba", "hello", "olleh", "world", "test", "tset", "abc"};
    size_t count = sizeof(list) / sizeof(list[0]);
    size_t result = count_reverse_pairs(list, count);
    printf("%zu\n", result);
    return 0;
}
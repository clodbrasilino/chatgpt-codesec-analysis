#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *s, size_t len) {
    if (len < 2) {
        return false;
    }
    char c1 = s[0];
    char c2 = s[1];
    if (c1 == c2) {
        return false;
    }
    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (s[i] != c1) {
                return false;
            }
        } else {
            if (s[i] != c2) {
                return false;
            }
        }
    }
    return true;
}

bool safe_is_alternating(const char *s, size_t max_len) {
    size_t len = strnlen(s, max_len);
    return is_alternating(s, len);
}

int main(void) {
    const char *test1 = "ABABABAB";
    const char *test2 = "ABABABAA";
    const char *test3 = "AAAAAAA";
    const char *test4 = "A";
    const char *test5 = "";

    size_t len1 = strnlen(test1, 1024);
    size_t len2 = strnlen(test2, 1024);
    size_t len3 = strnlen(test3, 1024);
    size_t len4 = strnlen(test4, 1024);
    size_t len5 = strnlen(test5, 1024);

    printf("%s: %d\n", test1, is_alternating(test1, len1));
    printf("%s: %d\n", test2, is_alternating(test2, len2));
    printf("%s: %d\n", test3, is_alternating(test3, len3));
    printf("%s: %d\n", test4, is_alternating(test4, len4));
    printf("%s: %d\n", test5, is_alternating(test5, len5));

    return 0;
}
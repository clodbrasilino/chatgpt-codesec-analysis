#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool is_alternating(const char *s, size_t len) {
    if (len <= 1) {
        return false;
    }
    if (s[0] == s[1]) {
        return false;
    }
    for (size_t i = 2; i < len; i++) {
        if (i % 2 == 0) {
            if (s[i] != s[0]) {
                return false;
            }
        } else {
            if (s[i] != s[1]) {
                return false;
            }
        }
    }
    return true;
}

size_t safe_strlen(const char *s, size_t max_len) {
    for (size_t i = 0; i < max_len; i++) {
        if (s[i] == '\0') {
            return i;
        }
    }
    return max_len;
}

int main(void) {
    const char *test1 = "ABABABAB";
    const char *test2 = "ABABABAA";
    const char *test3 = "AAAAAAA";
    const char *test4 = "A";
    const char *test5 = "";

    printf("%s: %d\n", test1, is_alternating(test1, safe_strlen(test1, 1024)));
    printf("%s: %d\n", test2, is_alternating(test2, safe_strlen(test2, 1024)));
    printf("%s: %d\n", test3, is_alternating(test3, safe_strlen(test3, 1024)));
    printf("%s: %d\n", test4, is_alternating(test4, safe_strlen(test4, 1024)));
    printf("%s: %d\n", test5, is_alternating(test5, safe_strlen(test5, 1024)));

    return 0;
}
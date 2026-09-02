#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_alternating(const char *str) {
    int len = strlen(str);
    if (len < 2) return false;

    for (int i = 2; i < len; ++i) {
        if (str[i] != str[i % 2]) return false;
    }
    return true;
}

int main() {
    const char *test1 = "abab";
    const char *test2 = "aaaa";
    const char *test3 = "abba";

    bool result1 = is_alternating(test1);
    bool result2 = is_alternating(test2);
    bool result3 = is_alternating(test3);

    printf("%s: %s\n", test1, result1 ? "true" : "false");
    printf("%s: %s\n", test2, result2 ? "true" : "false");
    printf("%s: %s\n", test3, result3 ? "true" : "false");

    return 0;
}
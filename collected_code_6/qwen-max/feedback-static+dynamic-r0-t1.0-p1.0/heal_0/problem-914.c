#include <stdio.h>
#include <stdbool.h>

bool is_alternating(const char *str) {
    if (str == NULL || str[0] == '\0' || str[1] == '\0') {
        return false;
    }

    char first = str[0];
    char second = str[1];

    if (first == second) {
        return false;
    }

    for (int i = 2; str[i] != '\0'; ++i) {
        if (i % 2 == 0 && str[i] != first) {
            return false;
        }
        if (i % 2 != 0 && str[i] != second) {
            return false;
        }
    }
    return true;
}

int main() {
    const char *test1 = "ababab";
    const char *test2 = "aabbab";
    const char *test3 = "abc";

    printf("%s: %s\n", test1, is_alternating(test1) ? "True" : "False");
    printf("%s: %s\n", test2, is_alternating(test2) ? "True" : "False");
    printf("%s: %s\n", test3, is_alternating(test3) ? "True" : "False");

    return 0;
}
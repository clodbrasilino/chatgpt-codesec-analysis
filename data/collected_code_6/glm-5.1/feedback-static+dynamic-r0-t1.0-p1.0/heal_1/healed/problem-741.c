#include <stdio.h>
#include <stdbool.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (str[0] == '\0') {
        return true;
    }

    char first = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test1 = "aaaa";
    const char *test2 = "abaa";
    const char *test3 = "";
    const char *test4 = NULL;

    printf("%d\n", are_all_chars_same(test1));
    printf("%d\n", are_all_chars_same(test2));
    printf("%d\n", are_all_chars_same(test3));
    printf("%d\n", are_all_chars_same(test4));

    return 0;
}
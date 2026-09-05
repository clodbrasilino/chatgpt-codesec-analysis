#include <stdio.h>
#include <stdbool.h>

bool are_all_chars_same(const char *str) {
    if (str == NULL) {
        return false;
    }

    if (*str == '\0') {
        return true;
    }

    char first = *str;
    str++;

    while (*str != '\0') {
        if (*str != first) {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    char str1[] = "aaaa";
    char str2[] = "abaa";
    char str3[] = "";
    char *str4 = NULL;

    printf("%d\n", are_all_chars_same(str1));
    printf("%d\n", are_all_chars_same(str2));
    printf("%d\n", are_all_chars_same(str3));
    printf("%d\n", are_all_chars_same(str4));

    return 0;
}
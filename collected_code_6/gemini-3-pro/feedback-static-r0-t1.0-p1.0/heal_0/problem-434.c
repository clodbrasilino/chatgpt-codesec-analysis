#include <stdio.h>
#include <string.h>

int match_string(const char *str) {
    if (str == NULL || *str != 'a') {
        return 0;
    }

    str++;

    if (*str != 'b') {
        return 0;
    }

    while (*str == 'b') {
        str++;
    }

    if (*str != '\0') {
        return 0;
    }

    return 1;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "abb",
        "abbb",
        "a",
        "b",
        "abc",
        "abbc",
        NULL
    };

    for (int i = 0; test_strings[i] != NULL; i++) {
        if (match_string(test_strings[i])) {
            printf("String '%s' matches.\n", test_strings[i]);
        } else {
            printf("String '%s' does not match.\n", test_strings[i]);
        }
    }

    return 0;
}
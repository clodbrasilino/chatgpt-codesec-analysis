#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_a_zero_or_one_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    if (*str == 'a') {
        str++;
        if (*str == 'b') {
            str++;
        }
        if (*str == '\0') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "b",
        "ba",
        "abc",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (match_a_zero_or_one_b(test_strings[i])) {
            printf("\"%s\" matches.\n", test_strings[i]);
        } else {
            printf("\"%s\" does not match.\n", test_strings[i]);
        }
    }

    return 0;
}
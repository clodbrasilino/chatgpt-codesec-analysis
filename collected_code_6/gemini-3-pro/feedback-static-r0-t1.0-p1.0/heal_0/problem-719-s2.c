#include <stdio.h>
#include <string.h>

int match_a_zero_or_more_bs(const char *str) {
    if (str == NULL) {
        return 0;
    }

    if (*str != 'a') {
        return 0;
    }

    str++;

    while (*str == 'b') {
        str++;
    }

    return (*str == '\0');
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "abbb",
        "b",
        "ba",
        "abc",
        "aab",
        "",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            printf("String: '%s' -> Match: %d\n", test_strings[i], match_a_zero_or_more_bs(test_strings[i]));
        } else {
            printf("String: NULL -> Match: %d\n", match_a_zero_or_more_bs(test_strings[i]));
        }
    }

    return 0;
}
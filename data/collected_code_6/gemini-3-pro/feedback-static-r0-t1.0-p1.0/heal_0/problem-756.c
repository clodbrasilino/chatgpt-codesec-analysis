#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return 0;
    }

    if (str[0] == 'a') {
        if (len == 1) {
            return 1;
        } else if (len == 2 && str[1] == 'b') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "a",
        "ab",
        "abb",
        "b",
        "ac",
        "",
        NULL
    };

    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t i = 0; i < num_cases; i++) {
        if (test_cases[i] != NULL) {
            printf("Test case '%s': %d\n", test_cases[i], match_pattern(test_cases[i]));
        } else {
            printf("Test case NULL: %d\n", match_pattern(test_cases[i]));
        }
    }

    return 0;
}
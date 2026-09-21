#include <stdio.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    if (str[0] == '\0') {
        return 0;
    }

    if (str[0] == 'a') {
        if (str[1] == '\0') {
            return 1;
        } else if (str[1] == 'b' && str[2] == '\0') {
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
        "ba",
        "",
        NULL
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        int result = match_pattern(test_cases[i]);
        if (test_cases[i] != NULL) {
            printf("Test case '%s': %s\n", test_cases[i], result ? "Match" : "No match");
        } else {
            printf("Test case NULL: %s\n", result ? "Match" : "No match");
        }
    }
    
    return 0;
}
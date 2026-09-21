#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
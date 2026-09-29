#include <stdio.h>
#include <string.h>

int match_string(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    int len = strlen(str);
    int b_count = 0;
    int a_found = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] == 'a') {
            a_found = 1;
            b_count = 0; 
        } else if (str[i] == 'b' && a_found) {
            b_count++;
        } else {
            if (a_found && (b_count == 2 || b_count == 3)) {
                return 1;
            }
            a_found = 0;
            b_count = 0;
        }
    }

    if (a_found && (b_count == 2 || b_count == 3)) {
        return 1;
    }

    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "abb",
        "abbb",
        "a",
        "ab",
        "abbbb",
        "cabbc",
        "cabbbc",
        "cabbbbc",
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        int result = match_string(test_cases[i]);
        printf("String: '%s' -> Match: %s\n", test_cases[i], result ? "Yes" : "No");
    }

    return 0;
}
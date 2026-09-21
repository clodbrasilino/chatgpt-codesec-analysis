#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match_a_three_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 4) {
        return 0;
    }

    for (size_t i = 0; i <= len - 4; i++) {
        if (str[i] == 'a' && str[i+1] == 'b' && str[i+2] == 'b' && str[i+3] == 'b') {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test_cases[] = {
        "abbb",
        "xabbbx",
        "ab",
        "abb",
        "abbbb",
        "bbaaaabbb",
        NULL
    };

    for (size_t i = 0; test_cases[i] != NULL; i++) {
        int result = match_a_three_b(test_cases[i]);
        if (result) {
            printf("Match found in: %s\n", test_cases[i]);
        } else {
            printf("No match in: %s\n", test_cases[i]);
        }
    }

    return 0;
}
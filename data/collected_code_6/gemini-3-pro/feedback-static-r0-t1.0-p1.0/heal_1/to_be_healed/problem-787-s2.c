#include <stdio.h>
#include <string.h>

int match_a_three_b(const char *str) {
    if (str == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
        if (str[i] == 'a') {
            if (i + 3 < len && str[i + 1] == 'b' && str[i + 2] == 'b' && str[i + 3] == 'b') {
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    const char *test_strings[] = {
        "abbb",
        "aabbbc",
        "ab",
        "abb",
        "abbbb",
        "babbb",
        NULL
    };

    for (size_t i = 0; test_strings[i] != NULL; i++) {
        int result = match_a_three_b(test_strings[i]);
        printf("%s: %d\n", test_strings[i], result);
    }

    return 0;
}
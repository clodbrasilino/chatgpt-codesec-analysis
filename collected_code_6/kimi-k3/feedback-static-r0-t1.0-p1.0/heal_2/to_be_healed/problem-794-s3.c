#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    if (len < 2) {
        return false;
    }
    
    return (str[0] == 'a' && str[len - 1] == 'b');
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "acb",
        "a123b",
        "axyzb",
        "bca",
        "abc",
        "a",
        "b",
        "",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (match_pattern(test_strings[i])) {
            printf("Match: %s\n", test_strings[i]);
        } else {
            printf("No match: %s\n", test_strings[i]);
        }
    }
    
    return 0;
}
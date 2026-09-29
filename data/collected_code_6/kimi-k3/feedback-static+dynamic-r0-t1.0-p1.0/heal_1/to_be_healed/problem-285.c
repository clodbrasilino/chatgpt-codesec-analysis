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
    
    if (len < 3 || len > 4) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (str[1] != 'b' || str[2] != 'b') {
        return false;
    }
    
    if (len == 4 && str[3] != 'b') {
        return false;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "abb",
        "abbb",
        "ab",
        "abbbb",
        "abc",
        "aabb",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (match_pattern(test_strings[i])) {
            printf("\"%s\" matches\n", test_strings[i]);
        } else {
            printf("\"%s\" does not match\n", test_strings[i]);
        }
    }
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_alternating(const char *str) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    
    if (len < 2) {
        return true;
    }
    
    if (str[0] == str[1]) {
        return false;
    }
    
    for (size_t i = 2; i < len; i++) {
        if (str[i] != str[i - 2]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "ababab",
        "aaaa",
        "a",
        "ab",
        "ababa",
        "abcabc",
        "abababa",
        ""
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("\"%s\" -> %s\n", 
               test_strings[i], 
               is_alternating(test_strings[i]) ? "true" : "false");
    }
    
    return 0;
}
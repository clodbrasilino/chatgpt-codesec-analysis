#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_ab23(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }
    
    size_t len = strlen(str);
    if (len < 3 || len > 4) {
        return false;
    }
    
    for (size_t i = 1; i < len; i++) {
        if (str[i] != 'b') {
            return false;
        }
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "abb",
        "abbb",
        "a",
        "ab",
        "abbbb",
        "ac",
        "abc",
        "abbbbb",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (match_ab23(test_strings[i])) {
            printf("\"%s\" matches\n", test_strings[i]);
        } else {
            printf("\"%s\" does not match\n", test_strings[i]);
        }
    }
    
    return 0;
}
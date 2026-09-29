#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_pattern(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }
    
    size_t i = 1;
    if (str[i] == '\0') {
        return false;
    }
    
    while (str[i] != '\0') {
        if (str[i] != 'b') {
            return false;
        }
        i++;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "abb",
        "abbb",
        "a",
        "b",
        "ac",
        "abc",
        "abbbbc",
        NULL
    };
    
    for (size_t i = 0; test_strings[i] != NULL; i++) {
        if (matches_pattern(test_strings[i])) {
            printf("\"%s\" matches the pattern\n", test_strings[i]);
        } else {
            printf("\"%s\" does NOT match the pattern\n", test_strings[i]);
        }
    }
    
    return 0;
}
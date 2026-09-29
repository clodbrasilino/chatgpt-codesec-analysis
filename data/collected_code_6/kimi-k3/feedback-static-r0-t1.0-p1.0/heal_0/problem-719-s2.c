#include <stdio.h>
#include <string.h>

int match_pattern(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    if (str[0] != 'a') {
        return 0;
    }
    
    size_t i = 1;
    while (str[i] == 'b') {
        i++;
    }
    
    return (str[i] == '\0');
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "abbb",
        "b",
        "ba",
        "abc",
        "aab",
        "abba",
        "",
        NULL
    };
    
    size_t i = 0;
    while (test_strings[i] != NULL) {
        printf("String: \"%s\" - Match: %s\n", 
               test_strings[i], 
               match_pattern(test_strings[i]) ? "Yes" : "No");
        i++;
    }
    
    return 0;
}
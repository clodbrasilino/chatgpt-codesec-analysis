#include <stdio.h>
#include <stdbool.h>

bool match_ab_pattern(const char *str) {
    if (str == NULL || str[0] != 'a') {
        return false;
    }
    
    int i = 1;
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
    const char *test_cases[] = {
        "ab",
        "abb",
        "abbb",
        "a",
        "aab",
        "abc",
        "ac",
        "",
        NULL
    };
    
    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("\"%s\": %s\n", test_cases[i], 
               match_ab_pattern(test_cases[i]) ? "Match" : "No match");
    }
    
    return 0;
}
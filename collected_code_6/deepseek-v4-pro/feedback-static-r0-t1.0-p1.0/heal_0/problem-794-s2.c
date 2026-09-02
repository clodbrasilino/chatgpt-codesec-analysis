#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    size_t len = strlen(str);
    
    if (len < 2) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (str[len - 1] != 'b') {
        return false;
    }
    
    return true;
}

int main(void) {
    const char *test_strings[] = {
        "ab",
        "acb",
        "a123b",
        "a",
        "b",
        "abc",
        "aXYZb",
        "ba",
        "a b",
        "abca",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        printf("\"%s\" -> %s\n", test_strings[i], 
               match_pattern(test_strings[i]) ? "match" : "no match");
    }
    
    return 0;
}
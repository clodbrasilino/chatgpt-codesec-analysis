#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool match_ab(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    if (str[1] == 'b') {
        return str[2] == '\0';
    }
    
    return str[1] == '\0';
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abc",
        "b",
        "ba",
        "aab",
        "abbb",
        "ac",
        ""
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        bool result = match_ab(test_strings[i]);
        printf("String: \"%s\" - Match: %s\n", 
               test_strings[i], 
               result ? "true" : "false");
    }
    
    return 0;
}
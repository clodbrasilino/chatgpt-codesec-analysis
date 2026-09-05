#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    if (str == NULL) {
        return false;
    }
    
    if (str[0] != 'a') {
        return false;
    }
    
    int b_count = 0;
    int i = 1;
    
    while (str[i] == 'b') {
        b_count++;
        i++;
    }
    
    if (b_count < 2 || b_count > 3) {
        return false;
    }
    
    return str[i] == '\0';
}

int main(void) {
    const char *test_strings[] = {
        "abb",
        "abbb",
        "ab",
        "abbbb",
        "a",
        "babb",
        "abbx",
        "abbc"
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("String: %-10s Match: %s\n", 
               test_strings[i], 
               match_pattern(test_strings[i]) ? "true" : "false");
    }
    
    return 0;
}
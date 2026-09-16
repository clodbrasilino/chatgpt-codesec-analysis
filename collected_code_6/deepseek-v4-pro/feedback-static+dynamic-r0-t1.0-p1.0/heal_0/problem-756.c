#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    size_t len = strlen(str);
    if (len == 0) return false;
    if (str[0] != 'a') return false;
    if (len == 1) return true;
    if (len == 2 && str[1] == 'b') return true;
    return false;
}

int main(void) {
    const char *test_strings[] = {
        "a",
        "ab",
        "abb",
        "b",
        "",
        "ac",
        "abc"
    };
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("\"%s\": %s\n", test_strings[i], 
               match_pattern(test_strings[i]) ? "match" : "no match");
    }
    
    return 0;
}
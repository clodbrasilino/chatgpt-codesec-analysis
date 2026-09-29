#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool match_pattern(const char *str) {
    if (str == NULL) return false;
    if (str[0] != 'a') return false;
    if (str[1] == '\0') return true;
    if (str[1] == 'b' && str[2] == '\0') return true;
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
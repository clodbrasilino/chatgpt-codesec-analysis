#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool matches_pattern(const char *str, size_t str_len) {
    if (str_len == 0 || str[0] != 'a') {
        return false;
    }
    if (str_len == 1) {
        return true;
    }
    if (str[1] == 'b') {
        return str_len == 2;
    }
    return false;
}

int main(int argc, char *argv[]) {
    const char *test_cases[] = {
        "a",
        "ab",
        "abb",
        "abc",
        "b",
        "ba",
        ""
    };
    
    size_t num_cases = sizeof(test_cases) / sizeof(test_cases[0]);
    
    for (size_t i = 0; i < num_cases; i++) {
        size_t len = strnlen(test_cases[i], 1024);
        bool result = matches_pattern(test_cases[i], len);
        printf("\"%s\" -> %s\n", test_cases[i], result ? "true" : "false");
    }
    
    return 0;
}
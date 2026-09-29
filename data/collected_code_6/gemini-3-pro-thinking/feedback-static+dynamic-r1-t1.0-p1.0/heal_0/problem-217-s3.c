#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

char find_first_repeated_char(const char *str);

char find_first_repeated_char(const char *str) {
    bool seen[256] = { false };

    if (str == NULL) {
        return '\0';
    }

    while (*str != '\0') {
        unsigned char c = (unsigned char)(*str);
        
        if (seen[c]) {
            return (char)c;
        }
        
        seen[c] = true;
        str++;
    }

    return '\0';
}

int main(void) {
    const char *test_strings[] = {
        "programming",
        "abcdefg",
        "hello",
        "",
        NULL
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);
    size_t i;

    for (i = 0; i < num_tests; i++) {
        char result = find_first_repeated_char(test_strings[i]);
        
        if (result != '\0') {
            printf("String %zu: '%c'\n", i, result);
        } else {
            printf("String %zu: None\n", i);
        }
    }

    return 0;
}
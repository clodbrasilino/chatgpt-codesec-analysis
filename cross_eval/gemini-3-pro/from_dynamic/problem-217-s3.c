#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated_character(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};
    
    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        if (seen[current_char]) {
            return str[i];
        }
        seen[current_char] = 1;
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

    for (size_t i = 0; i < num_tests; i++) {
        char result = find_first_repeated_character(test_strings[i]);
        if (result != '\0') {
            printf("First repeated character in '%s' is: %c\n", 
                   test_strings[i] ? test_strings[i] : "NULL", result);
        } else {
            printf("No repeated character found in '%s'\n", 
                   test_strings[i] ? test_strings[i] : "NULL");
        }
    }

    return 0;
}
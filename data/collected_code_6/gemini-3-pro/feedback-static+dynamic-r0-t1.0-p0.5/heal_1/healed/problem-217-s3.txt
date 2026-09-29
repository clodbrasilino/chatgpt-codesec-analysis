#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (seen[c]) {
            return str[i];
        }
        seen[c] = 1;
    }

    return '\0';
}

int main(void) {
    const char *test_strings[] = {
        "programming",
        "abcdefg",
        NULL
    };
    
    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        const char *current_str = test_strings[i];
        char res = find_first_repeated_char(current_str);
        
        if (current_str == NULL) {
            if (res == '\0') {
                printf("No repeated char in NULL string\n");
            }
        } else {
            if (res != '\0') {
                printf("First repeated char in '%s': %c\n", current_str, res);
            } else {
                printf("No repeated char in '%s'\n", current_str);
            }
        }
    }

    return 0;
}
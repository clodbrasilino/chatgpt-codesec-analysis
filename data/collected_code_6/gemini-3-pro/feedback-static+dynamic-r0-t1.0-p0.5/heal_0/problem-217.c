#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated_char(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int char_counts[256] = {0};

    for (int i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        if (char_counts[current_char] == 1) {
            return str[i];
        }
        char_counts[current_char]++;
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
        char result = find_first_repeated_char(test_strings[i]);
        if (test_strings[i] != NULL) {
            if (result != '\0') {
                printf("String: \"%s\", First repeated char: '%c'\n", test_strings[i], result);
            } else {
                printf("String: \"%s\", No repeated char found.\n", test_strings[i]);
            }
        } else {
            printf("String: NULL, Result: '\\0'\n");
        }
    }

    return 0;
}
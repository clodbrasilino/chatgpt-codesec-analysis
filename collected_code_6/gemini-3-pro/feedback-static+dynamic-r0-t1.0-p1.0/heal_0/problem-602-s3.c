#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char find_first_repeated_character(const char *str) {
    if (str == NULL) {
        return '\0';
    }

    int seen[256] = {0};

    for (size_t i = 0; str[i] != '\0'; i++) {
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
        "hello",
        "programming",
        "abcdef",
        "aabbcc",
        NULL
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); i++) {
        if (test_strings[i] == NULL) {
            continue;
        }
        char result = find_first_repeated_character(test_strings[i]);
        if (result != '\0') {
            printf("First repeated character in '%s' is '%c'\n", test_strings[i], result);
        } else {
            printf("No repeated character found in '%s'\n", test_strings[i]);
        }
    }

    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

bool contains_all_vowels(const char *str, size_t len) {
    bool vowels[5] = {false};
    for (size_t i = 0; i < len; i++) {
        switch (tolower((unsigned char)str[i])) {
            case 'a': vowels[0] = true; break;
            case 'e': vowels[1] = true; break;
            case 'i': vowels[2] = true; break;
            case 'o': vowels[3] = true; break;
            case 'u': vowels[4] = true; break;
        }
    }

    for (int i = 0; i < 5; i++) {
        if (!vowels[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    const char *test_strings[] = {"hello", "education", "sequence", "aeiou", "CQWEN"};
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++) {
        size_t len = strlen(test_strings[i]);
        if (len > SIZE_MAX - 1) {
            printf("Error: String length overflow.\n");
            continue;
        }
        if (contains_all_vowels(test_strings[i], len)) {
            printf("The string \"%s\" contains all vowels.\n", test_strings[i]);
        } else {
            printf("The string \"%s\" does not contain all vowels.\n", test_strings[i]);
        }
    }

    return 0;
}
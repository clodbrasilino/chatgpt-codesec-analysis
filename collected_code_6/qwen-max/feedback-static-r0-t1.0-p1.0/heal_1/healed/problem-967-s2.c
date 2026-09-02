#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_all_vowels(const char *str) {
    bool vowels[5] = {false, false, false, false, false};
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        switch (tolower((unsigned char)str[i])) {
            case 'a': vowels[0] = true; break;
            case 'e': vowels[1] = true; break;
            case 'i': vowels[2] = true; break;
            case 'o': vowels[3] = true; break;
            case 'u': vowels[4] = true; break;
            default: break;
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
        if (contains_all_vowels(test_strings[i])) {
            printf("The string \"%s\" contains all vowels.\n", test_strings[i]);
        } else {
            printf("The string \"%s\" does not contain all vowels.\n", test_strings[i]);
        }
    }

    return 0;
}
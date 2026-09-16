#include <stdio.h>
#include <ctype.h>
#include <string.h>

int count_same_position_chars(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            char current_char = tolower((unsigned char)str[i]);
            if (current_char - 'a' == i) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    const char *test_strings[] = {
        "abode",
        "ABc",
        "xyz",
        "aBcdE",
        NULL
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (test_strings[i] != NULL) {
            int result = count_same_position_chars(test_strings[i]);
            printf("String: %s, Count: %d\n", test_strings[i], result);
        }
    }

    return 0;
}
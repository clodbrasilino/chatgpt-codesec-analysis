#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

bool are_all_characters_same(const char *str) {
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    char first_char = str[0];
    for (size_t i = 1; str[i] != '\0'; i++) {
        if (str[i] != first_char) {
            return false;
        }
    }

    return true;
}

int main(void) {
    const char *test_strings[] = {
        "aaaaa",
        "aaaba",
        "",
        NULL
    };
    
    const char *test_names[] = {
        "test_str1",
        "test_str2",
        "test_str3",
        "test_str4"
    };

    size_t num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (size_t i = 0; i < num_tests; i++) {
        if (are_all_characters_same(test_strings[i])) {
            printf("%s: All characters are the same.\n", test_names[i]);
        } else {
            printf("%s: Characters are not all the same.\n", test_names[i]);
        }
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool contains_letter_and_number(const char *str) {
    bool has_letter = false;
    bool has_number = false;

    while (*str) {
        if (isalpha((unsigned char)*str)) {
            has_letter = true;
        }
        if (isdigit((unsigned char)*str)) {
            has_number = true;
        }
        if (has_letter && has_number) {
            return true;
        }
        str++;
    }

    return false;
}

int main() {
    const char *test_strings[] = {
        "abc123",
        "123",
        "abc",
        "!",
        "a1b2c3",
        ""
    };

    for (size_t i = 0; i < sizeof(test_strings) / sizeof(test_strings[0]); ++i) {
        if (contains_letter_and_number(test_strings[i])) {
            printf("The string \"%s\" contains at least one letter and one number.\n", test_strings[i]);
        } else {
            printf("The string \"%s\" does not contain both a letter and a number.\n", test_strings[i]);
        }
    }

    return 0;
}
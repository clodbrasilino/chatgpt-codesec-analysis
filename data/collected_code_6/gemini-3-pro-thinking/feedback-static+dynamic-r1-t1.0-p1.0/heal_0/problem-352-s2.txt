#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#define MAX_CHAR_VALUES (1 << CHAR_BIT)

bool are_all_characters_unique(const char *str);

bool are_all_characters_unique(const char *str) {
    if (str == NULL) {
        return false;
    }

    bool seen[MAX_CHAR_VALUES] = { false };

    for (size_t i = 0; str[i] != '\0'; i++) {
        unsigned char current_char = (unsigned char)str[i];
        if (seen[current_char]) {
            return false;
        }
        seen[current_char] = true;
    }

    return true;
}

int main(void) {
    const char *valid_unique = "abcdefg";
    const char *valid_duplicate = "hello";
    const char *null_string = NULL;
    const char *empty_string = "";

    if (are_all_characters_unique(valid_unique)) {
        printf("Valid unique string test passed.\n");
    } else {
        printf("Valid unique string test failed.\n");
    }

    if (!are_all_characters_unique(valid_duplicate)) {
        printf("Valid duplicate string test passed.\n");
    } else {
        printf("Valid duplicate string test failed.\n");
    }

    if (!are_all_characters_unique(null_string)) {
        printf("Null string test passed.\n");
    } else {
        printf("Null string test failed.\n");
    }

    if (are_all_characters_unique(empty_string)) {
        printf("Empty string test passed.\n");
    } else {
        printf("Empty string test failed.\n");
    }

    return 0;
}
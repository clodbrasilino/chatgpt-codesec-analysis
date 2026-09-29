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
    const char *test_str1 = "aaaaa";
    const char *test_str2 = "aaaba";
    const char *test_str3 = "";
    const char *test_str4 = NULL;

    if (are_all_characters_same(test_str1)) {
        printf("test_str1: All characters are the same.\n");
    } else {
        printf("test_str1: Characters are not all the same.\n");
    }

    if (are_all_characters_same(test_str2)) {
        printf("test_str2: All characters are the same.\n");
    } else {
        printf("test_str2: Characters are not all the same.\n");
    }

    if (are_all_characters_same(test_str3)) {
        printf("test_str3: All characters are the same.\n");
    } else {
        printf("test_str3: Characters are not all the same.\n");
    }

    /* Possible weaknesses found:
     *  Condition 'are_all_characters_same(test_str4)' is always false [knownConditionTrueFalse]
     *  Calling function 'are_all_characters_same' returns 0
     *  Condition 'are_all_characters_same(test_str4)' is always false
     */
    if (are_all_characters_same(test_str4)) {
        printf("test_str4: All characters are the same.\n");
    } else {
        printf("test_str4: Characters are not all the same.\n");
    }

    return 0;
}
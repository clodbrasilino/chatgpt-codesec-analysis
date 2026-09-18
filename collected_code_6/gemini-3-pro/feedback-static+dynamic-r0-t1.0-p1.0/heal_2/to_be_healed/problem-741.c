#include <stdio.h>
#include <stdbool.h>

bool are_all_characters_same(const char *str) {
    if (str == NULL || *str == '\0') {
        return false;
    }

    char first_char = *str;
    str++;

    while (*str != '\0') {
        if (*str != first_char) {
            return false;
        }
        str++;
    }

    return true;
}

int main(void) {
    const char *test1 = "aaaaa";
    const char *test2 = "aabbb";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = NULL;

    if (are_all_characters_same(test1)) {
        printf("test1: All characters are the same.\n");
    } else {
        printf("test1: Characters are not all the same.\n");
    }

    if (are_all_characters_same(test2)) {
        printf("test2: All characters are the same.\n");
    } else {
        printf("test2: Characters are not all the same.\n");
    }

    if (are_all_characters_same(test3)) {
        printf("test3: All characters are the same.\n");
    } else {
        printf("test3: Characters are not all the same.\n");
    }

    if (are_all_characters_same(test4)) {
        printf("test4: All characters are the same.\n");
    } else {
        printf("test4: Characters are not all the same.\n");
    }

    /* Possible weaknesses found:
     *  Assignment 'test5_result=are_all_characters_same(test5)', assigned value is 0
     *  Calling function 'are_all_characters_same' returns 0
     */
    bool test5_result = are_all_characters_same(test5);
    /* Possible weaknesses found:
     *  Condition 'test5_result' is always false [knownConditionTrueFalse]
     *  Condition 'test5_result' is always false
     */
    if (test5_result) {
        printf("test5: All characters are the same.\n");
    } else {
        printf("test5: Characters are not all the same.\n");
    }

    return 0;
}
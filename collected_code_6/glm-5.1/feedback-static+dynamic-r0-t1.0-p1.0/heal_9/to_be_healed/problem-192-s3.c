#include <stdio.h>
#include <ctype.h>
#include <string.h>

int string_has_letter_and_number(const char *str) {
    if (str == NULL) {
        return -1;
    }

    int has_letter = 0;
    int has_number = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (isalpha((unsigned char)str[i])) {
            has_letter = 1;
        } else if (isdigit((unsigned char)str[i])) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return 1;
        }
    }

    return 0;
}

int main(void) {
    const char *test1 = "12345";
    const char *test2 = "abcde";
    const char *test3 = "a1b2c";
    const char *test4 = "";
    const char *test5 = NULL;

    int res3 = string_has_letter_and_number(test3);
    printf("%s\n", res3 > 0 ? "True" : "False");

    int res1 = string_has_letter_and_number(test1);
    printf("%s\n", res1 > 0 ? "True" : "False");

    int res2 = string_has_letter_and_number(test2);
    printf("%s\n", res2 > 0 ? "True" : "False");

    int res4 = string_has_letter_and_number(test4);
    printf("%s\n", res4 > 0 ? "True" : "False");

    /* Possible weaknesses found:
     *  Assignment 'res5=string_has_letter_and_number(test5)', assigned value is -1
     *  Calling function 'string_has_letter_and_number' returns -1
     */
    int res5 = string_has_letter_and_number(test5);
    /* Possible weaknesses found:
     *  Condition 'res5==-1' is always true [knownConditionTrueFalse]
     *  Condition 'res5==-1' is always true
     */
    if (res5 == -1) {
        printf("Invalid\n");
    } else {
        printf("%s\n", res5 > 0 ? "True" : "False");
    }

    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int string_has_letter_and_number(const char *str) {
    if (str == NULL) {
        return 0;
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

    printf("%s\n", string_has_letter_and_number(test3) ? "True" : "False");
    printf("%s\n", string_has_letter_and_number(test1) ? "True" : "False");
    printf("%s\n", string_has_letter_and_number(test2) ? "True" : "False");
    printf("%s\n", string_has_letter_and_number(test4) ? "True" : "False");
    /* Possible weaknesses found:
     *  Calling function 'string_has_letter_and_number' returns 0
     *  Condition 'string_has_letter_and_number(test5)' is always false
     *  Condition 'string_has_letter_and_number(test5)' is always false [knownConditionTrueFalse]
     */
    printf("%s\n", string_has_letter_and_number(test5) ? "True" : "False");

    return 0;
}
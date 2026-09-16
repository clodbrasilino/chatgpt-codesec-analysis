#include <stdio.h>
#include <ctype.h>
#include <string.h>

int check_string(const char *str) {
    if (str == NULL) {
        return 0;
    }

    int has_letter = 0;
    int has_number = 0;

    for (size_t i = 0; i < strlen(str); i++) {
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
    const char *test5 = "!@#1a";

    printf("%d\n", check_string(test1));
    printf("%d\n", check_string(test2));
    printf("%d\n", check_string(test3));
    printf("%d\n", check_string(test4));
    printf("%d\n", check_string(test5));

    return 0;
}
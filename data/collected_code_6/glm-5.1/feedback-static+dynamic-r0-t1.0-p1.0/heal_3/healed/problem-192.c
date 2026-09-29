#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool check_string(const char *str) {
    if (str == NULL) {
        return false;
    }

    int has_letter = 0;
    int has_number = 0;

    for (const char *p = str; *p != '\0'; p++) {
        if (isalpha((unsigned char)*p)) {
            has_letter = 1;
        } else if (isdigit((unsigned char)*p)) {
            has_number = 1;
        }

        if (has_letter && has_number) {
            return true;
        }
    }

    return false;
}

int main(void) {
    const char *test1 = "12345";
    const char *test2 = "abcde";
    const char *test3 = "a1b2c";
    const char *test4 = "";
    const char *test5 = "!@#1a";

    printf("%s\n", check_string(test1) ? "True" : "False");
    printf("%s\n", check_string(test2) ? "True" : "False");
    printf("%s\n", check_string(test3) ? "True" : "False");
    printf("%s\n", check_string(test4) ? "True" : "False");
    printf("%s\n", check_string(test5) ? "True" : "False");

    return 0;
}
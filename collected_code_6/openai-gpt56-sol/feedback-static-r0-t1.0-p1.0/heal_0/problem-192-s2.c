#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_number = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char ch = (unsigned char)*str;

        if (isalpha(ch) != 0) {
            has_letter = true;
        } else if (isdigit(ch) != 0) {
            has_number = true;
        }

        if (has_letter && has_number) {
            return true;
        }

        ++str;
    }

    return false;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin) != 0) {
            return 1;
        }
        return 0;
    }

    if (has_letter_and_number(input)) {
        puts("The string contains at least one letter and one number.");
    } else {
        puts("The string does not contain at least one letter and one number.");
    }

    return 0;
}
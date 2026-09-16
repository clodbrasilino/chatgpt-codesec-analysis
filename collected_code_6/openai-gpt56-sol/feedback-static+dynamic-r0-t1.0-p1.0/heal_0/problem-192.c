#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

bool has_letter_and_number(const char *string)
{
    bool has_letter = false;
    bool has_number = false;

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (isalpha(character) != 0) {
            has_letter = true;
        } else if (isdigit(character) != 0) {
            has_number = true;
        }

        if (has_letter && has_number) {
            return true;
        }

        ++string;
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

    puts(has_letter_and_number(input) ? "true" : "false");
    return 0;
}
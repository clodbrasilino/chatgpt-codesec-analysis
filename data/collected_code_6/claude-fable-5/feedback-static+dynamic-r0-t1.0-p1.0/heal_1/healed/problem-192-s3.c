#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_digit = false;
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0U; str[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)str[i];
        if (isalpha(ch)) {
            has_letter = true;
        } else if (isdigit(ch)) {
            has_digit = true;
        }
        if (has_letter && has_digit) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    char buffer[256];
    size_t len;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strlen(buffer);
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    }

    if (has_letter_and_number(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    return 0;
}
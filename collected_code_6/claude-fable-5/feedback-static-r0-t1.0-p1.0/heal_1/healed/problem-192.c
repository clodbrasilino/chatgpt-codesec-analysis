#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

bool has_letter_and_number(const char *str)
{
    bool has_letter = false;
    bool has_digit = false;
    size_t i;

    if (str == NULL) {
        return false;
    }

    for (i = 0; str[i] != '\0'; i++) {
        unsigned char c = (unsigned char)str[i];
        if (isalpha(c)) {
            has_letter = true;
        } else if (isdigit(c)) {
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
    char *buffer = NULL;
    size_t bufsize = 0;
    ssize_t len;

    printf("Enter a string: ");

    len = getline(&buffer, &bufsize, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    if (has_letter_and_number(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    free(buffer);
    return 0;
}
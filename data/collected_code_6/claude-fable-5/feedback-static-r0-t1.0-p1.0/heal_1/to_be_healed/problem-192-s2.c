#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool has_letter_and_digit(const char *str)
{
    bool has_letter = false;
    bool has_digit = false;

    if (str == NULL) {
        return false;
    }

    while (*str != '\0') {
        unsigned char c = (unsigned char)*str;
        if (isalpha(c)) {
            has_letter = true;
        } else if (isdigit(c)) {
            has_digit = true;
        }
        if (has_letter && has_digit) {
            return true;
        }
        str++;
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    if (has_letter_and_digit(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    return 0;
}
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    size_t len;

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
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
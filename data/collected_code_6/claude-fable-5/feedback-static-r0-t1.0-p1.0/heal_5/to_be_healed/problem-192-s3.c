#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define BUFFER_SIZE 256

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

static void discard_remaining_input(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;
    size_t count = 0U;

    while (count < (size_t)-1) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
        if (ch == '\n' || ch == EOF) {
            break;
        }
        count++;
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[BUFFER_SIZE];
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1U] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0U && buffer[len - 1U] == '\n') {
        buffer[len - 1U] = '\0';
    } else {
        discard_remaining_input();
    }

    if (has_letter_and_number(buffer)) {
        printf("The string contains at least one letter and one number.\n");
    } else {
        printf("The string does not contain both a letter and a number.\n");
    }

    return EXIT_SUCCESS;
}
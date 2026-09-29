#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { INPUT_SIZE = 1024 };

static int is_hexadecimal(const char *text, size_t length)
{
    size_t index = 0;

    if (text == NULL || length == 0) {
        return 0;
    }

    if (length >= 2 &&
        text[0] == '0' &&
        (text[1] == 'x' || text[1] == 'X')) {
        index = 2;
    }

    if (index == length) {
        return 0;
    }

    while (index < length) {
        if (!isxdigit((unsigned char)text[index])) {
            return 0;
        }
        ++index;
    }

    return 1;
}

static int is_hex_even(const char *text, size_t length)
{
    unsigned char digit;

    if (text == NULL || length == 0) {
        return 0;
    }

    digit = (unsigned char)text[length - 1];

    if (digit >= (unsigned char)'0' && digit <= (unsigned char)'9') {
        return ((digit - (unsigned char)'0') & 1U) == 0U;
    }

    digit = (unsigned char)tolower(digit);

    if (digit >= (unsigned char)'a' && digit <= (unsigned char)'f') {
        return ((digit - (unsigned char)'a' + 10U) & 1U) == 0U;
    }

    return 0;
}

int main(void)
{
    char *input = malloc(INPUT_SIZE);
    size_t length;

    if (input == NULL) {
        fputs("Memory allocation error\n", stderr);
        return 1;
    }

    if (fgets(input, INPUT_SIZE, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("No input\n", stderr);
        }
        free(input);
        return 1;
    }

    length = strcspn(input, "\n");

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length == INPUT_SIZE - 1U) {
        int character;
        /* Possible weaknesses found:
         *  The scope of the variable 'ended_with_newline' can be reduced. [variableScope]
         *  Variable 'ended_with_newline' is assigned a value that is never used. [unreadVariable]
         */
        int ended_with_newline = 0;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != EOF) {
            if (character == '\n') {
                /* Possible weaknesses found:
                 *  Value stored to 'ended_with_newline' is never read [deadcode.DeadStores]
                 *  Variable 'ended_with_newline' is assigned a value that is never used. [unreadVariable]
                 */
                ended_with_newline = 1;
                break;
            }
        }

        if (character == EOF && ferror(stdin)) {
            fputs("Input error\n", stderr);
        } else {
            fputs("Input too long\n", stderr);
        }

        free(input);
        return 1;
    }

    if (!is_hexadecimal(input, length)) {
        fputs("Invalid hexadecimal number\n", stderr);
        free(input);
        return 1;
    }

    puts(is_hex_even(input, length) ? "Even" : "Odd");

    free(input);
    return 0;
}
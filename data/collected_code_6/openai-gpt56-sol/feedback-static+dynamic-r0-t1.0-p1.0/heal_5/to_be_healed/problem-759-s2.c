#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 4096

static bool is_decimal_with_precision_2(const char *text)
{
    const unsigned char *p;
    size_t integer_digits = 0;

    if (text == NULL || *text == '\0') {
        return false;
    }

    p = (const unsigned char *)text;

    if (*p == '+' || *p == '-') {
        ++p;
    }

    while (*p >= '0' && *p <= '9') {
        ++integer_digits;
        ++p;
    }

    if (integer_digits == 0 || *p != '.') {
        return false;
    }

    ++p;

    return p[0] >= '0' && p[0] <= '9' &&
           p[1] >= '0' && p[1] <= '9' &&
           p[2] == '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'character' can be reduced. [variableScope]
     */
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Input error\n", stderr);
                return EXIT_FAILURE;
            }

            fputs("Input too long\n", stderr);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(is_decimal_with_precision_2(input) ? "Valid" : "Invalid");
    return EXIT_SUCCESS;
}
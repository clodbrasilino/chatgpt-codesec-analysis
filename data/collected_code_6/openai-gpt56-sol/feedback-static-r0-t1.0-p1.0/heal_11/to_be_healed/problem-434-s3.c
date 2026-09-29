#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool matches(const char *str)
{
    if (str == NULL || str[0] != 'a' || str[1] != 'b') {
        return false;
    }

    str += 2;

    while (*str == 'b') {
        ++str;
    }

    return *str == '\0';
}

static bool discard_line(void)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch == '\n') {
            return true;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                ungetc(ch, stdin);
            }

            return ch != EOF || !ferror(stdin);
        }

        if (ch == EOF) {
            return !ferror(stdin);
        }
    }
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[MAX_INPUT_LENGTH + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Input error.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t length = strcspn(input, "\r\n");

        if (input[length] == '\0' && length > MAX_INPUT_LENGTH) {
            if (discard_line()) {
                fputs("Input is too long.\n", stderr);
            } else {
                fputs("Input error.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        input[length] = '\0';
    }

    puts(matches(input) ? "Match" : "No match");
    return EXIT_SUCCESS;
}
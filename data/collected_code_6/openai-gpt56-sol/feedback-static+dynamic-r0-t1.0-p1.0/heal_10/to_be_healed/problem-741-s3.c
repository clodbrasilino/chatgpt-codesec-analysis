#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool all_characters_same(const char *str)
{
    if (str == NULL || str[0] == '\0') {
        return false;
    }

    for (size_t i = 1; str[i] != '\0'; ++i) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(input);

        if (length > 0 && input[length - 1] == '\n') {
            input[--length] = '\0';

            if (length > 0 && input[length - 1] == '\r') {
                input[--length] = '\0';
            }
        } else if (!feof(stdin)) {
            int ch;

            do {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        } else if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    }

    puts(all_characters_same(input) ? "True" : "False");
    return EXIT_SUCCESS;
}
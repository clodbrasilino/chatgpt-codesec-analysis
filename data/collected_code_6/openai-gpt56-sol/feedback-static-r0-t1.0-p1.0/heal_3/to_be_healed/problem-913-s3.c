#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

static bool ends_with_number(const char *string, size_t length)
{
    return string != NULL &&
           length > 0U &&
           isdigit((unsigned char)string[length - 1U]) != 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t length = 0U;
    bool truncated = false;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) != 0 ? 1 : 0;
    }

    while (input[length] != '\0' && input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length == sizeof input - 1U) {
        int character;

        truncated = true;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' && character != EOF) {
            if (character == '\r') {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                int next = getchar();

                if (next != '\n' && next != EOF) {
                    ungetc(next, stdin);
                }
                break;
            }
        }

        if (ferror(stdin) != 0) {
            return 1;
        }
    }

    if (truncated) {
        fputs("Input is too long.\n", stderr);
        return 1;
    }

    if (ends_with_number(input, length)) {
        puts("The string ends with a number.");
    } else {
        puts("The string does not end with a number.");
    }

    return 0;
}
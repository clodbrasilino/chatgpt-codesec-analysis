#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool all_characters_same(const char *string)
{
    size_t i;

    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (i = 1U; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
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
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[length - 1U] = '\0';
    } else if (length == sizeof input - 1U) {
        int character;

        do {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            fputs("Input is too long.\n", stderr);
            return 1;
        }
    }

    puts(all_characters_same(input) ? "All characters are the same."
                                    : "Not all characters are the same.");

    return 0;
}
#include <stdbool.h>
#include <stdio.h>

static bool all_characters_same(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    const char first = *string++;

    while (*string != '\0') {
        if (*string++ != first) {
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
    size_t length = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= sizeof input) {
            while (character != '\n' && character != EOF) {
                /* Possible weaknesses found:
                 * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                character = getchar();
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    input[length] = '\0';

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    return 0;
}
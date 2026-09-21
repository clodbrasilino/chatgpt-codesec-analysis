#include <stdbool.h>
#include <stdio.h>

static bool first_and_last_are_equal(const char *string, size_t length)
{
    return string != NULL && length > 0U && string[0] == string[length - 1U];
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
    while (length < sizeof input && (character = getchar()) != EOF &&
           character != '\n' && character != '\r') {
        input[length++] = (char)character;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = getchar();

        if (next != '\n' && next != EOF) {
            ungetc(next, stdin);
        }
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    if (length == sizeof input &&
        character != '\n' && character != '\r' && character != EOF) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((character = getchar()) != '\n' &&
               character != '\r' && character != EOF) {
        }
        fputs("Input too long\n", stderr);
        return 1;
    }

    puts(first_and_last_are_equal(input, length) ? "Equal" : "Not equal");
    return 0;
}
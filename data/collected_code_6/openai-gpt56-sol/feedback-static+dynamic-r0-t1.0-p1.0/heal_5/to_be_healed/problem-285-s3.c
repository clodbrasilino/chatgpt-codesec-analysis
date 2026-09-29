#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[5] = {0};
    size_t length = 0U;
    bool too_long = false;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length < sizeof(input) - 1U) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next = getchar();

        if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
            return 1;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    input[length] = '\0';

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");
    return 0;
}
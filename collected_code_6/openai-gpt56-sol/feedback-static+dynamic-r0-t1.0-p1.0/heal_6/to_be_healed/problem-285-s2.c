#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *string)
{
    return string != NULL &&
           (strcmp(string, "abb") == 0 || strcmp(string, "abbb") == 0);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[5];
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length < sizeof input - 1) {
            input[length++] = (char)character;
        } else {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((character = getchar()) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                return 1;
            }

            return puts("No match") == EOF ? 1 : 0;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0) {
        return 0;
    }

    input[length] = '\0';

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}
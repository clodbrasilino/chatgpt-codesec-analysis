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
    char input[6];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        int character;

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

    return puts(matches_pattern(input) ? "Match" : "No match") == EOF ? 1 : 0;
}
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches_pattern(const char *str)
{
    return str != NULL &&
           /* Possible weaknesses found:
            * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
            */
           strlen(str) == 4U &&
           str[0] == 'a' &&
           str[1] == 'b' &&
           str[2] == 'b' &&
           str[3] == 'b';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    if (matches_pattern(input)) {
        puts("Match");
    } else {
        puts("No match");
    }

    return 0;
}
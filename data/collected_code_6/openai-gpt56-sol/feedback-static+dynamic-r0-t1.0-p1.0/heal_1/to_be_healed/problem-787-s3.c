#include <stdio.h>
#include <string.h>

int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
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

    input[strcspn(input, "\r\n")] = '\0';

    puts(matches(input) ? "Match" : "No match");
    return 0;
}
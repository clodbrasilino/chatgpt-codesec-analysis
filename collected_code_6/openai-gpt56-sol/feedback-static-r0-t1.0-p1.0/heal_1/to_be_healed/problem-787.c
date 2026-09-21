#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool matches(const char *str)
{
    return str != NULL && strcmp(str, "abbb") == 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];

    if (fgets(input, sizeof(input), stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    input[strcspn(input, "\r\n")] = '\0';
    printf("%s\n", matches(input) ? "Match" : "No match");

    return 0;
}
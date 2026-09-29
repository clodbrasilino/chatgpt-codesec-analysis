#include <stdio.h>
#include <string.h>

void remove_spaces(char *string)
{
    char *source = string;
    char *destination = string;

    while (*source != '\0') {
        if (*source != ' ') {
            *destination++ = *source;
        }
        source++;
    }

    *destination = '\0';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
            return 1;
        }
        return 0;
    }

    string[strcspn(string, "\n")] = '\0';
    remove_spaces(string);

    if (printf("%s\n", string) < 0) {
        fprintf(stderr, "Failed to write output.\n");
        return 1;
    }

    return 0;
}
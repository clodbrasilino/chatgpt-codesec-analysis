#include <ctype.h>
#include <stdio.h>

int string_to_lower(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (char *p = string; *p != '\0'; ++p) {
        *p = (char)tolower((unsigned char)*p);
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char string[1024];

    if (fgets(string, sizeof string, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    if (string_to_lower(string) != 0) {
        return 1;
    }

    if (fputs(string, stdout) == EOF) {
        return 1;
    }

    return 0;
}
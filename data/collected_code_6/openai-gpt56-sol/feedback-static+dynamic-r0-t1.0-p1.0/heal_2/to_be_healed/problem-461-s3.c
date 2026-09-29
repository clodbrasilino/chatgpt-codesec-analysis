#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_uppercase(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (isupper((unsigned char)*string) != 0) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    size_t count = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (isupper((unsigned char)character) != 0) {
            ++count;
        }
    }

    if (ferror(stdin) != 0) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}
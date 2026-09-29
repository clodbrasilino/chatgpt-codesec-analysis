#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_vowels(const char *string)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        int character = tolower((unsigned char)*string);

        if (character == 'a' || character == 'e' ||
            character == 'i' || character == 'o' ||
            character == 'u') {
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
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        int lower = tolower((unsigned char)character);

        if (lower == 'a' || lower == 'e' ||
            lower == 'i' || lower == 'o' ||
            lower == 'u') {
            ++count;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count);
    return EXIT_SUCCESS;
}
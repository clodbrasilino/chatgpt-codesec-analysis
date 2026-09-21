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

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        int lowercase = tolower((unsigned char)character);

        if (lowercase == 'a' || lowercase == 'e' ||
            lowercase == 'i' || lowercase == 'o' ||
            lowercase == 'u') {
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
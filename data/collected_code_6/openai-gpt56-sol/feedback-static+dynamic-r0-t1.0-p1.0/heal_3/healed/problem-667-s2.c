#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

static int is_vowel(unsigned char character)
{
    int lower = tolower(character);

    return lower == 'a' ||
           lower == 'e' ||
           lower == 'i' ||
           lower == 'o' ||
           lower == 'u';
}

int main(void)
{
    size_t count = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (is_vowel((unsigned char)character)) {
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
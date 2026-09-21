#include <ctype.h>
#include <stdint.h>
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
            if (count == SIZE_MAX) {
                fputs("Vowel count overflow.\n", stderr);
                return EXIT_FAILURE;
            }
            ++count;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
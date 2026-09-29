#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_vowels(const char *string)
{
    size_t count = 0U;

    if (string == NULL) {
        return 0U;
    }

    while (*string != '\0') {
        int character = tolower((unsigned char)*string);

        if (character == 'a' || character == 'e' || character == 'i' ||
            character == 'o' || character == 'u') {
            ++count;
        }

        ++string;
    }

    return count;
}

int main(void)
{
    char input[1024];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    printf("%zu\n", count_vowels(input));
    return EXIT_SUCCESS;
}
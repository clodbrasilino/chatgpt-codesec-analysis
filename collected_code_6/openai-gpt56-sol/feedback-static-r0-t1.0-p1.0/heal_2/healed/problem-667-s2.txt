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
    char buffer[4096];

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        printf("0\n");
        return EXIT_SUCCESS;
    }

    printf("%zu\n", count_vowels(buffer));
    return EXIT_SUCCESS;
}
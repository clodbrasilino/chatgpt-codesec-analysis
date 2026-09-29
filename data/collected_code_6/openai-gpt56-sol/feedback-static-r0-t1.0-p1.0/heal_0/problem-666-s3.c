#include <stdio.h>
#include <stdlib.h>

size_t count_char_occurrences(const char *string, char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        if (*string == character) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char input[1024];
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    character = getchar();
    if (character == EOF) {
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_char_occurrences(input, (char)character));

    return EXIT_SUCCESS;
}
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || repeated == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = *string++;

        if (seen[character]) {
            *repeated = character;
            return true;
        }

        seen[character] = true;
    }

    return false;
}

int main(void)
{
    unsigned char input[UCHAR_MAX + 2];
    unsigned char repeated;
    size_t length = 0;
    int character = EOF;

    while (length < sizeof(input) - 1) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof(input) - 1 &&
        character != EOF &&
        character != '\n') {
        do {
            character = fgetc(stdin);
        } while (character != EOF && character != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (find_first_repeated_character(input, &repeated)) {
        printf("%c\n", (int)repeated);
    } else {
        puts("No repeated character");
    }

    return EXIT_SUCCESS;
}
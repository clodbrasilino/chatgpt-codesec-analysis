#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   size_t length,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || repeated == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = string[i];

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
    unsigned char input[UCHAR_MAX + 1];
    unsigned char repeated;
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= sizeof input) {
            while ((character = fgetc(stdin)) != EOF && character != '\n') {
            }

            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (find_first_repeated_character(input, length, &repeated)) {
        if (printf("%c\n", (int)repeated) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
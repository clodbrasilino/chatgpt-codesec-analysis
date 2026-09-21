#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   size_t length,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (repeated == NULL || (string == NULL && length != 0)) {
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
    enum { INPUT_SIZE = 4096 };
    unsigned char input[INPUT_SIZE];
    size_t length = 0;
    unsigned char repeated;

    while (length < sizeof input) {
        int character = getchar();

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        input[length++] = (unsigned char)character;
    }

    if (length == sizeof input) {
        int character;

        do {
            character = getchar();
        } while (character != EOF && character != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (find_first_repeated_character(input, length, &repeated)) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
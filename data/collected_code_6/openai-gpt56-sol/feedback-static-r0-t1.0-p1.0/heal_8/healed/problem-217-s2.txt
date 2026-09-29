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
    bool seen[UCHAR_MAX + 1] = { false };
    bool found = false;
    unsigned char repeated = 0;
    int character;

    while ((character = getchar()) != EOF && character != '\n') {
        unsigned char value = (unsigned char)character;

        if (!found && seen[value]) {
            repeated = value;
            found = true;
        }

        seen[value] = true;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (found) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int first_repeated_character(const unsigned char *data, size_t length,
                             unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (result == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char character = data[i];

        if (seen[character] != 0U) {
            *result = character;
            return 1;
        }

        seen[character] = 1U;
    }

    return 0;
}

int main(void)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    unsigned char repeated_character = 0U;
    int found = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n') {
        unsigned char character = (unsigned char)ch;

        if (!found && seen[character] != 0U) {
            repeated_character = character;
            found = 1;
        }

        seen[character] = 1U;
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (found) {
        if (putchar((int)repeated_character) == EOF ||
            putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character found.") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
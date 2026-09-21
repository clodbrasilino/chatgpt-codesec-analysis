#include <limits.h>
#include <stddef.h>
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
    unsigned char input[4096];
    size_t length = 0U;
    int ch;

    while (length < sizeof input &&
           (ch = getchar()) != EOF &&
           ch != '\n') {
        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof input && ch != EOF && ch != '\n') {
        do {
            ch = getchar();
        } while (ch != EOF && ch != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    unsigned char repeated_character;
    int status = first_repeated_character(input, length, &repeated_character);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated_character) == EOF ||
            putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
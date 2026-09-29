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
        unsigned int index = data[i];

        if (seen[index] != 0U) {
            *result = data[i];
            return 1;
        }

        seen[index] = 1U;
    }

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 4096 };
    unsigned char input[INPUT_CAPACITY];
    size_t length = 0U;
    int ch;
    int status;
    unsigned char repeated_character = 0U;

    while (length < sizeof input) {
        ch = getchar();

        if (ch == EOF || ch == '\n') {
            break;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof input) {
        ch = getchar();

        if (ch != EOF && ch != '\n') {
            do {
                ch = getchar();
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            if (fputs("Input is too long.\n", stderr) == EOF) {
                return EXIT_FAILURE;
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    status = first_repeated_character(input, length, &repeated_character);

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
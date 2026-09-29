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
    unsigned char *input = malloc(INPUT_CAPACITY);
    size_t length = 0U;
    int ch = EOF;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length == INPUT_CAPACITY) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != '\n');

            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }

            fputs("Input is too long.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    unsigned char repeated_character = 0U;
    int status = first_repeated_character(input, length, &repeated_character);

    free(input);

    if (status < 0) {
        return EXIT_FAILURE;
    }

    if (status > 0) {
        if (putchar((int)repeated_character) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found.") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
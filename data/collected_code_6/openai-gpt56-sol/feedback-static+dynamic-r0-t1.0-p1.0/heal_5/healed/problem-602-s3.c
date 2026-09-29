#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int first_repeated_character(const char *string, size_t length,
                             unsigned char *result)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};

    if (string == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)string[i];

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
    enum { INPUT_CAPACITY = 1024 };
    char input[INPUT_CAPACITY];
    unsigned char repeated_character = 0;

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
        return 0;
    }

    size_t length = 0;

    while (length < (size_t)INPUT_CAPACITY &&
           input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == (size_t)INPUT_CAPACITY) {
        fputs("Invalid input.\n", stderr);
        return 1;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
    }

    int status = first_repeated_character(input, length,
                                          &repeated_character);

    if (status < 0) {
        fputs("Invalid argument.\n", stderr);
        return 1;
    }

    if (status == 1) {
        if (putchar((int)repeated_character) == EOF ||
            putchar('\n') == EOF) {
            return 1;
        }
    } else if (puts("No repeated character found.") == EOF) {
        return 1;
    }

    return 0;
}
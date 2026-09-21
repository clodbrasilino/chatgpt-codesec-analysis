#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool starts_with_vowel(const char *string)
{
    if (string == NULL || *string == '\0') {
        return false;
    }

    switch (*string) {
    case 'A':
    case 'E':
    case 'I':
    case 'O':
    case 'U':
    case 'a':
    case 'e':
    case 'i':
    case 'o':
    case 'u':
        return true;
    default:
        return false;
    }
}

static bool discard_remainder(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 1];
    size_t length = 0;
    int character;

    while ((character = getchar()) != '\n' && character != EOF) {
        if (length >= MAX_INPUT_LENGTH) {
            if (!discard_remainder()) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }
            return EXIT_FAILURE;
        }

        input[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == 0) {
            fputs("No input provided.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    puts(starts_with_vowel(input)
             ? "Starts with a vowel"
             : "Does not start with a vowel");

    return EXIT_SUCCESS;
}
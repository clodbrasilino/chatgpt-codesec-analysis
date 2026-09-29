#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static bool starts_with_vowel(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    switch (string[0]) {
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
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ch == '\n' || !ferror(stdin);
}

int main(void)
{
    char input[MAX_INPUT_LENGTH + 2];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "No input provided.\n",
              stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (length < sizeof input && input[length] != '\0' &&
           input[length] != '\n') {
        ++length;
    }

    if (length == sizeof input) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else if (length > MAX_INPUT_LENGTH) {
        if (!discard_remainder()) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }
        return EXIT_FAILURE;
    } else if (length == MAX_INPUT_LENGTH) {
        int next = fgetc(stdin);

        if (next == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
        } else if (next != '\n') {
            if (!discard_remainder()) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }
            return EXIT_FAILURE;
        }
    }

    puts(starts_with_vowel(input)
             ? "Starts with a vowel"
             : "Does not start with a vowel");

    return EXIT_SUCCESS;
}
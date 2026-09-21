#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return !ferror(stdin);
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char input[MAX_INPUT_LENGTH + 2];

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "No input provided.\n",
              stderr);
        return EXIT_FAILURE;
    }

    size_t length = 0;

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
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
        int ch = getchar();

        if (ch != '\n' && ch != EOF) {
            if (!discard_remainder()) {
                fputs("Failed to read input.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(starts_with_vowel(input)
             ? "Starts with a vowel"
             : "Does not start with a vowel");

    return EXIT_SUCCESS;
}
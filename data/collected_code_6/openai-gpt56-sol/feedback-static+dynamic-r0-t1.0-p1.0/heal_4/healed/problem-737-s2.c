#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "Input is too large.\n",
              stderr);
        return EXIT_FAILURE;
    } else if (length == MAX_INPUT_LENGTH) {
        int ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            fputs(ferror(stdin) ? "Failed to read input.\n"
                               : "Input is too large.\n",
                  stderr);
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
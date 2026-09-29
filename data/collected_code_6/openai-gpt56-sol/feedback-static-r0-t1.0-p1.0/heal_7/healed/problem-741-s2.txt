#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { INPUT_CAPACITY = 1024 };

static bool all_characters_same(const char *string)
{
    if (string == NULL || string[0] == '\0') {
        return false;
    }

    for (size_t i = 1; string[i] != '\0'; ++i) {
        if (string[i] != string[0]) {
            return false;
        }
    }

    return true;
}

static bool discard_line(void)
{
    int character;

    do {
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        char *newline = memchr(input, '\n', INPUT_CAPACITY);

        if (newline != NULL) {
            *newline = '\0';
        } else {
            int character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                if (!discard_line()) {
                    fputs("Failed to read input.\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }

                fputs("Input is too long.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            if (character == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }
        }
    }

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return EXIT_SUCCESS;
}
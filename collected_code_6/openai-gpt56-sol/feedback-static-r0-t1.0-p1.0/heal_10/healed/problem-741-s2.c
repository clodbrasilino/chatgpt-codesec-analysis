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

    while ((character = getchar()) != '\n' && character != EOF) {
    }

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
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
        size_t length = strlen(input);

        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        } else {
            int character = getchar();

            if (character == '\n') {
            } else if (character == EOF) {
                if (ferror(stdin)) {
                    fputs("Failed to read input.\n", stderr);
                    free(input);
                    return EXIT_FAILURE;
                }
            } else {
                if (!discard_line()) {
                    fputs("Failed to read input.\n", stderr);
                } else {
                    fputs("Input is too long.\n", stderr);
                }

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
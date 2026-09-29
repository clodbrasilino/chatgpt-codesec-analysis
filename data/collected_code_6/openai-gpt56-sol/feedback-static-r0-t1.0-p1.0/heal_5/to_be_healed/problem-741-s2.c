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
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();
    } while (character != '\n' && character != EOF);

    return character == '\n' || !ferror(stdin);
}

int main(void)
{
    char *input = malloc(INPUT_CAPACITY);

    if (input == NULL) {
        fputs("Failed to allocate input buffer.\n", stderr);
        return 1;
    }

    if (fgets(input, INPUT_CAPACITY, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            free(input);
            return 1;
        }

        input[0] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(input);

        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        } else if (!feof(stdin)) {
            if (!discard_line()) {
                fputs("Failed to read input.\n", stderr);
                free(input);
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            free(input);
            return 1;
        }
    }

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    free(input);
    return 0;
}
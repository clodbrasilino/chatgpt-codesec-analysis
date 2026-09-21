#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);
    } while (character != '\n' && character != EOF);

    return character == '\n' || (character == EOF && !ferror(stdin));
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_CAPACITY];

    if (fgets(input, (int)sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    } else {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length > 0 && input[length - 1] == '\n') {
            input[length - 1] = '\0';
        } else {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int character = fgetc(stdin);

            if (character == '\n') {
            } else if (character == EOF) {
                if (ferror(stdin)) {
                    fputs("Failed to read input.\n", stderr);
                    return EXIT_FAILURE;
                }
            } else {
                if (!discard_line()) {
                    fputs("Failed to read input.\n", stderr);
                    return EXIT_FAILURE;
                }

                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    puts(all_characters_same(input)
             ? "All characters are the same."
             : "Not all characters are the same.");

    return EXIT_SUCCESS;
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           string[0] == 'a' &&
           string[1] == 'b' &&
           string[2] == 'b' &&
           (length == 3U || string[3] == 'b');
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };

    char input[MAX_INPUT_LENGTH + 1U];
    size_t length = 0U;
    int character = EOF;

    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length >= MAX_INPUT_LENGTH) {
            while ((character = fgetc(stdin)) != EOF &&
                   character != '\n' &&
                   character != '\r') {
            }

            if (character == '\r') {
                int next_character = fgetc(stdin);

                if (next_character != '\n' && next_character != EOF) {
                    if (ungetc(next_character, stdin) == EOF) {
                        return EXIT_FAILURE;
                    }
                }
            }

            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }

        input[length++] = (char)character;
    }

    if (character == '\r') {
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF) {
            if (ungetc(next_character, stdin) == EOF) {
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}
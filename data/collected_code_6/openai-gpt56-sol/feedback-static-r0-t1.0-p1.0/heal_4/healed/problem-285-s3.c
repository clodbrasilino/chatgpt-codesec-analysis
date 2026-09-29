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
    char input[5];
    size_t length = 0U;
    int character;
    bool too_long = false;

    while ((character = getchar()) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length < sizeof(input) - 1U) {
            input[length++] = (char)character;
        } else {
            too_long = true;
        }
    }

    if (character == '\r') {
        int next_character = getchar();

        if (next_character != '\n' && next_character != EOF &&
            ungetc(next_character, stdin) == EOF) {
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    puts(!too_long && matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}
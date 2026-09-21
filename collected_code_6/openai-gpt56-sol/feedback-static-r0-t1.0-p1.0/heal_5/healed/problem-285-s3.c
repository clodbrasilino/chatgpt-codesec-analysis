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

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    bool complete_line = input[length] == '\n' ||
                         input[length] == '\r' ||
                         feof(stdin);

    if (input[length] == '\r') {
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF) {
            complete_line = false;
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    } else if (!complete_line) {
        int character;

        while ((character = fgetc(stdin)) != '\n' &&
               character != '\r' &&
               character != EOF) {
        }

        if (character == '\r') {
            int next_character = fgetc(stdin);

            if (next_character != '\n' && next_character != EOF) {
                while ((character = fgetc(stdin)) != '\n' &&
                       character != '\r' &&
                       character != EOF) {
                }
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    puts(complete_line && matches_pattern(input, length)
             ? "Match"
             : "No match");

    return EXIT_SUCCESS;
}
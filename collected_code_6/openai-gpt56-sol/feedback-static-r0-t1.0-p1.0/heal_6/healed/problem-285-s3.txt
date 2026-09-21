#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool matches_pattern(const char *string, size_t length)
{
    return string != NULL &&
           (length == 3U || length == 4U) &&
           memcmp(string, "abbb", length) == 0;
}

int main(void)
{
    char input[6];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\r') {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            ungetc(character, stdin);
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    } else if (input[length] == '\0' && !feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != '\r' && character != EOF);

        if (character == '\r') {
            character = fgetc(stdin);

            if (character != '\n' && character != EOF) {
                ungetc(character, stdin);
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    input[length] = '\0';

    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}
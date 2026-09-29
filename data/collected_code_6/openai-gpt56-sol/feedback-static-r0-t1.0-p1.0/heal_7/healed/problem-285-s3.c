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

static int discard_line_remainder(void)
{
    int character;

    while ((character = getchar()) != '\n' &&
           character != '\r' &&
           character != EOF) {
    }

    if (character == '\r') {
        character = getchar();

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return -1;
            }
        }
    }

    return ferror(stdin) ? -1 : 0;
}

int main(void)
{
    char input[5];
    size_t length;

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }

        puts("No match");
        return EXIT_SUCCESS;
    }

    length = strcspn(input, "\r\n");

    if (input[length] == '\0' && length == sizeof input - 1U) {
        int character = getchar();

        if (character != '\n' && character != '\r' && character != EOF) {
            if (discard_line_remainder() != 0) {
                return EXIT_FAILURE;
            }

            puts("No match");
            return EXIT_SUCCESS;
        }

        if (character == '\r') {
            character = getchar();

            if (character != '\n' && character != EOF) {
                if (ungetc(character, stdin) == EOF) {
                    return EXIT_FAILURE;
                }
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    } else if (input[length] == '\r') {
        int character = getchar();

        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                return EXIT_FAILURE;
            }
        }

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';
    puts(matches_pattern(input, length) ? "Match" : "No match");

    return EXIT_SUCCESS;
}
#include <stdbool.h>
#include <stdio.h>

enum { MAX_WORD_LENGTH = 255 };

static bool has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (length == MAX_WORD_LENGTH) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        ++length;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0U) {
            return 1;
        }
    } else if (character == '\r') {
        character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            ungetc(character, stdin);
        }

        if (ferror(stdin)) {
            return 1;
        }
    }

    puts(has_even_length(length) ? "Even" : "Odd");
    return 0;
}
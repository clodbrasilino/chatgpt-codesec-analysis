#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool ends_with_number(int character)
{
    return character != EOF && isdigit((unsigned char)character) != 0;
}

int main(void)
{
    int character;
    int last_character = EOF;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n' || character == '\r') {
            break;
        }

        last_character = character;
    }

    if (puts(ends_with_number(last_character) ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
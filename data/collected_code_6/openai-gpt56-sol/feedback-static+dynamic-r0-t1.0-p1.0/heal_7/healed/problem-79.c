#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_odd_length(size_t length)
{
    return (length & (size_t)1) != 0;
}

int main(void)
{
    size_t length = 0;
    int character;

    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next_character = getchar();

            if (next_character == EOF) {
                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }
            } else if (next_character != '\n') {
                if (ungetc(next_character, stdin) == EOF) {
                    return EXIT_FAILURE;
                }
            }

            break;
        }

        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (character == EOF && ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
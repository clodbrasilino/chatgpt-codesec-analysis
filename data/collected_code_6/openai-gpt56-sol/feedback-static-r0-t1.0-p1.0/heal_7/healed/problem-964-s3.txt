#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_even_length(size_t length)
{
    return (length & 1U) == 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = fgetc(stdin);

            if (next == EOF) {
                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }
            } else if (next != '\n' && ungetc(next, stdin) == EOF) {
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (character == EOF && (ferror(stdin) || length == 0U)) {
        return EXIT_FAILURE;
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
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
            } else if (next != '\n') {
                if (ungetc(next, stdin) == EOF) {
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
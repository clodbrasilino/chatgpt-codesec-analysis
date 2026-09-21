#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    while ((character = getchar()) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
                if (ungetc(next, stdin) == EOF) {
                    return EXIT_FAILURE;
                }
            }

            if (next == EOF && ferror(stdin)) {
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == SIZE_MAX) {
            return EXIT_FAILURE;
        }

        ++length;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        return EXIT_FAILURE;
    }

    if (puts(has_odd_length(length) ? "Odd" : "Even") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
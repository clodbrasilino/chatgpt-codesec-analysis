#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_even_length(size_t length)
{
    return (length & 1U) == 0U;
}

int main(void)
{
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
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

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        return EXIT_FAILURE;
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
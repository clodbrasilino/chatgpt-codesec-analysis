#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    size_t length = 0U;
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = getchar();

            if (next != '\n' && next != EOF) {
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

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0U) {
        return EXIT_FAILURE;
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

enum { MAX_WORD_LENGTH = 255 };

static bool has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    size_t length = 0U;
    int character;

    while ((character = getchar()) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length >= MAX_WORD_LENGTH) {
            do {
                character = getchar();
            } while (character != EOF &&
                     character != '\n' &&
                     character != '\r');

            if (ferror(stdin)) {
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        ++length;
    }

    if (ferror(stdin)) {
        return 1;
    }

    puts(has_even_length(length) ? "Even" : "Odd");
    return 0;
}
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
    char input[MAX_WORD_LENGTH + 2U];

    if (fgets(input, sizeof input, stdin) == NULL) {
        return ferror(stdin) ? 1 : 0;
    }

    size_t length = 0U;

    while (input[length] != '\0' &&
           input[length] != '\n' &&
           input[length] != '\r') {
        ++length;
    }

    if (input[length] == '\0' && length > MAX_WORD_LENGTH) {
        int character;

        do {
            character = getchar();
        } while (character != EOF && character != '\n' && character != '\r');

        if (ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    puts(has_even_length(length) ? "Even" : "Odd");
    return 0;
}
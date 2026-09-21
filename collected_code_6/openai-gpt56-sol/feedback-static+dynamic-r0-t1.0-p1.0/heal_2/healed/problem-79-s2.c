#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool has_odd_length(size_t length)
{
    return length % 2U != 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length >= sizeof word - 1U) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                return 1;
            }

            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == EOF) {
        if (ferror(stdin) || length == 0U) {
            return 1;
        }
    }

    word[length] = '\0';

    puts(has_odd_length(length) ? "Odd" : "Even");
    return 0;
}
#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (character == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            } else if (next == EOF && ferror(stdin)) {
                return 1;
            }

            break;
        }

        if (length >= sizeof word - 1U) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }

            if (ferror(stdin)) {
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    word[length] = '\0';
    puts(has_even_length(word, length) ? "Even" : "Odd");

    return 0;
}
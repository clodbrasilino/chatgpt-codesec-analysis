#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1U >= sizeof word) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }

            fprintf(stderr, "Input is too long.\n");
            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");
    return 0;
}
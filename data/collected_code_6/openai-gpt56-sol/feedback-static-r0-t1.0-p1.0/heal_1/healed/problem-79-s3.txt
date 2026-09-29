#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' &&
           character != '\r' &&
           character != EOF) {
        if (length >= sizeof word - 1U) {
            while (character != '\n' && character != EOF) {
                character = fgetc(stdin);
            }
            return 1;
        }

        word[length++] = (char)character;
    }

    if (character == '\r') {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            ungetc(character, stdin);
        }
    }

    if (character == EOF && length == 0U) {
        return 1;
    }

    word[length] = '\0';

    if (has_odd_length(length)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    return 0;
}
#include <stdbool.h>
#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static bool has_odd_length(size_t length)
{
    return length % 2U != 0U;
}

static bool discard_line(int character)
{
    while (character != '\n' && character != EOF) {
        character = fgetc(stdin);
    }

    return character != EOF;
}

int main(void)
{
    char word[WORD_CAPACITY];
    size_t length = 0U;
    int character;

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    while (word[length] != '\0' &&
           word[length] != '\n' &&
           word[length] != '\r') {
        ++length;
    }

    if (word[length] == '\0') {
        character = fgetc(stdin);

        if (character != '\n' && character != '\r' && character != EOF) {
            discard_line(character);
            return 1;
        }

        if (character == '\r') {
            character = fgetc(stdin);
            if (character != '\n' && character != EOF) {
                ungetc(character, stdin);
            }
        }
    } else if (word[length] == '\r' && word[length + 1U] == '\0') {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            ungetc(character, stdin);
        }
    }

    word[length] = '\0';

    if (has_odd_length(length)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    return 0;
}
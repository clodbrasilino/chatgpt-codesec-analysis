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

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = 0U;

    while (word[length] != '\0' && word[length] != '\n') {
        ++length;
    }

    if (word[length] == '\n') {
        word[length] = '\0';
    } else {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            return 1;
        }

        if (character == EOF && ferror(stdin)) {
            return 1;
        }
    }

    if (length == 0U && feof(stdin)) {
        return 1;
    }

    puts(has_odd_length(length) ? "Odd" : "Even");
    return 0;
}
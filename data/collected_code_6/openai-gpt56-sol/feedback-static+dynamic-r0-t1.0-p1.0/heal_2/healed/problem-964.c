#include <stdio.h>

enum { WORD_CAPACITY = 256 };

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];

    if (fgets(word, sizeof word, stdin) == NULL) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        }
        return 1;
    }

    size_t length = 0U;

    while (length < sizeof word && word[length] != '\0' &&
           word[length] != '\n') {
        ++length;
    }

    if (length < sizeof word && word[length] == '\n') {
        word[length] = '\0';
    } else if (length == sizeof word - 1U) {
        int character = fgetc(stdin);

        if (character != '\n' && character != EOF) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (character == EOF && ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            fputs("Input is too long.\n", stderr);
            return 1;
        }

        if (character == EOF && ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
            return 1;
        }
    }

    puts(has_even_length(word, length) ? "Even" : "Odd");
    return 0;
}
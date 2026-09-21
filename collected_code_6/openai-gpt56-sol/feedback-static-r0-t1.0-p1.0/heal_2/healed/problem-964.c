#include <stdio.h>

#define WORD_CAPACITY 256U

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char word[WORD_CAPACITY];

    if (fgets(word, sizeof word, stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        }
        return 1;
    }

    size_t length = 0U;

    while (length < sizeof word && word[length] != '\0' && word[length] != '\n') {
        ++length;
    }

    if (length < sizeof word && word[length] == '\n') {
        word[length] = '\0';
    } else if (!feof(stdin)) {
        int character;

        do {
            character = fgetc(stdin);
        } while (character != '\n' && character != EOF);

        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        } else {
            fprintf(stderr, "Input is too long.\n");
        }

        return 1;
    }

    puts(has_even_length(word, length) ? "Even" : "Odd");
    return 0;
}
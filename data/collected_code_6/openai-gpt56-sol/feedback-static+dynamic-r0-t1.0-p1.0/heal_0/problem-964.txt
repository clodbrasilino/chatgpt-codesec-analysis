#include <stdio.h>
#include <string.h>

static int has_even_length(const char *word)
{
    return word != NULL && strlen(word) % 2U == 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof(word), stdin) == NULL) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed to read input.\n");
        }
        return 1;
    }

    size_t length = strlen(word);

    if (length > 0U && word[length - 1U] == '\n') {
        word[length - 1U] = '\0';
    } else if (length == sizeof(word) - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            fprintf(stderr, "Input is too long.\n");
            return 1;
        }
    }

    puts(has_even_length(word) ? "Even" : "Odd");
    return 0;
}
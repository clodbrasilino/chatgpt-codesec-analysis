#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool has_even_length(const char *word)
{
    return word != NULL && strlen(word) % 2U == 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && !feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF && ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    word[length] = '\0';

    puts(has_even_length(word) ? "Even" : "Odd");
    return 0;
}
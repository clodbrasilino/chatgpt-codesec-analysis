#include <stdbool.h>
#include <stdio.h>
#include <string.h>

static bool has_odd_length(const char *word)
{
    return word != NULL && (strlen(word) % 2U) != 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = strlen(word);

    if (length > 0U && word[length - 1U] == '\n') {
        word[length - 1U] = '\0';
    } else if (length == sizeof word - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            return 1;
        }
    }

    printf("%s\n", has_odd_length(word) ? "Odd" : "Even");
    return 0;
}
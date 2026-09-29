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

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && length == sizeof word - 1U) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character != '\n') {
            return 1;
        }
    }

    word[length] = '\0';

    if (has_odd_length(word)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    return 0;
}
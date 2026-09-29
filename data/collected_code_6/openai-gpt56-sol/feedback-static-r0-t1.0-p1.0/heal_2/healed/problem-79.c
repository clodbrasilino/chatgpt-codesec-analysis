#include <stdio.h>
#include <string.h>

static int has_odd_length(const char *word, size_t length)
{
    return word != NULL && (length % 2U) != 0U;
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

        while ((character = getchar()) != '\n' && character != EOF) {
        }

        return 1;
    }

    word[length] = '\0';

    if (ferror(stdin)) {
        return 1;
    }

    puts(has_odd_length(word, length) ? "Odd" : "Even");

    return 0;
}
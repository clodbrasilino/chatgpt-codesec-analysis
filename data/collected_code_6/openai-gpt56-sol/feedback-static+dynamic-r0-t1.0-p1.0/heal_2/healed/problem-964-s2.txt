#include <stdio.h>
#include <string.h>

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && (length % 2U) == 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && length == sizeof word - 1U) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);
    }

    word[length] = '\0';

    if (puts(has_even_length(word, length) ? "Even" : "Odd") == EOF) {
        return 1;
    }

    return 0;
}
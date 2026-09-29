#include <stdio.h>
#include <string.h>

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char word[256];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return 1;
    }

    size_t length = strcspn(word, "\r\n");

    if (length == sizeof word - 1U && word[length] != '\n') {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char word[MAX_INPUT_LENGTH + 2];

    if (fgets(word, sizeof word, stdin) == NULL) {
        return ferror(stdin) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    size_t length = strcspn(word, "\r\n");

    if (word[length] == '\0' && length == MAX_INPUT_LENGTH + 1) {
        int ch;

        while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        }

        return EXIT_FAILURE;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    return EXIT_SUCCESS;
}
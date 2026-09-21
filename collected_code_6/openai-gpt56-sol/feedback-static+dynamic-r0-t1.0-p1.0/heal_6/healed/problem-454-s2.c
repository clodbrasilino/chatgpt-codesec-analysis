#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum { MAX_INPUT_LENGTH = 4096 };

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char word[MAX_INPUT_LENGTH + 1];
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length >= MAX_INPUT_LENGTH) {
            while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
            }

            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            return EXIT_FAILURE;
        }

        word[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0) {
        return EXIT_SUCCESS;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    return EXIT_SUCCESS;
}
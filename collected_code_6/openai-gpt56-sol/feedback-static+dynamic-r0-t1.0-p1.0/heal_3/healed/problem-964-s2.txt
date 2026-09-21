#include <stdio.h>
#include <stdlib.h>

static int has_even_length(size_t length)
{
    return (length % 2U) == 0U;
}

int main(void)
{
    char *word = NULL;
    size_t size = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1U >= size) {
            size_t new_size = size == 0U ? 128U : size * 2U;

            if (new_size <= size) {
                free(word);
                return 1;
            }

            char *new_word = realloc(word, new_size);
            if (new_word == NULL) {
                free(word);
                return 1;
            }

            word = new_word;
            size = new_size;
        }

        word[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(word);
        return 1;
    }

    if (length > 0U && word[length - 1U] == '\r') {
        --length;
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        free(word);
        return 1;
    }

    free(word);
    return 0;
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(word);
                return EXIT_FAILURE;
            }

            char *new_word = realloc(word, new_capacity);

            if (new_word == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == '\r') {
        int next = fgetc(stdin);

        if (next != '\n' && next != EOF) {
            if (ungetc(next, stdin) == EOF) {
                free(word);
                return EXIT_FAILURE;
            }
        }
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(word);
        return EXIT_FAILURE;
    }

    puts(has_even_length(length) ? "Even" : "Odd");

    free(word);
    return EXIT_SUCCESS;
}
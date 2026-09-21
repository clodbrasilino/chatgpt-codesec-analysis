#include <stdio.h>
#include <stdlib.h>

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(word);
                fputs("Input is too long.\n", stderr);
                return 1;
            }

            char *new_word = realloc(word, new_capacity);

            if (new_word == NULL) {
                free(word);
                fputs("Failed to allocate memory.\n", stderr);
                return 1;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(word);
        fputs("Failed to read input.\n", stderr);
        return 1;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0U ? 1U : capacity + 1U;
        char *new_word = realloc(word, new_capacity);

        if (new_word == NULL) {
            free(word);
            fputs("Failed to allocate memory.\n", stderr);
            return 1;
        }

        word = new_word;
        capacity = new_capacity;
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");

    free(word);
    return 0;
}
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character;

    while ((character = fgetc(stdin)) != EOF &&
           character != '\n' &&
           character != '\r') {
        if (length == capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;
            char *resized;

            if (new_capacity <= capacity) {
                free(word);
                return 1;
            }

            resized = realloc(word, new_capacity);
            if (resized == NULL) {
                free(word);
                return 1;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == '\r') {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            if (ungetc(character, stdin) == EOF) {
                free(word);
                return 1;
            }
        }
    }

    if (character == EOF && ferror(stdin)) {
        free(word);
        return 1;
    }

    if (length == capacity) {
        size_t new_capacity = capacity == 0U ? 1U : capacity + 1U;
        char *resized;

        if (new_capacity <= capacity) {
            free(word);
            return 1;
        }

        resized = realloc(word, new_capacity);
        if (resized == NULL) {
            free(word);
            return 1;
        }

        word = resized;
        capacity = new_capacity;
    }

    word[length] = '\0';

    if (has_odd_length(length)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    free(word);
    return 0;
}
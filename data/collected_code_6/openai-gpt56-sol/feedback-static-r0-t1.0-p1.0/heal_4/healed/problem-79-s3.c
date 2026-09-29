#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character = EOF;

    for (;;) {
        character = fgetc(stdin);

        if (character == EOF || character == '\n' || character == '\r') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(word);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else if (capacity > SIZE_MAX / 2U) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            resized = realloc(word, new_capacity);
            if (resized == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == '\r') {
        int next_character = fgetc(stdin);

        if (next_character != '\n' && next_character != EOF &&
            ungetc(next_character, stdin) == EOF) {
            free(word);
            return EXIT_FAILURE;
        }

        if (next_character == EOF && ferror(stdin)) {
            free(word);
            return EXIT_FAILURE;
        }
    } else if (character == EOF && ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (word == NULL) {
        word = malloc(1U);
        if (word == NULL) {
            return EXIT_FAILURE;
        }
    }

    word[length] = '\0';

    if (has_odd_length(length)) {
        puts("The word length is odd.");
    } else {
        puts("The word length is even.");
    }

    free(word);
    return EXIT_SUCCESS;
}
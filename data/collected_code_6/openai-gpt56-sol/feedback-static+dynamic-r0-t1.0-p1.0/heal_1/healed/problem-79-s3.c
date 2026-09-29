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
    size_t length = 0U;
    size_t capacity = 16U;
    int character;

    word = malloc(capacity);
    if (word == NULL) {
        return 1;
    }

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        char *resized_word;

        if (character == '\r') {
            int next_character = fgetc(stdin);

            if (next_character != '\n' && next_character != EOF) {
                if (ungetc(next_character, stdin) == EOF) {
                    free(word);
                    return 1;
                }
            }
            break;
        }

        if (length == capacity - 1U) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(word);
                return 1;
            }

            new_capacity = capacity * 2U;
            resized_word = realloc(word, new_capacity);
            if (resized_word == NULL) {
                free(word);
                return 1;
            }

            word = resized_word;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(word);
        return 1;
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
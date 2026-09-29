#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_even_length(const char *word, size_t length)
{
    return word != NULL && length % 2U == 0U;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    for (;;) {
        ch = fgetc(stdin);

        if (ch == EOF) {
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                free(word);
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(word);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else if (capacity > SIZE_MAX / 2U) {
                free(word);
                return EXIT_FAILURE;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length) {
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

        word[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stdin) || (ch == EOF && length == 0U)) {
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

    if (puts(has_even_length(word, length) ? "Even" : "Odd") == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
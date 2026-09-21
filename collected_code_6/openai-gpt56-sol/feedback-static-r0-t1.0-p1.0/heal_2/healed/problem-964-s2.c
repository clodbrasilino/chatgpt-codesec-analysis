#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (ch == '\r') {
            int next = fgetc(stdin);

            if (next != '\n' && next != EOF) {
                ungetc(next, stdin);
            }
            break;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(word);
                return 1;
            }

            char *new_word = realloc(word, new_capacity);

            if (new_word == NULL) {
                free(word);
                return 1;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)ch;
    }

    if (ch == EOF && length == 0U) {
        free(word);
        return 1;
    }

    if (length + 1U > capacity) {
        char *new_word = realloc(word, length + 1U);

        if (new_word == NULL) {
            free(word);
            return 1;
        }

        word = new_word;
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");

    free(word);
    return 0;
}
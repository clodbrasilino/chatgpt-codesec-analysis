#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_even_length(size_t length)
{
    return length % 2U == 0U;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int ch;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(word);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(word);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            char *temporary = realloc(word, new_capacity);
            if (temporary == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = temporary;
            capacity = new_capacity;
        }

        word[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (ch == EOF && length == 0U) {
        free(word);
        return EXIT_FAILURE;
    }

    if (length > 0U && word[length - 1U] == '\r') {
        --length;
    }

    if (word != NULL) {
        word[length] = '\0';
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
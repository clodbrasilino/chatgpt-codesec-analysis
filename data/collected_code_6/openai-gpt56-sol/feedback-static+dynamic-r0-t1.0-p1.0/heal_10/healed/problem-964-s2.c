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
    int ch = EOF;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        char *temporary;
        size_t required;
        size_t new_capacity;

        if (length > SIZE_MAX - 2U) {
            free(word);
            return EXIT_FAILURE;
        }

        required = length + 2U;

        if (required > capacity) {
            new_capacity = capacity == 0U ? 128U : capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            temporary = realloc(word, new_capacity);
            if (temporary == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = temporary;
            capacity = new_capacity;
        }

        word[length++] = (char)(unsigned char)ch;
        word[length] = '\0';
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
        word[--length] = '\0';
    }

    if (puts(has_even_length(length) ? "Even" : "Odd") == EOF) {
        free(word);
        return EXIT_FAILURE;
    }

    free(word);
    return EXIT_SUCCESS;
}
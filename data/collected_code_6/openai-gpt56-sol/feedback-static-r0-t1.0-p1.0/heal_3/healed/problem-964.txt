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
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity * 2U;

            if (new_capacity <= capacity) {
                free(word);
                fprintf(stderr, "Input is too long.\n");
                return 1;
            }

            char *resized = realloc(word, new_capacity);
            if (resized == NULL) {
                free(word);
                fprintf(stderr, "Failed to allocate memory.\n");
                return 1;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(word);
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    if (word == NULL) {
        word = malloc(1U);
        if (word == NULL) {
            fprintf(stderr, "Failed to allocate memory.\n");
            return 1;
        }
    }

    word[length] = '\0';
    puts(has_even_length(word, length) ? "Even" : "Odd");

    free(word);
    return 0;
}
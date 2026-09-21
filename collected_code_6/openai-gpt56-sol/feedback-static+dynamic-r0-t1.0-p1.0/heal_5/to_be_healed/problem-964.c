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
    size_t length = 0U;
    size_t capacity = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(word);
                    fputs("Input is too long.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            char *new_word = realloc(word, new_capacity);

            if (new_word == NULL) {
                free(word);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(word);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(word);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        char *new_word = realloc(word, capacity + 1U);

        if (new_word == NULL) {
            free(word);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        word = new_word;
    }

    word[length] = '\0';

    puts(has_even_length(word, length) ? "Even" : "Odd");

    free(word);
    return EXIT_SUCCESS;
}
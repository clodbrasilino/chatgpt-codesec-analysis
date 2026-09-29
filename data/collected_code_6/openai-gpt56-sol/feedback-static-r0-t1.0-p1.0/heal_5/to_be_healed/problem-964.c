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
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == SIZE_MAX - 1U) {
            free(word);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;

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

            char *resized = realloc(word, new_capacity);
            if (resized == NULL) {
                free(word);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(word);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (word == NULL) {
        word = malloc(1U);
        if (word == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    word[length] = '\0';
    puts(has_even_length(word, length) ? "Even" : "Odd");

    free(word);
    return EXIT_SUCCESS;
}
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
        size_t required;

        if (length > SIZE_MAX - 2U) {
            free(word);
            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        required = length + 2U;

        if (required > capacity) {
            size_t new_capacity = capacity == 0U ? 64U : capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            resized = realloc(word, new_capacity);
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
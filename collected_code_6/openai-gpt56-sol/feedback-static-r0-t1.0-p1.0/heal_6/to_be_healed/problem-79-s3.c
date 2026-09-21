#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
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
    while ((character = fgetc(stdin)) != EOF) {
        size_t required;

        if (character == '\n' || character == '\r') {
            break;
        }

        if (length > SIZE_MAX - 2U) {
            free(word);
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
                return EXIT_FAILURE;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (character == '\r') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int next_character = fgetc(stdin);

        if (next_character == EOF) {
            if (ferror(stdin)) {
                free(word);
                return EXIT_FAILURE;
            }
        } else if (next_character != '\n' &&
                   ungetc(next_character, stdin) == EOF) {
            free(word);
            return EXIT_FAILURE;
        }
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
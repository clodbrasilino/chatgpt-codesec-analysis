#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return length % 2U != 0U;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0U;
    size_t capacity = 16U;
    int character;

    word = malloc(capacity);
    if (word == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next_character = fgetc(stdin);

            if (next_character != '\n' && next_character != EOF) {
                if (ungetc(next_character, stdin) == EOF) {
                    free(word);
                    return EXIT_FAILURE;
                }
            }

            if (next_character == EOF && ferror(stdin)) {
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
            char *resized_word;

            if (capacity > SIZE_MAX / 2U) {
                free(word);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized_word = realloc(word, new_capacity);
            if (resized_word == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = resized_word;
            capacity = new_capacity;
        }

        word[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(word);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(word);
        return EXIT_FAILURE;
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
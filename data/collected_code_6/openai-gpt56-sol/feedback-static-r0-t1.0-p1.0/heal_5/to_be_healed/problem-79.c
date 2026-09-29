#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int has_odd_length(size_t length)
{
    return (length & 1U) != 0U;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    int character = EOF;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = getchar();

        if (character == EOF || character == '\n') {
            break;
        }

        if (character == '\r') {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int next = getchar();

            if (next != '\n' && next != EOF && ungetc(next, stdin) == EOF) {
                free(word);
                return EXIT_FAILURE;
            }

            if (next == EOF && ferror(stdin)) {
                free(word);
                return EXIT_FAILURE;
            }

            break;
        }

        if (length == capacity) {
            size_t new_capacity;

            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    free(word);
                    return EXIT_FAILURE;
                }
                new_capacity = capacity * 2U;
            }

            if (new_capacity > SIZE_MAX / sizeof(*word)) {
                free(word);
                return EXIT_FAILURE;
            }

            char *new_word = realloc(word, new_capacity * sizeof(*word));

            if (new_word == NULL) {
                free(word);
                return EXIT_FAILURE;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)character;
    }

    if (ferror(stdin) || (character == EOF && length == 0U)) {
        free(word);
        return EXIT_FAILURE;
    }

    puts(has_odd_length(length) ? "Odd" : "Even");

    free(word);
    return EXIT_SUCCESS;
}
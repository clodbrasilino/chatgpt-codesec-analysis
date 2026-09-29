#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_odd_length(size_t length)
{
    return (length % 2U) != 0U;
}

int main(void)
{
    size_t length = 0U;
    size_t capacity = 16U;
    char *word = malloc(capacity);
    int character;

    if (word == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (length + 1U >= capacity) {
            size_t new_capacity;
            char *resized_word;

            if (capacity > (size_t)-1 / 2U) {
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

        word[length++] = (char)character;
    }

    if (character == EOF && length == 0U) {
        free(word);
        return EXIT_FAILURE;
    }

    word[length] = '\0';
    printf("%s\n", has_odd_length(length) ? "Odd" : "Even");

    free(word);
    return EXIT_SUCCESS;
}
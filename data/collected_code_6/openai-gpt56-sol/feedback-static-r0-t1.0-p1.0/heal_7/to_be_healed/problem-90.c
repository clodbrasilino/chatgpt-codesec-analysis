#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static size_t longest_word_length(const char *text)
{
    size_t longest = 0;
    size_t current = 0;

    if (text == NULL) {
        return 0;
    }

    while (*text != '\0') {
        if (isalnum((unsigned char)*text)) {
            ++current;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 0;
        }
        ++text;
    }

    return longest;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    char *input = malloc(capacity);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2;
            new_input = realloc(input, new_capacity);

            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    input[length] = '\0';

    if (printf("%zu\n", longest_word_length(input)) < 0) {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
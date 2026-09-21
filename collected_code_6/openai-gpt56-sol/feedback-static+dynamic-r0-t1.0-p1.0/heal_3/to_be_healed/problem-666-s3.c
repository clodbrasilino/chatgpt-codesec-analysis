#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t count_char_occurrences(const char *string, int character)
{
    size_t count = 0;
    unsigned char target;

    if (string == NULL || character == EOF) {
        return 0;
    }

    target = (unsigned char)character;

    while (*string != '\0') {
        if ((unsigned char)*string == target) {
            ++count;
        }
        ++string;
    }

    return count;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character;

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int current = fgetc(stdin);

        if (current == EOF) {
            if (ferror(stdin) || length == 0) {
                free(input);
                fputs("Failed to read the string.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        if (current == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_input;

            if (capacity == 0) {
                new_capacity = 128;
            } else if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)current;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stdin);
    if (character == EOF) {
        free(input);
        fputs("Failed to read the character.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%zu\n", count_char_occurrences(input, character));

    free(input);
    return EXIT_SUCCESS;
}
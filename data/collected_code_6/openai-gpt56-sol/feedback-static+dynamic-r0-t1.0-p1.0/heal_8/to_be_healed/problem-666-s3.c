#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t count_char_occurrences(const unsigned char *string,
                                     size_t length,
                                     unsigned char target)
{
    size_t count = 0;
    size_t i;

    for (i = 0; i < length; ++i) {
        if (string[i] == target) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    unsigned char *input;
    size_t capacity = 128;
    size_t length = 0;
    int current;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((current = fgetc(stdin)) != EOF && current != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            unsigned char *resized;

            if (capacity > SIZE_MAX / 2) {
                if (capacity == SIZE_MAX) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)current;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (current == EOF) {
        free(input);
        fputs("No character was provided.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    character = fgetc(stdin);
    if (character == EOF) {
        free(input);

        if (ferror(stdin)) {
            fputs("Failed to read the character.\n", stderr);
        } else {
            fputs("No character was provided.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    printf("%zu\n",
           count_char_occurrences(input, length, (unsigned char)character));

    free(input);
    return EXIT_SUCCESS;
}
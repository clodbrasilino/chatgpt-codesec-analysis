#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static size_t count_char_occurrences(const unsigned char *string,
                                     size_t length,
                                     unsigned char target)
{
    size_t count = 0;

    for (size_t i = 0; i < length; ++i) {
        if (string[i] == target) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    size_t capacity = 128;
    size_t length = 0;
    unsigned char *input = malloc(capacity);

    if (input == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int current = fgetc(stdin);

        if (current == EOF) {
            if (ferror(stdin)) {
                fputs("Failed to read the string.\n", stderr);
            } else {
                fputs("No character was provided.\n", stderr);
            }

            free(input);
            return EXIT_FAILURE;
        }

        if (current == '\n') {
            break;
        }

        if (length == capacity) {
            if (capacity == SIZE_MAX) {
                fputs("Input is too large.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            size_t new_capacity =
                capacity > SIZE_MAX / 2 ? SIZE_MAX : capacity * 2;
            unsigned char *resized = realloc(input, new_capacity);

            if (resized == NULL) {
                fputs("Failed to allocate memory.\n", stderr);
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)current;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    int character = fgetc(stdin);

    if (character == EOF) {
        if (ferror(stdin)) {
            fputs("Failed to read the character.\n", stderr);
        } else {
            fputs("No character was provided.\n", stderr);
        }

        free(input);
        return EXIT_FAILURE;
    }

    size_t count =
        count_char_occurrences(input, length, (unsigned char)character);

    if (printf("%zu\n", count) < 0) {
        fputs("Failed to write the result.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
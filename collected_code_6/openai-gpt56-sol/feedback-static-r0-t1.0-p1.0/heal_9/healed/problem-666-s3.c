#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

size_t count_char_occurrences(const unsigned char *string,
                              size_t length,
                              unsigned char character)
{
    size_t count = 0;

    if (string == NULL) {
        return 0;
    }

    for (size_t i = 0; i < length; ++i) {
        if (string[i] == character) {
            ++count;
        }
    }

    return count;
}

int main(void)
{
    unsigned char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;
    int character;

    while ((ch = fgetc(stdin)) != EOF && ch != '\n') {
        if (length == SIZE_MAX) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == capacity) {
            size_t new_capacity;
            unsigned char *temporary;

            if (capacity == 0) {
                new_capacity = 128;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free(input);
                    fputs("Input is too large.\n", stderr);
                    return EXIT_FAILURE;
                }

                new_capacity = capacity * 2;
            }

            temporary = realloc(input, new_capacity);
            if (temporary == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = temporary;
            capacity = new_capacity;
        }

        input[length++] = (unsigned char)ch;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read the string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (ch == EOF) {
        free(input);
        fputs("No character was provided.\n", stderr);
        return EXIT_FAILURE;
    }

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
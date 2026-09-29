#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t length_of_last_word(const char *string)
{
    size_t length = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string++;

        if (isspace(character)) {
            length = 0;
        } else {
            ++length;
        }
    }

    return length;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int character = EOF;

    while ((character = getchar()) != EOF) {
        if (length == capacity) {
            size_t new_capacity;

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

            char *resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                fputs("Failed to allocate memory.\n", stderr);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        if (character == '\n') {
            break;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == capacity) {
        if (capacity == SIZE_MAX) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        char *resized = realloc(input, capacity + 1);
        if (resized == NULL) {
            free(input);
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input = resized;
    }

    input[length] = '\0';
    printf("%zu\n", length_of_last_word(input));

    free(input);
    return EXIT_SUCCESS;
}
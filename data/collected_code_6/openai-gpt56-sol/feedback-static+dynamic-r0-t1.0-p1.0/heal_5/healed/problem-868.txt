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

    for (;;) {
        char buffer[4096];

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            if (ferror(stdin)) {
                free(input);
                fputs("Failed to read input.\n", stderr);
                return EXIT_FAILURE;
            }
            break;
        }

        size_t chunk_length = 0;

        while (chunk_length < sizeof buffer && buffer[chunk_length] != '\0' &&
               buffer[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > (size_t)-1 - length - 1) {
            free(input);
            fputs("Input is too large.\n", stderr);
            return EXIT_FAILURE;
        }

        size_t required = length + chunk_length + 1;

        if (required > capacity) {
            size_t new_capacity = capacity == 0 ? sizeof buffer : capacity;

            while (new_capacity < required) {
                if (new_capacity > (size_t)-1 / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
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

        for (size_t i = 0; i < chunk_length; ++i) {
            input[length + i] = buffer[i];
        }

        length += chunk_length;
        input[length] = '\0';

        if (buffer[chunk_length] == '\n') {
            break;
        }
    }

    if (input == NULL) {
        input = malloc(1);

        if (input == NULL) {
            fputs("Failed to allocate memory.\n", stderr);
            return EXIT_FAILURE;
        }

        input[0] = '\0';
    }

    if (printf("%zu\n", length_of_last_word(input)) < 0) {
        free(input);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    return EXIT_SUCCESS;
}
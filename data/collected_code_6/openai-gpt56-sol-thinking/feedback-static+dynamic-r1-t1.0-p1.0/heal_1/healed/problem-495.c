#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_MEMORY_FAILURE,
    REMOVE_REGEX_FAILURE,
    REMOVE_RANGE_FAILURE
} RemoveResult;

RemoveResult remove_lowercase_substrings(const char *input, char **output)
{
    const unsigned char *current;
    char *buffer;
    size_t capacity = 1U;
    size_t output_length = 0U;

    if (output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return REMOVE_MEMORY_FAILURE;
    }

    current = (const unsigned char *)input;

    while (*current != '\0') {
        if (islower((int)*current) == 0) {
            if (output_length == capacity - 1U) {
                size_t new_capacity;
                char *new_buffer;

                if (capacity == SIZE_MAX) {
                    free(buffer);
                    return REMOVE_RANGE_FAILURE;
                }

                if (capacity > SIZE_MAX / 2U) {
                    new_capacity = SIZE_MAX;
                } else {
                    new_capacity = capacity * 2U;
                }

                new_buffer = realloc(buffer, new_capacity);
                if (new_buffer == NULL) {
                    free(buffer);
                    return REMOVE_MEMORY_FAILURE;
                }

                buffer = new_buffer;
                capacity = new_capacity;
            }

            buffer[output_length++] = (char)*current;
        }

        ++current;
    }

    buffer[output_length] = '\0';
    *output = buffer;
    return REMOVE_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *result = NULL;
    RemoveResult status;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    status = remove_lowercase_substrings(argv[1], &result);
    if (status != REMOVE_SUCCESS) {
        if (fprintf(stderr, "Failed to process the input string.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
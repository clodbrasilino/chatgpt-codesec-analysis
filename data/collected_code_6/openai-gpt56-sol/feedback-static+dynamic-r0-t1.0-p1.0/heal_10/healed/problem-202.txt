#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_even_characters(const char *input, size_t length)
{
    size_t output_length;
    size_t source_index;
    size_t destination_index = 0U;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output_length = length / 2U;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    for (source_index = 1U; source_index < length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *input = malloc(capacity);
    char *result;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                free(input);
                return EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            size_t required = length + 2U;
            size_t new_capacity;
            char *resized_input;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity < required) {
                new_capacity = required;
            }

            if (new_capacity <= capacity) {
                free(input);
                return EXIT_FAILURE;
            }

            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    input[length] = '\0';

    result = remove_even_characters(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
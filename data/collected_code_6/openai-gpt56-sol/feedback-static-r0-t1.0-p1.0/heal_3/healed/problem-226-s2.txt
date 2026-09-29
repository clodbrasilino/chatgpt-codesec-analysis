#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_odd_indexed_characters(const char *input, size_t input_length)
{
    size_t output_length;
    size_t source_index;
    size_t destination_index;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output_length = input_length / 2U + input_length % 2U;

    if (output_length == SIZE_MAX) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    destination_index = 0U;

    for (source_index = 0U; source_index < input_length;) {
        output[destination_index++] = input[source_index];

        if (input_length - source_index <= 2U) {
            break;
        }

        source_index += 2U;
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char *input;
    char *result;
    size_t input_length;
    size_t input_capacity;
    int character;

    input = NULL;
    input_length = 0U;
    input_capacity = 0U;

    while ((character = getchar()) != EOF && character != '\n') {
        if (input_length == SIZE_MAX) {
            free(input);
            return EXIT_FAILURE;
        }

        if (input_length + 1U >= input_capacity) {
            size_t required_capacity;
            size_t new_capacity;
            char *resized_input;

            required_capacity = input_length + 2U;

            if (input_capacity == 0U) {
                new_capacity = 128U;
            } else if (input_capacity <= SIZE_MAX / 2U) {
                new_capacity = input_capacity * 2U;
            } else {
                new_capacity = SIZE_MAX;
            }

            if (new_capacity < required_capacity) {
                new_capacity = required_capacity;
            }

            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            input_capacity = new_capacity;
        }

        input[input_length++] = (char)(unsigned char)character;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (input == NULL) {
        input = malloc(1U);
        if (input == NULL) {
            return EXIT_FAILURE;
        }
    }

    input[input_length] = '\0';

    result = remove_odd_indexed_characters(input, input_length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (puts(result) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
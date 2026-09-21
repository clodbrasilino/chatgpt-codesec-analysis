#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static char *remove_odd_indexed_characters(const char *input, size_t input_length)
{
    size_t output_length;
    size_t source_index;
    size_t destination_index;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output_length = input_length / 2U + input_length % 2U;

    if (output_length > SIZE_MAX - 1U) {
        return NULL;
    }

    output = malloc(output_length + 1U);
    if (output == NULL) {
        return NULL;
    }

    destination_index = 0U;

    for (source_index = 0U; source_index < input_length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    size_t input_capacity = 128U;
    size_t input_length = 0U;
    char *input;
    char *result;
    int character;

    input = malloc(input_capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (input_length > SIZE_MAX - 2U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (input_length + 1U >= input_capacity) {
            size_t required_capacity = input_length + 2U;
            size_t new_capacity;
            char *resized_input;

            if (input_capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = input_capacity * 2U;
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
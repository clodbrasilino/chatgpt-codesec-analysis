#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_odd_indexed_characters(const char *input, size_t input_length)
{
    size_t output_length;
    char *output;
    size_t source_index;
    size_t destination_index = 0U;

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

    for (source_index = 0U; source_index < input_length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char *input = NULL;
    char *result;
    size_t input_length = 0U;
    size_t input_capacity = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != '\n' && character != EOF) {
        if (input_length > SIZE_MAX - 2U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (input_length + 1U >= input_capacity) {
            size_t new_capacity;
            char *resized_input;

            if (input_capacity == 0U) {
                new_capacity = 128U;
            } else {
                if (input_capacity > SIZE_MAX / 2U) {
                    free(input);
                    return EXIT_FAILURE;
                }
                new_capacity = input_capacity * 2U;
            }

            if (new_capacity <= input_length + 1U) {
                new_capacity = input_length + 2U;
            }

            resized_input = realloc(input, new_capacity);
            if (resized_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized_input;
            input_capacity = new_capacity;
        }

        input[input_length++] = (char)character;
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
        /* Possible weaknesses found:
         *  Value stored to 'input_capacity' is never read [deadcode.DeadStores]
         *  Variable 'input_capacity' is assigned a value that is never used. [unreadVariable]
         */
        input_capacity = 1U;
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
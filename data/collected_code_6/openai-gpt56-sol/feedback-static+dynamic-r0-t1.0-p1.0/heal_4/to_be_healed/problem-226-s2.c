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
    for (source_index = 0U; source_index < input_length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char *input;
    char *result;
    size_t length;
    size_t capacity;
    int character;

    capacity = 128U;
    length = 0U;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity) {
            size_t new_capacity;
            char *new_input;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length] = (char)(unsigned char)character;
        ++length;
    }

    if (character == EOF && ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    result = remove_odd_indexed_characters(input, length);
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_even_characters(const char *input, size_t length)
{
    size_t output_length;
    size_t source_index;
    size_t destination_index;
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

    destination_index = 0U;
    for (source_index = 1U; source_index < length; source_index += 2U) {
        output[destination_index++] = input[source_index];
    }

    output[destination_index] = '\0';
    return output;
}

int main(void)
{
    char *input;
    char *result;
    size_t capacity = 128U;
    size_t length = 0U;
    int character;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= SIZE_MAX - 1U) {
            free(input);
            return EXIT_FAILURE;
        }

        if (length + 1U >= capacity) {
            char *resized_input;
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
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

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    result = remove_even_characters(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}
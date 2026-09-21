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
    char *input;
    char *result;
    int character;
    int status = EXIT_SUCCESS;

    input = malloc(capacity);
    if (input == NULL) {
        return EXIT_FAILURE;
    }

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(input);
                return EXIT_FAILURE;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                free(input);
                return EXIT_FAILURE;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
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
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}
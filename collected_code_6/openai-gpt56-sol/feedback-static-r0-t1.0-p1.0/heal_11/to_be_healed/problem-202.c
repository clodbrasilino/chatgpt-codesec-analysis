#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_even_characters(const char *input, size_t length)
{
    size_t output_length;
    size_t source_index;
    size_t destination_index = 0;
    char *output;

    if (input == NULL) {
        return NULL;
    }

    output_length = length / 2U;

    if (output_length > SIZE_MAX - 1U) {
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
    int status = EXIT_SUCCESS;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                status = EXIT_FAILURE;
            }
            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                status = EXIT_FAILURE;
                break;
            }

            new_capacity = capacity * 2U;
            resized = realloc(input, new_capacity);
            if (resized == NULL) {
                status = EXIT_FAILURE;
                break;
            }

            input = resized;
            capacity = new_capacity;
        }

        input[length++] = (char)(unsigned char)character;
    }

    if (status != EXIT_SUCCESS) {
        free(input);
        return status;
    }

    input[length] = '\0';

    result = remove_even_characters(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fputs(result, stdout) == EOF || fputc('\n', stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free(result);
    return status;
}
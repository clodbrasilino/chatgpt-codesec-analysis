#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char *remove_lowercase_substrings(const char *input, size_t length)
{
    char *result;
    size_t read_index;
    size_t write_index = 0U;

    if (input == NULL || length == SIZE_MAX) {
        return NULL;
    }

    result = malloc(length + 1U);
    if (result == NULL) {
        return NULL;
    }

    for (read_index = 0U; read_index < length; ++read_index) {
        unsigned char character = (unsigned char)input[read_index];

        if (!islower(character)) {
            result[write_index++] = input[read_index];
        }
    }

    result[write_index] = '\0';
    return result;
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

        input[length++] = (char)(unsigned char)character;
    }

    if (ferror(stdin)) {
        free(input);
        return EXIT_FAILURE;
    }

    if (character == EOF && length == 0U) {
        free(input);
        return EXIT_SUCCESS;
    }

    result = remove_lowercase_substrings(input, length);
    free(input);

    if (result == NULL) {
        return EXIT_FAILURE;
    }

    if (fwrite(result, 1U, length, stdout) < length) {
        free(result);
        return EXIT_FAILURE;
    }

    if (fputc('\n', stdout) == EOF) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}